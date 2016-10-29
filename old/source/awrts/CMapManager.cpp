
#include <hrengin/io/IReadFile.h>
#include <hrengin/io/IBufferedStream.h>
#include <hrengin/core/IHDFParser.h>
#include <hrengin/graphics/ISceneManager.h>
#include <hrengin/graphics/IVisNode.h>

#include "CMapManager.h"
#include "units/CUnitManager.h"

namespace hrengin {
namespace awrts {

bool addUnit(hdf::IHDFParser* hdf, CUnitManager* umgr)
{
	u32 id;
	f32 x;
	f32 z;
	f32 f;
	bool loop = true;

	while(hdf->read() && loop) {
		hdf::HdfObjectType type = hdf->getObjectType();
		std::string name;
		std::string temp;

		switch(type) {
		case hdf::HDF_OBJ_NODE:
			hdf->getObjectName(name);
			hdf->error(hdf::HDF_LOG_WARNING, "unexpected node: " + name);
			hdf->skipNode();
			break;
		case hdf::HDF_OBJ_VAL:
			hdf->getObjectName(name);
			if(name == "type") {
				hdf->readString(temp);
				id = (temp.c_str()[0] << 24) +
				(temp.c_str()[1] << 16) + 
				(temp.c_str()[2] << 8) + 
				temp.c_str()[3];
			} else if(name == "x") {
				hdf->readFloat(x);
			} else if(name == "z") {
				hdf->readFloat(z);
			} else if(name == "f") {
				hdf->readFloat(f);
			}
			break;
		case hdf::HDF_OBJ_NODE_END:
			loop = false;
			break;
		case hdf::HDF_OBJ_NULL:
		default:
			return false;
		}
	}

	f32 h = umgr->unitTypes_[id].movementHeight;
	umgr->createUnit(id, Vector3d<f32>(x, h, z), f);

	return true;
}


} // namespace awrts
} // namespace hrengin
