/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */

#include <Irrlicht/irrlicht.h>

#include "CRenderingDevice.h"

#include "hrToIrr.h"

namespace hrengin {
namespace graphics {

CRenderingDevice::CRenderingDevice(irr::video::IVideoDriver* driver)
: driver_(driver)
{

}

bool CRenderingDevice::drawVertexPrimitive(const IVertexBuffer& vb, const IIndexBuffer& ib)
{
	return false;
}

void CRenderingDevice::drawLine(const Vector3d<f32>& from,
	const Vector3d<f32>& to, const Vector3d<f32>& color)
{
	irr::video::SColor irrcolor(255, irr::u32(color.x), irr::u32(color.y), irr::u32(color.z));

	driver_->draw3DLine(hrengin::toIrr(from), hrengin::toIrr(to), irrcolor);
}


bool CRenderingDevice::beginRender()
{
	return driver_->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
}

void CRenderingDevice::drawDebug()
{
	irr::video::SMaterial debugMat;
	debugMat.Lighting = false;

	driver_->setMaterial(debugMat);
	driver_->setTransform(irr::video::ETS_WORLD, irr::core::IdentityMatrix);
}

bool CRenderingDevice::endRender()
{
	return driver_->endScene();
}

} // namespace video
} // namespace hrengin
