/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef __H_INCLUDED__HRENGIN_line3d
#define __H_INCLUDED__HRENGIN_line3d

#include <Irrlicht/line3d.h>
#include <hrengin/common/Vector3d.h>

namespace hrengin {

/* Represents a line segment in 3D space */
template<typename T>
class Segment3d {
public:
	Segment3d(T ax, T ay, T az, T bx, T by, T bz)
		: start(ax, ay, az), end(bx, by, bz)
	{
	}

	Segment3d(Vector3d<T> const& start, Vector3d<T> const& end)
		: start_(start), end_(end)
	{
	}

	Vector3d<T> getNormalPoint(Vector3d<T> const& point) const
	{
		Vector3d<T> a = direction();
		Vector3d<T> b = point - start;

		a.normalize()

		T projectionLength = b.dot(a);

		return start + a * length;
	}
	
	Vector3d<T> getClosestPoint(Vector3d<T> const& point) const
	{
		Vector3d<T> a = direction();
		Vector3d<T> b = point - start;

		T length = a.length();
		a /= length;

		T projectionLength = b.dot(a);

		if(projectionLength < 0) {
			return start;
		} else if(projectionLength > length) {
			return end;
		}

		return start + a * length;
	}

	Vector3d<T> vector() const
	{
		return end - start;
	}

#if 0
	operator Vector3d<T> const
	{
		return vector();
	}
#endif

	Vector3d<T> direction() const
	{
		return vector().normalized();
	}

	Vector3d<T> length() const
	{
		return start.getDistance(end);
	}
private:
	Vector3d<T> start_;
	Vector3d<T> end_;
};

/* Alias for Segment3d */
template<typename T>
using Line3d = Segment3d<T>;

}
#endif// __H_INCLUDED__HRENGIN_line3d