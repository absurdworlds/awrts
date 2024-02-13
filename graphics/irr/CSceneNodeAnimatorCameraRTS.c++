// This is an extension for the "Irrlicht Engine".
// See copyright notice in irrlicht.h

#include <iostream>
#include <aw/irr/CSceneNodeAnimatorCameraRTS.h>

#include <Irrlicht/IVideoDriver.h>
#include <Irrlicht/ICursorControl.h>
#include <Irrlicht/CSceneManager.h>
#include <Irrlicht/ISceneCollisionManager.h>
#include <Irrlicht/CCameraSceneNode.h>
#include <Irrlicht/CIrrDeviceLinux.h>

namespace irr {
namespace scene {
	
	CSceneNodeAnimatorCameraRTS::CSceneNodeAnimatorCameraRTS(gui::ICursorControl* cursor)
		: CursorControl{cursor}
	{
		if (CursorControl)
		{
			CursorControl->grab();
			//MousePos = CursorControl->getRelativePosition();
		}

		allKeysUp();

		// create default key map
		/*KeyMap.push_back(SRTSKeyMap(EKA_TRANSLATE_POS_X, irr::KEY_KEY_W));
		KeyMap.push_back(SRTSKeyMap(EKA_TRANSLATE_POS_Y, irr::KEY_KEY_A));
		KeyMap.push_back(SRTSKeyMap(EKA_TRANSLATE_NEG_X, irr::KEY_KEY_S));
		KeyMap.push_back(SRTSKeyMap(EKA_TRANSLATE_NEG_Y, irr::KEY_KEY_D));
		KeyMap.push_back(SRTSKeyMap(EKA_MOVEMENT_CONTROLS, irr::KEY_MENU));*/
	}

	//! destructor
	CSceneNodeAnimatorCameraRTS::~CSceneNodeAnimatorCameraRTS()
	{
		if (CursorControl)
		{
			CursorControl->drop();
		}
	}

	bool CSceneNodeAnimatorCameraRTS::OnEvent(const SEvent& event)
	{
		//if (event.EventType != EET_MOUSE_INPUT_EVENT)
		//	return false;


		switch(event.EventType)
		{
		case EET_MOUSE_INPUT_EVENT:
			switch(event.MouseInput.Event)
			{
			case EMIE_RMOUSE_PRESSED_DOWN:
				MouseKeys[1] = true;
				break;
			case EMIE_RMOUSE_LEFT_UP:
				MouseKeys[1] = false;
				break;
			case EMIE_MOUSE_MOVED:
				mousepos = CursorControl->getPosition();
				break;
			case EMIE_MOUSE_WHEEL:
				NewZoom -= event.MouseInput.Wheel * ZoomSpeed * (CurrentZoom / (MaxZoom * MinZoom));
				break;
			/*case EMIE_LMOUSE_PRESSED_DOWN:
				break;
			case EMIE_MMOUSE_PRESSED_DOWN
			case EMIE_MMOUSE_LEFT_UP:
			case EMIE_LMOUSE_LEFT_UP:
			case EMIE_LMOUSE_DOUBLE_CLICK:
			case EMIE_RMOUSE_DOUBLE_CLICK:
			case EMIE_MMOUSE_DOUBLE_CLICK:
			case EMIE_LMOUSE_TRIPLE_CLICK:
			case EMIE_RMOUSE_TRIPLE_CLICK:
			case EMIE_MMOUSE_TRIPLE_CLICK:
			case EMIE_COUNT:*/
			default:
				return false;
			}

			break;
			
		case EET_KEY_INPUT_EVENT:		
			/*for (u32 i=0; i<KeyMap.size(); ++i)
			{
				if (KeyMap[i].KeyCode == event.KeyInput.Key)
				{
					CursorKeys[KeyMap[i].Action] = event.KeyInput.PressedDown;
					return true;
				}
			}

			break;*/

		default:
			return false;
		}
		return true;
	}
	
	bool CSceneNodeAnimatorCameraRTS::isMouseKeyDown(s32 key) const
	{
		return MouseKeys[key];
	}
	

	void CSceneNodeAnimatorCameraRTS::allKeysUp()
	{
		for (s32 i=0; i<3; ++i)
			MouseKeys[i] = false;
	}
	
