#ifndef _awrts_CGame_
#define _awrts_CGame_

namespace hrengin {
class IEventManager;
class IEntityManager;
namespace core {
class ILogger;
class ISettingsManager;
class IShell;
}
namespace scene {
class ISceneManager;
}
namespace graphics {
class IVideoManager;
class IRenderingDevice;
}
namespace gui {
class IGUIManager;
class IInputManager;
}
namespace physics {
class IPhysicsManager;
class IPhysicsWorld;
class IDebugDrawer;
}

namespace awrts {
class CUnitManager;
class CMapManager;

class CGame {
public:
	CGame ();
	~CGame ();
	
	void loadSettings ();
	bool run ();

	graphics::IRenderingDevice* getRenderer()
	{
		return renderer_;
	}
private:
	// core
	core::ILogger* logger_;
	core::ISettingsManager* settings_;
	core::IShell* shell_;

	// graphics
	graphics::IVideoManager* videomgr_;
	graphics::IRenderingDevice* renderer_;

	// gui
	gui::IGUIManager* guimgr_;
	gui::IInputManager* inputmgr_;

	// physics
	physics::IPhysicsManager* phymgr_;
	physics::IPhysicsWorld*   pWorld_;
	
	physics::IDebugDrawer*    drawer_;

	// game
	scene::ISceneManager* scenemgr_;

	IEntityManager* entmgr_;
	IEventManager* eventmgr_;

	CUnitManager* unitmgr_;
	CMapManager* mapmgr_;
};

} // namespace awrts
} // namespace hrengin

#endif//_awrts_CGame_
