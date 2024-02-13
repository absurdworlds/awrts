/*
 * Copyright (C) 2016 Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef awrts_player_h
#define awrts_player_h
#include <awrts/graphics/video_manager.h>
#include <aw/irr/rts_camera.h>
namespace aw::rts {

struct player {
	player(graphics::video_manager& vm);
	graphics::rts_camera cam;
};

} // namespace aw::rts
#endif//awrts_player_h