	//! OnAnimate() is called just before rendering the whole scene.
	void CSceneNodeAnimatorCameraRTS::animateNode(ISceneNode *node, u32 timeMs)
	{
		// Controls :
		// Alt + WSAD = move camera
		// Mouse middle + Mouse move = move camera
		// Mouse pointer X/Y at border  = move camera
		// Mouse wheel up/down = zoom camera

		if (!node || node->getType() != ESNT_CAMERA)
		{
			return;
		}
		
		camera = static_cast<CCameraSceneNode*>(node);

		// If the camera isn't the active camera, and receiving input, then don't process it.
		if (!camera->isInputReceiverEnabled())
		{
			return;
		}

		scene::CSceneManager* scnmgr = camera->getSceneManager();
		if (scnmgr && scnmgr->getActiveCamera() != camera)
		{
			return;
		}

		scene::ISceneCollisionManager* colman = scnmgr->getSceneCollisionManager();

		if (!CursorControl)
		{
			return;
		}
		
		core::dimension2d<u32> screen = scnmgr->getVideoDriver()->getScreenSize();
		if(!FirstUpdateReceived)
		{
			last_update = clock::now();
			FirstUpdateReceived = true;
			return;
		}
		
		auto now = clock::now();
		duration time_delta = now - last_update;
		last_update = now;
		
		// Camera movement
		core::vector3df pos = camera->getPosition();
		core::vector3df target = camera->getTarget();

		core::vector3df translate(0,0,0);
		
		bool outwindow = ((mousepos.X < 0)
				|| (mousepos.X > (screen.Width - 0))
				|| (mousepos.Y < 0)
				|| (mousepos.Y > (screen.Height - 0)));
		
		
		core::plane3df plane{ {0,1,0}, 0 };

		core::line3df ray_new = colman->getRayFromScreenCoordinates(mousepos, camera);

		core::vector3df pos_new;

		plane.getIntersectionWithLine(ray_new.start, ray_new.getVector(), pos_new);

		if(isMouseKeyDown(MOUSE_KEY_MIDDLE) && !Zooming) //&& !Translating)
		{
			Dragging = true;
			
			if(mousepos_old != mousepos) {
				core::line3df ray_new = colman->getRayFromScreenCoordinates(mousepos, camera);
				core::line3df ray_old = colman->getRayFromScreenCoordinates(mousepos_old, camera);

				core::vector3df pos_old;
				core::vector3df pos_new;

				plane.getIntersectionWithLine(ray_old.start, ray_old.getVector(), pos_old);
				plane.getIntersectionWithLine(ray_new.start, ray_new.getVector(), pos_new);

				translate.X += pos_old.X - pos_new.X;
				translate.Z += pos_old.Z - pos_new.Z;
				
			}
			
			if (outwindow)
			{
				Scroll_lock = true;
			}
		}
		else
		{
			Dragging = false;

			if (!outwindow)
			{
				Scroll_lock = false;
			}
		}
		mousepos_old = mousepos;
		
		if(NewZoom >= MaxZoom)
		{
			NewZoom = MaxZoom;
		}
		else if(NewZoom <= MinZoom)
		{
			NewZoom = MinZoom;
		}

		if(CurrentZoom != NewZoom && !Dragging && !Scrolling)
		{
			CurrentZoom = NewZoom;
			Zooming = true;
		}
		else
		{
			NewZoom = CurrentZoom;
			Zooming = false;
		}
		

		if (!Scroll_lock && !Dragging && !Zooming && !outwindow) {
			f32 scrollstep = TranslateSpeed * CurrentZoom * time_delta.count();
			if ((mousepos.X > 0) && (mousepos.X < 10)) {
				translate.X -= scrollstep;
			} else if ((mousepos.X > (screen.Width - 10))
				   && (mousepos.X < screen.Width)) {
				translate.X += scrollstep;
			}
			
			if ((mousepos.Y > 0) && (mousepos.Y < 10)) {
				translate.Z += scrollstep;
			} else if ((mousepos.Y > (screen.Height - 10))
				   && (mousepos.Y < screen.Height)) {
				translate.Z -= scrollstep;
			}
			
			Scrolling = !core::equals(translate.X + translate.Y,0.0f,core::ROUNDING_ERROR_f32);
		}

		f32 cur_angle;

		if(CurrentZoom < 1.f)
		{
			f32 relativeZoom = (CurrentZoom - MinZoom)/(1.f - MinZoom);
			cur_angle = angle * relativeZoom + angle_close * (1-relativeZoom);
		}
		else
		{
			cur_angle = angle;
		}

		target += translate; 

		core::vector3df camera_offset(0,distance*sin(cur_angle),-distance*cos(cur_angle));
		pos = target + camera_offset * CurrentZoom;
		
		/*target -=pos_new;
		pos -=pos_new;

		if(Zooming)
		{
			target /= CurrentZoom;
			pos /= CurrentZoom;
		fprintf(stderr, "DEBUG: �����-����\n", target.X);
		}

		target +=pos_new;
		pos +=pos_new;*/

		camera->setPosition(pos);
		camera->setTarget(target);
	}

