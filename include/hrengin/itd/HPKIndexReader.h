/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 2.1 <http://gnu.org/licenses/lgpl-2.1.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_HPKIndexReader_
#define _hrengin_HPKIndexReader_
#include <hrengin/common/types.h>
#include <hrengin/itd/itd.h>

namespace hrengin {
namespace itd {
/*!
 * Interface for reading HPKA index
 */
class HPKIndexReader {
public:
	virtual ~HPKIndexReader ()
	{
	}

	/*!
	 * Find a file
	 * \param path Full path to file
	 * \return D of the file or -1
	 */	 
	virtual u64 findFile (std::string const& path) = 0;
	/*!
	 * List all files with paths starting with \a prefix
	 * \param prefix Diectory to list
	 * \return List of files in directory \prefix
	 */
	virtual std::vector<std::string> list (std::string const& prefix) = 0;
};

} //namespace itd
} //namespace hrengin
#endif//_hrengin_HPKIndexReader_
