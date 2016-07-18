
#include <hrengin/io/IReadFile.h>
#include <hrengin/io/IBufferedStream.h>
#include <hrengin/core/IHDFParser.h>
#include <hrengin/graphics/ISceneManager.h>
#include <hrengin/graphics/IVisNode.h>

#include "CMapManager.h"
#include "units/CUnitManager.h"

namespace hrengin {
namespace awrts {

CMapManager::CMapManager(graphics::ISceneManager* sceneManager,
	CUnitManager* unitManager)
: scenemgr_(sceneManager), unitmgr_(unitManager)
{

}

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

bool CMapManager::loadMap(char * mapname)
{
	bool success = true;

	hrengin::graphics::IVisNode* node = scenemgr_->createMeshSceneNode(mapname);

	io::IReadFile* file = io::openReadFile("../maps/mainmenu.hmp/mapdata.hdf");
	io::IBufferedStream* stream = io::createBufferedStream(file);
	hdf::IHDFParser* hdf = hdf::createHDFParser(stream);
	
	hdf->read();
	if(hdf->getObjectType() == hdf::HDF_OBJ_NODE) {
		std::string name;
		hdf->getObjectName(name);
		if(name != "map") {
			hdf->error(hdf::HDF_LOG_ERROR, "not a map data");
		}
	}

	while(hdf->read()) {
		if(hdf->getObjectType() == hdf::HDF_OBJ_NODE) {
			std::string name;
			hdf->getObjectName(name);

			if(name == "addUnit") {
				addUnit(hdf, unitmgr_);
			} else {
				hdf->error(hdf::HDF_LOG_WARNING, "unknown node: " + name);
				hdf->skipNode();
			}
		} else {
			break;
		}
	}

	delete hdf;
	delete stream;
	delete file;

	return success;
}

} // namespace awrts
} // namespace hrengin