	//! Returns the speed of movement
	f32 CSceneNodeAnimatorCameraRTS::getMoveSpeed() const
	{
		return TranslateSpeed;
	}

	//! Sets the speed of movement
	void CSceneNodeAnimatorCameraRTS::setMoveSpeed(f32 speed)
	{
		TranslateSpeed = speed;
	}

	//! Returns the rotation speed
	f32 CSceneNodeAnimatorCameraRTS::getRotateSpeed() const
	{
		return RotateSpeed;
	}

	//! Set the rotation speed
	void CSceneNodeAnimatorCameraRTS::setRotateSpeed(f32 speed)
	{
		RotateSpeed = speed;
	}

	//! Returns the zoom speed
	f32 CSceneNodeAnimatorCameraRTS::getZoomSpeed() const
	{
		return ZoomSpeed;
	}

	//! Set the zoom speed
	void CSceneNodeAnimatorCameraRTS::setZoomSpeed(f32 speed)
	{
		ZoomSpeed = speed;
	}

	//! Returns the camera zoom
	f32 CSceneNodeAnimatorCameraRTS::getZoom() const
	{
		return CurrentZoom;
	}

	//! Set the camera zoom
	void CSceneNodeAnimatorCameraRTS::setZoom(f32 multiplier)
	{
		if(multiplier < MaxZoom)
		{
			CurrentZoom = MaxZoom;
		}
		else if(multiplier > MinZoom)
		{
			CurrentZoom = MinZoom;
		}
		else
		{
			CurrentZoom = multiplier;
		}
	}

	//! Returns the current distance, i.e. orbit radius
	f32 CSceneNodeAnimatorCameraRTS::getDistance() const
	{
		return distance;
	}

	//! Set the distance
	void CSceneNodeAnimatorCameraRTS::setDistance(f32 dist)
	{
		distance = dist;
	}
		
	//! Get the camera angle
	f32 CSceneNodeAnimatorCameraRTS::getAngle() const
	{
		return angle;
	}

	//! Set the camera angle
	void CSceneNodeAnimatorCameraRTS::setAngle(f32 a)
	{
		angle = a;
	}

	//! Get the camera angle for close zoom
	f32 CSceneNodeAnimatorCameraRTS::getAngleClose() const
	{
		return angle_close;
	}

	//! Set the camera angle
	void CSceneNodeAnimatorCameraRTS::setAngleClose(f32 a)
	{
		angle_close = a;
	}


	
	/*//! Sets the keyboard mapping for this animator
	void CSceneNodeAnimatorCameraFPS::setKeyMap(SKeyMap *map, u32 count)
	{
		// clear the keymap
		KeyMap.clear();

		// add actions
		for (u32 i=0; i<count; ++i)
		{
			KeyMap.push_back(map[i]);
		}
	}

	void CSceneNodeAnimatorCameraFPS::setKeyMap(const core::array<SKeyMap>& keymap)
	{
		KeyMap=keymap;
	}

	const core::array<SKeyMap>& CSceneNodeAnimatorCameraFPS::getKeyMap() const
	{
		return KeyMap;
	}*/

} // end namespace scene
} // end namespace irr
