/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 2.1 <http://gnu.org/licenses/lgpl-2.1.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <cstdio>

#include <aw/core/ArgumentParser.h>
#include <aw/string/utility.h>

#include "hpacker.h"

namespace aw {
namespace itd {
void printUsage()
{
	printf("Usage: hpacker [OPTION]... [FILE...]\n");
	printf("hpacker is a utility which packs files together into ITD archive.\n");
	printf("\n");
	printf("  -c, --create         Create an archive\n");
	printf("  -e, --extract        Extract contents of archive\n");
	printf("  -l, --list           List contents of archive\n");
	printf("  -f, --file NAME      Perform actions on file NAME\n");
	printf("  -v, --verbose        Show verbose output\n");
	printf("  -h, --help           Display this message\n");

}

i32 main (char** args)
{
	core::ArgumentParser* argp = core::createArgumentParser(args+1);

	enum Action {
		None,
		Create,
		Unpack,
		Extract,
		List
	} action;

	std::string filename;
	std::vector<std::string> files;
	bool verbose = false;

	core::Argument arg;
	while (argp->getNextArgument(arg)) {
		if (arg.type == core::Argument::Option) {
			if(arg.name == "c" || arg.name == "create") {
				action = Create;
			} else if (arg.name == "l" || arg.name == "list") {
				action = List;
			} else if (arg.name == "e" || arg.name == "extract") {
				action = Extract;
			} else if (arg.name == "f" || arg.name == "file") {
				argp->getNextArgument(arg);
				filename = arg.name;
			} else if (arg.name == "v" || arg.name == "verbose") {
				verbose = true;
			}
#if 0
		if(arg.type == core::Argument::Option && arg.name == "-") {
			// from stdin
		}
#endif

			if (arg.name == "h" || arg.name == "help") {
				printUsage();
			}
		} else if (arg.type == core::Argument::Arg) {
			if (!action) {
				fprintf(stderr, "No action selected\n");
				fprintf(stderr, "Type hpacker -h or hpacker --help for usage.\n");
				return -1;
			} else {
				files.push_back(arg.name);
			}
		}
	}

	if (action == Create) {
		ItdPacker packer(filename, verbose);
		packer.addList(files);

		packer.pack();
	} else if (action == List) {
		ItdReader reader(filename, verbose);
		auto list = reader.list("");

		for (auto file : list) {
			printf("%s\n",file.c_str());
		}
	} else if (action == Extract) {
		ItdReader reader(filename, verbose);

		for (auto file : files) {
			std::ofstream f(string::split(file,"/").back(), std::ios::binary);
			auto v = reader.getFileContents(file);
			f.write((char*)v.data(),v.size());
		}
	}


	return 0;
}

} // namespace itd
} // namespace aw

int main(int, char** argv)
{
	return aw::itd::main(argv);
}
