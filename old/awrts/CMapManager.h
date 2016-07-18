#ifndef _awrts_CMapManager_
#define _awrts_CMapManager_

namespace hrengin {
namespace graphics {
class ISceneManager;
}
namespace awrts {
class CUnitManager;

class CMapManager {
public:
	CMapManager(graphics::ISceneManager* sceneManager,
		CUnitManager* unitManager);
	bool loadMap(char * mapname);

private:
	graphics::ISceneManager* scenemgr_;
	CUnitManager* unitmgr_;
};

} // namespace awrts
} // namespace hrengin

#endif//_awrts_CMapManager_
