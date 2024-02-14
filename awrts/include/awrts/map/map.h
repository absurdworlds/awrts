#ifndef awrts_map_h
#define awrts_map_h

#include "awrts/graphics/video_manager.h"
#include "awrts/units/unit.h"

namespace aw::rts {

class map {
public:
	std::vector<unit> units;
	void render(graphics::video_manager& vm);
};

} // namespace map
#endif // awrts_map_h
