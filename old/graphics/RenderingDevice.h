/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_RenderingDevice_
#define _aw_RenderingDevice_

#include <aw/graphics/RenderingDevice.h>

namespace irr {
class IrrlichtDevice;

namespace video {
class VideoDriver;

} // namespace video
} // namespace irr

namespace aw {
namespace graphics {
class VertexBuffer;
class IndexBuffer;


class RenderingDevice : public RenderingDevice {
public:
	RenderingDevice(irr::video::IVideoDriver* driver);
	/*! Prepare scene for rendering.
	 *  Must be called before drawing anything.
	 */
	virtual bool beginRender();
	// beginFrame()

	//! end rendering the scene, and swap the buffers
	virtual bool endRender();
	// post()
	
	//! temporary tool to render debug drawers
	virtual void drawDebug();

	//! Draw a primitive using index buffer and vertex buffer
	virtual bool drawVertexPrimitive(const VertexBuffer& vb, const IndexBuffer& ib);

	//! Draw a line primitive
	virtual void drawLine(Vector3d<f32> const& from,
		Vector3d<f32> const& to, Vector3d<f32> const& color) = 0;
	virtual void drawLine(const Vector3d<f32>& from, const Vector3d<f32>& to, const Vector3d<f32>& color);

private:
	irr::video::IVideoDriver* driver_;
};

} // namespace graphics
} // namespace aw
#endif//_aw_RenderingDevice_
