/*
 * Copyright (C) 2016 Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <awrts/players/player.h>
#include <Irrlicht/IrrlichtDevice.h>
namespace aw::rts {
player::player(graphics::video_manager& vm)
	: cam{vm.irr_device().getSceneManager(),
	      vm.irr_device().getCursorControl()}
{}
} // namespace aw::rts
