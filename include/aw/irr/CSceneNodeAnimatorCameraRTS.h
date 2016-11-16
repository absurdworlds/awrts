
// This is an extension for the "Irrlicht Engine".
// See copyright notice in irrlicht.h

#ifndef __C_SCENE_NODE_ANIMATOR_CAMERA_RTS_H_INCLUDED__
#define __C_SCENE_NODE_ANIMATOR_CAMERA_RTS_H_INCLUDED__

#include <Irrlicht/ISceneNodeAnimator.h>
#include <Irrlicht/vector2d.h>

#include <chrono>

namespace irr {
namespace scene {
class CCameraSceneNode;
}
namespace gui
{
	class ICursorControl;
}

namespace scene {

	//! Scene node animator for RTS cameras
	struct CSceneNodeAnimatorCameraRTS : ISceneNodeAnimator {
		//! Constructor
		CSceneNodeAnimatorCameraRTS(gui::ICursorControl* cursor);

		~CSceneNodeAnimatorCameraRTS() override;

		//! Animates the scene node, currently only works on cameras
		void animateNode(ISceneNode* node, u32 timeMs) override;

		//! Event receiver
		bool OnEvent(const SEvent& event) override;

		//! Sets the keyboard mapping for this animator (old style)
		//virtual void setKeyMap(SRTSKeyMap *map, u32 count);

		//! Sets the keyboard mapping for this animator
		//!	\param keymap The new keymap array 
		//virtual void setKeyMap(const core::array<SRTSKeyMap>& keymap);

		//! Gets the keyboard mapping for this animator
		//virtual const core::array<SRTSKeyMap>& getKeyMap() const;
		
		//! This animator will receive events when attached to the active camera
		bool isEventReceiverEnabled() const override { return true; }

		//! Returns the type of this animator
		ESCENE_NODE_ANIMATOR_TYPE getType() const override
		{
			return ESNAT_CAMERA_FPS;
		}
		
		//! Returns the speed of movement
		f32 getMoveSpeed() const;

		//! Sets the speed of movement
		void setMoveSpeed(f32 moveSpeed);

		//! Returns the rotation speed
		f32 getRotateSpeed() const;

		//! Set the rotation speed
		void setRotateSpeed(f32 rotateSpeed);

		//! Returns the zoom speed
		f32 getZoomSpeed() const;

		//! Set the zoom speed
		void setZoomSpeed(f32 zoomSpeed);

		//! Returns the camera zoom
		f32 getZoom() const;

		//! Set the camera zoom
		void setZoom(f32 multiplier);

		//! Returns the current distance, i.e. orbit radius
		f32 getDistance() const;

		//! Set the distance
		void setDistance(f32 dist);
		
		//! Get the camera angle
		f32 getAngle() const;

		//! Set the camera angle
		void setAngle(f32 a);

		//! Get the camera angle for close zoom
		f32 getAngleClose() const;

		//! Set the camera angle
		void setAngleClose(f32 a);

	private:
		void allKeysUp();
		void animate();
		bool isMouseKeyDown(s32 key) const;

		bool MouseKeys[3];
		//bool MouseMiddle;
		enum MOUSE_KEY
		{
			MOUSE_KEY_RIGHT,
			MOUSE_KEY_MIDDLE,
			MOUSE_KEY_LEFT
		};
		
		gui::ICursorControl *CursorControl;
		
		bool FirstUpdateReceived = false;

		using clock = std::chrono::steady_clock;
		using time_point = std::chrono::time_point<clock>;
		using duration  = std::chrono::duration<double>;

		time_point last_update;

		scene::CCameraSceneNode* camera = nullptr;
		//core::vector3df OldTarget;
		//core::vector3df LastCameraTarget;
		
		//core::array<SRTSKeyMap> KeyMap;

		/*core::position2df RotateStart;
		core::position2df ZoomStart;
		core::position2df TranslateStart;*/

		f32 distance    = 36.055;
		f32 angle       = 0.9828;
		f32 angle_close = 0.5880;
		
		core::vector2di mousepos{0,0};
		core::vector2di mousepos_old{0,0};
		core::vector3df lasthit{0.0f, 0.0f, 0.0f};

		//bool CursorKeys[EKA_RTS_COUNT];

		f32 ZoomSpeed      = 0.1f;
		f32 RotateSpeed    = 0.1f;
		f32 TranslateSpeed = 100.0f;

		f32 MinZoom = 0.2f;
		f32 MaxZoom = 5.0f;
		f32 NewZoom = 1.0f;
		f32 CurrentZoom = 1.0f;
		
		f32 RotZ    = 0.0f;
		f32 MaxRotZ;

		//s32 LastAnimationTime;

		bool firstUpdate;
		//bool firstInput;

		bool Zooming     = false;
		bool Rotating    = false;
		bool Scrolling   = false;
		bool Scroll_lock = true;
		bool Dragging    = false;
	};

} // namespace scene
} // namespace irr

#endif//__C_SCENE_NODE_ANIMATOR_CAMERA_RTS_H_INCLUDED__
