/* This file is a part of hrengin library collection
 *
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 2.1 <http://gnu.org/licenses/lgpl-2.1.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <hrengin/platform/time.h>
#include <hrengin/io/IReadFile.h>
#include <hrengin/io/IDirectory.h>
#include <hrengin/core/IArgParser.h>
#include <sys/stat.h>

#include "hpacker.h"

namespace hrengin {
namespace itd {
CItdPacker::CItdPacker (std::string name)
	: name_(name)
{	
	archive_ = io::openWriteFile(name_, io::IWriteFile::Mode::Overwrite);
	tmp_ = io::openWriteFile(name_ + ".tmp.1",
				io::IWriteFile::Mode::Overwrite);

	
	itd::Header header;
	header.fileId = 'h' + ('i' << 8) + ('t' << 16) + ('d' << 24);
	header.version = 1;
	header.ptime = getTime();
	header.secondId = 'h' + ('p' << 8) + ('k' << 16) + ('a' << 24);

	archive_->write(&header.fileId,4);
	archive_->write(&header.version,4);
	archive_->write(&header.ptime,8);
	archive_->write(&header.secondId,4);
	archive_->write(&header.padding, 44);

	globalOffset_ = 64;
}

CItdPacker::~CItdPacker ()
{
	delete archive_;
}

i32 CItdPacker::packDir (std::string path, bool recursive)
{
	io::IDirectory* dir = io::openDirectory(path);
	if(!dir) {
		return -1;
	}

	io::Dirent file;

	while(dir->read(file)) {
		if(file.name == "." || file.name == "..") {
			continue;
		}
		switch(file.type) {
		case io::Dirent::Type::File:
			addFile(path, file);
			break;
		case io::Dirent::Type::Dir:
			if(recursive) {
				packDir(path + "/" + file.name, true);
			}
			break;
		default:
			break;
		}
	};

	return 0;
}

i32 CItdPacker::addFile (std::string path, io::Dirent file)
{
	io::IReadFile* rfile;
	itd::FileEntry entry;
	rfile = io::openReadFile(path + "/" + file.name);
	if(!rfile) {
		return -1;
	}
	
	//printf("%s\n",(path + "/" + file.name).c_str());

	entry.offset = tmp_->tell();
	entry.size   = rfile->getSize();
	entry.mtime  = 0;
	entry.flags  = itd::FileFlags::None;
	index_.push_back(entry);

	char* buf = new char[entry.size];
	rfile->read(buf, entry.size);

	tmp_->write(buf, entry.size);

	delete[] buf;
	delete rfile;

	return 0;
}

i32 CItdPacker::writeIndex()
{
	globalOffset_ += index_.size()*32;

	for(auto e : index_) {
		e.offset += globalOffset_;
		archive_->write(&e.offset,8);
		archive_->write(&e.size,8);
		archive_->write(&e.mtime,8);
		archive_->write(&e.flags,2);
		archive_->write(&e.padding[0],6);
	}
	
	return 0;
}

i32 CItdPacker::writeArchive() 
{
	delete tmp_;
	io::IReadFile* in;
	in = io::openReadFile(name_ + ".tmp.1");

	char buf[4096];
	i32 num;
	while((num = in->read(&buf, 4096))) {
		//printf("%d;%d\n",in->tell(),in->getSize());
		if(num > 0) {
			archive_->write(buf, num);
		}
	}

	return 0;
}

i32 main (char** args)
{
	core::IArgParser* argp = core::createArgParser(args);
	
	Action action;

	std::string filename;
	std::vector<std::string> files;
	std::string dir;

	core::ClineArg arg;
	while(argp->getToken(arg)) {
		if(arg.type == core::ClineArg::Option) {
			if(arg.name == "c" || arg.name == "create") {
				action = Create;
			}

			if(arg.name == "f" || arg.name == "file") {
				argp->getToken(arg);
				filename = arg.name;
			}
		}
	}
	
	argp->getToken(arg);
	dir = arg.name;
	
	if(action == Create) {
		CItdPacker packer(filename);
		packer.packDir(dir, true);
		packer.writeIndex();
		packer.writeArchive();
	}


	while(argp->getToken(arg)) {
		if(arg.type == core::ClineArg::Option && arg.name == "-") {
			// from stdin
		}

		if(arg.type == core::ClineArg::Argument) {
			files.push_back(arg.name);
		}
	}
	return 0;
}

} // namespace itd
} // namespace hrengin

int main (int, char** argv)
{
	return hrengin::itd::main(argv);
}
