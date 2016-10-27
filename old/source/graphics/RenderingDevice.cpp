/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <Irrlicht/irrlicht.h>

#include "RenderingDevice.h"

#include "hrToIrr.h"

namespace aw {
namespace graphics {

void RenderingDevice::drawLine(const Vector3d<f32>& from,
	const Vector3d<f32>& to, const Vector3d<f32>& color)
{
	irr::video::SColor irrcolor(255, irr::u32(color.x), irr::u32(color.y), irr::u32(color.z));

	driver_->draw3DLine(aw::toIrr(from), hrengin::toIrr(to), irrcolor);
}

void RenderingDevice::drawDebug()
{
	irr::video::SMaterial debugMat;
	debugMat.Lighting = false;

	driver_->setMaterial(debugMat);
	driver_->setTransform(irr::video::ETS_WORLD, irr::core::IdentityMatrix);
}
} // namespace video
} // namespace aw
