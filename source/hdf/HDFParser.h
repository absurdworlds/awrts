/*
 * Copyright (C) 2014-2105  absurdworlds
 * Copyright (C) 2015       Hedede <hededrk@gmail.com>
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_HDFParser_impl_
#define _hrengin_HDFParser_impl_
#include <string>
#include <vector>

#include <hrengin/hdf/hdf_value.h>
#include <hrengin/hdf/HDFParser.h>

namespace hrengin {
namespace hdf {
namespace impl_ {
enum HdfTokenType {
	HDF_TOKEN_NVALID,
	HDF_TOKEN_EOF,
	HDF_TOKEN_NAME,
	HDF_TOKEN_NUMBER,
	HDF_TOKEN_STRING,
};

struct HdfToken {
	HdfTokenType type;
	std::string value;
};

class HDFParser : public hdf::HDFParser {
public:
	HDFParser(io::CharacterStream* stream);
	virtual ~HDFParser();

	virtual void skipNode();
	virtual void skipValue();

	virtual bool read();

	virtual HdfObjectType getObjectType();
	virtual void getObjectName(std::string& name);

	virtual void readFloat(float& val);
	virtual void readFloat(double& val);
	virtual void readInt(u32& val);
	virtual void readInt(i32& val);
	virtual void readBool(bool& val);
	virtual void readString(std::string& val);
	virtual void readVector3d(Vector3d<f32>& val);

	void error(hdf::ParserMessage type, std::string msg);
private:
	template<typename T> 
	void readValue(T& val);
	template<typename T> 
	void convertValue(HdfToken& token, T& val);

	bool parseType(HdfToken& token);

	void readToken(HdfToken& token);

	void readStringToken(std::string& val);
	void readNumber(std::string& val);
	void readName(std::string& name, char stop = 0);

	void readValueName(std::string& name);
	void readTypeName(std::string& name);

	void fastForward();
	void skipLine();
	void skipWhitespace();
	void skipInlineWhitespace();
	//void skip(bool (*condition)(u8));
	template<bool (*condition)(char)> 
	void skip();

	enum HdfParserState {
		HDF_S_DLE = 0,
		HDF_S_OBJECT,
		HDF_S_NODE_BEGIN,
		HDF_S_MD_BEGIN,
		HDF_S_VALUE_BEGIN,
		HDF_S_VALUE_DATA,
		HDF_S_PANIC
	} state_;

	std::vector<std::string> errors_;

	void processCommand();

	io::CharacterStream* stream_;

	u32 depth_;
};
} // namespace impl_
} // namespace io
} // namespace hrengin
#endif//_hrengin_HDFParser_impl_
