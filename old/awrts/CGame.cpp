
#include "CGame.h"

#include <hrengin/platform/time.h>

#include <hrengin/core/IShell.h>
#include <hrengin/core/ILogger.h>
#include <hrengin/core/ISettingsManager.h>

#include <hrengin/graphics/IVideoManager.h>
#include <hrengin/scene/ISceneManager.h>
#include <hrengin/graphics/IRenderingDevice.h>

#include <hrengin/gui/IGUIManager.h>
#include <hrengin/gui/IConsoleGUI.h>
#include <hrengin/gui/IInputManager.h>

#include <hrengin/sound/ISoundManager.h>

#include <hrengin/game/IEntityManager.h>
#include <hrengin/game/IEventManager.h>

#include "Physics.h"

#include "Commands.h"


#include "CMapManager.h"
#include "players/CPlayerHuman.h"
#include "units/UnitType.h"
#include "units/CUnitManager.h"

namespace hrengin {
namespace awrts {

CGame::CGame ()
	: settings_(core::createSettingsManager()), logger_(core::createLogger())
{
	shell_ = core::createShell(logger_);

	scenemgr_ = videomgr_->getSceneManager();
	renderer_ = videomgr_->getRenderingDevice();

	scenemgr_->createLightSceneNode();

	guimgr_ = videomgr_->getGUIManager();
	inputmgr_ = guimgr_->getInputManager();
	guimgr_->setFont("../data/fonts/courier.xml");

	gui::IConsoleGUI* sonsole = gui::createConsole(shell_, guimgr_);
	logger_->addLog(sonsole);
	
	sound::getSoundManager().initSounds();
	
	phymgr_ = physics::createPhysicsManager();
	pWorld_ = phymgr_->createPhysicsWorld();

	drawer_ = phymgr_->createDebugDrawer(renderer_);
	drawer_->setWorld(pWorld_);

	entmgr_  = createEntityManager();
	eventmgr_ = createEventManager();

	
	unitmgr_ = new CUnitManager(scenemgr_, phymgr_, pWorld_, entmgr_, eventmgr_);
	mapmgr_ = new CMapManager(scenemgr_, unitmgr_);

	shell_->registerCommand("addUnit",new Thingy(logger_, unitmgr_));
	
	CPlayerHuman* TestPlayer = new CPlayerHuman(scenemgr_, /*inputmgr,*/unitmgr_, /*phymgr, */pWorld_);
	inputmgr_->registerReceiver(TestPlayer);
	
	unitmgr_->loadUnitTypes();
	pWorld_->addObject(phymgr_->createPhantom("ground.hdf"), physics::CollisionFilter(COL_GROUND, -1));
	mapmgr_->loadMap("ground.obj");
	
	settings_->setValue("debugmode", false);
}

CGame::~CGame ()
{
	delete logger_;
}

bool CGame::run ()
{
	bool runEngine = true;
	bool debugMode = 0;

	hrengin::u32 time = hrengin::getTime();
	hrengin::u32 lastTime = time;
	hrengin::u32 cycles = 0;
	hrengin::u32 mean = 0;
	do {
		if (!runEngine) break;

		lastTime = time;
		time = hrengin::getTime();

#if 0
		if (app.profiling) {
			if (((cycles + 1) % 100) == 0) {
				hrengin::getLogger().push("DEBUG:");
				hrengin::getLogger().push(std::to_string(mean/100.0));
				hrengin::getLogger().push(hrengin::endl);
				mean = 0;
			} else {
				mean += time - lastTime;
			}
		}
#endif

		if(!videomgr_->step())
			break;

		if(videomgr_->isWindowActive()) {
			renderer_->beginRender();
			renderer_->drawDebug();
			settings_->getValue("debugmode", debugMode);
			if(debugMode) {
				renderer_->drawLine(Vector3d<f32>(0,0.01f,0),Vector3d<f32>(0, 10.01f,0),Vector3d<f32>(0,255,0));
				renderer_->drawLine(Vector3d<f32>(0,0.01f,0),Vector3d<f32>(0,  0.01f,10),Vector3d<f32>(0,0,255));
				renderer_->drawLine(Vector3d<f32>(0,0.01f,0),Vector3d<f32>(10, 0.01f,0),Vector3d<f32>(255,0,0));
				drawer_->render();
			}
			renderer_->endRender();	
		} else {
			videomgr_->wait();
		}

		runEngine = pWorld_->step();

		entmgr_->doSync();
		//app.entmgr.doCleanup();
		cycles++;
	}
	while(runEngine);

	return runEngine;
}

void CGame::loadSettings ()
{
	settings_->loadSettings();
}

} // namespace awrts
} // namespace hrengin
