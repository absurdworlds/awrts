/*
 * Copyright (C) 2015 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_gui_Size_
#define aw_gui_Size_
#include <aw/math/Vector2d.h>
namespace aw {
namespace gui {
/*!
 * This structure is used to store GUI element dimensions
 */
struct Size {
	/*!
	 * List of possible Size types.
	 */
	enum Type {
		/*!
		 * Fixed size is static pixel size.
		 * It is always same, independent of resolution
		 * and parent dimensions.
		 */
		Fixed,
		/*!
		 * Size with scalable X coordinate.
		 * X will be scaled to parent's percentage
		 * and Y will be always static
		 */
		ScalableX,
		/*!
		 * Size with static Y coordinate.
		 */
		ScalableY,
		/*!
		 * Size with both scalable coordinates
		 * Both coordinates are dymanically scaled to
		 * percentage of parent;
		 */
		Scalable,
		/*!
		 * Size with locked aspect ratio.
		 * Y will be scaled along with parent,
		 * X will stay proportional to Y.
		 */
		AspectLockedX,
		/*!
		 * Size with locked aspect ratio.
		 * Y is scaled proportionally to X.
		 */
		AspectLockedY,
	};

	/*!
	 * Screate static pixel size.
	 */
	static Size makeFixed(i32 x, i32 y)
	static Size makeScalableX(f32 x, i32 y)
	static Size makeScalableY(i32 x, f32 y)
	static Size makeScalable(i32 x, i32 y)
	static Size makeAspectLockedX(f32 y, f32 ratio)
	static Size makeAspectLockedY(f32 x, f32 ratio)

	/*!
	 * Convert size into pixels. Result depends on type.
	 */
	Vector2d<i32> toPixels(Vector2d<i32> parent);

private:
	Size(Type type)
		: type(type)
	{
	}

	Type type;

	union {
		struct {
			i32 x;
			i32 y;
		} fixed;
		struct {
			i32 coord;
			f32 scale;
		} scalableX;
		struct {
			f32 x;
			f32 y;
		} scalable;
		struct {
			f32 coord;
			f32 ratio;
		} aspect;
	};
};
} // namespace gui
} // namespace aw
#endif//_aw_gui_Size_
