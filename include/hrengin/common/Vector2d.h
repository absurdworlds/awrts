#ifndef _hrengin_Vector2d_
#define _hrengin_Vector2d_

#include <hrengin/common/hrengintypes.h>
#include <hrengin/common/hrenginmath.h>

namespace hrengin
{

template <class T>
class hrVector2d
{
public: /* Data */
	// Vector coordinates
	T X;
	T Y;

public: /* Functions */
	// Constructors	
	hrVector2d() 
		: X(0), Y(0) 
	{	}

	hrVector2d(T x, T y) 
		: X(x), Y(y) 
	{	}
	
	// No implicit calling!
	explicit hrVector2d(T v) 
		: X(v), Y(v) 
	{	}

	// Copy constructor
	hrVector2d(const hrVector2d<T>& other) 
		: X(other.X), Y(other.Y)
	{	}

	/* Arithmetic operators */

	hrVector2d<T>& operator = (const hrVector2d<T>& other)
	{
		X = other.X; 
		Y = other.Y; 
		return *this; 
	}

	hrVector2d<T> operator - () const 
	{
		return hrVector2d<T>(-X, -Y);
	}

	
	hrVector2d<T> operator + (const hrVector2d<T>& other) const 
	{
		return hrVector2d<T>(X + other.X, Y + other.Y);
	}

	hrVector2d<T>& operator += (const hrVector2d<T>& other) 
	{
		X+=other.X; 
		Y+=other.Y; 
		return *this; 
	}

	hrVector2d<T> operator - (const hrVector2d<T>& other) const 
	{ 
		return hrVector2d<T>(X - other.X, Y - other.Y); 
	}

	hrVector2d<T>& operator -= (const hrVector2d<T>& other) 
	{ 
		X-=other.X; 
		Y-=other.Y; 
		return *this; 
	}

	hrVector2d<T> operator - (const T v) const 
	{ 
		return hrVector2d<T>(X - v, Y - v); 
	}

	hrVector2d<T>& operator -= (const T v) 
	{ 
		X-=v; 
		Y-=v; 
		return *this; 
	}

	hrVector2d<T> operator * (const hrVector2d<T>& other) const 
	{ 
		return hrVector2d<T>(X * other.X, Y * other.Y); 
	}

	hrVector2d<T>& operator *= (const hrVector2d<T>& other) 
	{ 
		X*=other.X; 
		Y*=other.Y; 
		return *this; 
	}

	hrVector2d<T> operator * (const T v) const
	{ 
		return hrVector2d<T>(X * v, Y * v);
	}

	hrVector2d<T>& operator *= (const T v) 
	{
		X*=v; 
		Y*=v; 
		return *this; 
	}

	hrVector2d<T> operator / (const hrVector2d<T>& other) const 
	{
		return hrVector2d<T>(X / other.X, Y / other.Y); 
	}

	hrVector2d<T>& operator /= (const hrVector2d<T>& other)
	{
		X/=other.X; 
		Y/=other.Y; 
		return *this;
	}

	hrVector2d<T> operator / (const T v) const 
	{
		return hrVector2d<T>(X / v, Y / v); 
	}

	hrVector2d<T>& operator /= (const T v) 
	{
		X/=v; 
		Y/=v; 
		return *this;
	}

	/* 
	 * Comparison operators 
	 * 
	 * Thinking of deprecating those, since they are confusing,
	 * and direct coparison of coordinates should be used instead,
	 * depending on occasion.
	 * 
	 */

	bool operator <= (const hrVector2d<T>&other) const
	{
		return (X + Y) < (other.X + other.Y) || this->equals(other);
	}

	bool operator >= (const hrVector2d<T>&other) const
	{
		return (X + Y) > (other.X + other.Y) || this->equals(other);
	}

	bool operator < (const hrVector2d<T>&other) const
	{
		return (X + Y) < (other.X + other.Y) && !this->equals(other);
	}

	bool operator > (const hrVector2d<T>&other) const
	{
		return (X + Y) > (other.X + other.Y) && !this->equals(other);
	}

	bool equals (const hrVector2d<T>& other) const 
	{
		return math::equals(X, other.X) && math::equals(Y, other.Y);
	}

	bool operator == (const hrVector2d<T>& other) const 
	{ 
		return this->equals(other); 
	}

	bool operator != (const hrVector2d<T>& other) const 
	{ 
		return !this->equals(other); 
	}
	
	/* Functions */

	//! Get length of the vector.
	T Length() const 
	{ 
		return math::sqrt( X*X + Y*Y ); 
	}

	//! Get squared length of the vector.
	T SquareLength() const 
	{ 
		return X*X + Y*Y; 
	}	
	
	//! Gets distance from another point. 
	T GetDistance(const hrVector2d<T>& other) const
	{
		return hrVector2d<T>(X - other.X, Y - other.Y).Length();
	}

	//! Get squared distance from another point.
	T GetSquaredDistance(const hrVector2d<T>& other) const
	{
		return hrVector2d<T>(X - other.X, Y - other.Y).SquareLength();
	}

	//! Get the dot product of this vector with another.
	T dotProduct(const hrVector2d<T>& other) const
	{
		return X*other.X + Y*other.Y;
	}

};

typedef hrVector2d<f32>	Vectorf2d;
typedef hrVector2d<f64>	Vectord2d;
typedef hrVector2d<i32>	Vectori2d;
typedef hrVector2d<i32>	Vector2d;
}

#endif // _hrengin_Vector2d_

/* borrowed from Irrlicht:
	// functions	


	//! rotates the point anticlockwise around a center by an amount of degrees.
	/** \param degrees Amount of degrees to rotate by, anticlockwise.
	\param center Rotation center.
	\return This vector after transformation. 
	vector2d<T>& rotateBy(f64 degrees, const vector2d<T>& center=vector2d<T>())
	{
		degrees *= DEGTORAD64;
		const f64 cs = cos(degrees);
		const f64 sn = sin(degrees);

		X -= center.X;
		Y -= center.Y;

		set((T)(X*cs - Y*sn), (T)(X*sn + Y*cs));

		X += center.X;
		Y += center.Y;
		return *this;
	}

	//! Normalize the vector.
	/** The null vector is left untouched.
	\return Reference to this vector, after normalization. 
	vector2d<T>& normalize()
	{
		f32 length = (f32)(X*X + Y*Y);
		if ( length == 0 )
			return *this;
		length = core::reciprocal_squareroot ( length );
		X = (T)(X * length);
		Y = (T)(Y * length);
		return *this;
	}

	//! Calculates the angle of this vector in degrees in the trigonometric sense.
	/** 0 is to the right (3 o'clock), values increase counter-clockwise.
	This method has been suggested by Pr3t3nd3r.
	\return Returns a value between 0 and 360. 
	f64 getAngleTrig() const
	{
		if (Y == 0)
			return X < 0 ? 180 : 0;
		else
		if (X == 0)
			return Y < 0 ? 270 : 90;

		if ( Y > 0)
			if (X > 0)
				return atan((irr::f64)Y/(irr::f64)X) * RADTODEG64;
			else
				return 180.0-atan((irr::f64)Y/-(irr::f64)X) * RADTODEG64;
		else
			if (X > 0)
				return 360.0-atan(-(irr::f64)Y/(irr::f64)X) * RADTODEG64;
			else
				return 180.0+atan(-(irr::f64)Y/-(irr::f64)X) * RADTODEG64;
	}

	//! Calculates the angle of this vector in degrees in the counter trigonometric sense.
	/** 0 is to the right (3 o'clock), values increase clockwise.
	\return Returns a value between 0 and 360. 
	inline f64 getAngle() const
	{
		if (Y == 0) // corrected thanks to a suggestion by Jox
			return X < 0 ? 180 : 0;
		else if (X == 0)
			return Y < 0 ? 90 : 270;

		// don't use getLength here to avoid precision loss with s32 vectors
		// avoid floating-point trouble as sqrt(y*y) is occasionally larger than y, so clamp
		const f64 tmp = core::clamp(Y / sqrt((f64)(X*X + Y*Y)), -1.0, 1.0);
		const f64 angle = atan( core::squareroot(1 - tmp*tmp) / tmp) * RADTODEG64;

		if (X>0 && Y>0)
			return angle + 270;
		else
		if (X>0 && Y<0)
			return angle + 90;
		else
		if (X<0 && Y<0)
			return 90 - angle;
		else
		if (X<0 && Y>0)
			return 270 - angle;

		return angle;
	}

	//! Calculates the angle between this vector and another one in degree.
	/** \param b Other vector to test with.
	\return Returns a value between 0 and 90. 
	inline f64 getAngleWith(const vector2d<T>& b) const
	{
		f64 tmp = (f64)(X*b.X + Y*b.Y);

		if (tmp == 0.0)
			return 90.0;

		tmp = tmp / core::squareroot((f64)((X*X + Y*Y) * (b.X*b.X + b.Y*b.Y)));
		if (tmp < 0.0)
			tmp = -tmp;
		if ( tmp > 1.0 ) //   avoid floating-point trouble
			tmp = 1.0;

		return atan(sqrt(1 - tmp*tmp) / tmp) * RADTODEG64;
	}

	//! Returns if this vector interpreted as a point is on a line between two other points.
	/** It is assumed that the point is on the line.
	\param begin Beginning vector to compare between.
	\param end Ending vector to compare between.
	\return True if this vector is between begin and end, false if not. 
	bool isBetweenPoints(const vector2d<T>& begin, const vector2d<T>& end) const
	{
		if (begin.X != end.X)
		{
			return ((begin.X <= X && X <= end.X) ||
				(begin.X >= X && X >= end.X));
		}
		else
		{
			return ((begin.Y <= Y && Y <= end.Y) ||
				(begin.Y >= Y && Y >= end.Y));
		}
	}

	//! Creates an interpolated vector between this vector and another vector.
	/** \param other The other vector to interpolate with.
	\param d Interpolation value between 0.0f (all the other vector) and 1.0f (all this vector).
	Note that this is the opposite direction of interpolation to getInterpolated_quadratic()
	\return An interpolated vector.  This vector is not modified. 
	vector2d<T> getInterpolated(const vector2d<T>& other, f64 d) const
	{
		f64 inv = 1.0f - d;
		return vector2d<T>((T)(other.X*inv + X*d), (T)(other.Y*inv + Y*d));
	}

	//! Creates a quadratically interpolated vector between this and two other vectors.
	/** \param v2 Second vector to interpolate with.
	\param v3 Third vector to interpolate with (maximum at 1.0f)
	\param d Interpolation value between 0.0f (all this vector) and 1.0f (all the 3rd vector).
	Note that this is the opposite direction of interpolation to getInterpolated() and interpolate()
	\return An interpolated vector. This vector is not modified. 
	vector2d<T> getInterpolated_quadratic(const vector2d<T>& v2, const vector2d<T>& v3, f64 d) const
	{
		// this*(1-d)*(1-d) + 2 * v2 * (1-d) + v3 * d * d;
		const f64 inv = 1.0f - d;
		const f64 mul0 = inv * inv;
		const f64 mul1 = 2.0f * d * inv;
		const f64 mul2 = d * d;

		return vector2d<T> ( (T)(X * mul0 + v2.X * mul1 + v3.X * mul2),
					(T)(Y * mul0 + v2.Y * mul1 + v3.Y * mul2));
	}

	//! Sets this vector to the linearly interpolated vector between a and b.
	/** \param a first vector to interpolate with, maximum at 1.0f
	\param b second vector to interpolate with, maximum at 0.0f
	\param d Interpolation value between 0.0f (all vector b) and 1.0f (all vector a)
	Note that this is the opposite direction of interpolation to getInterpolated_quadratic()
	
	vector2d<T>& interpolate(const vector2d<T>& a, const vector2d<T>& b, f64 d)
	{
		X = (T)((f64)b.X + ( ( a.X - b.X ) * d ));
		Y = (T)((f64)b.Y + ( ( a.Y - b.Y ) * d ));
		return *this;
	}

	//! X coordinate of vector.
	T X;

	//! Y coordinate of vector.
	T Y;
};

	//! Typedef for f32 2d vector.
	typedef vector2d<f32> vector2df;

	//! Typedef for integer 2d vector.
	typedef vector2d<s32> vector2di;

	template<class S, class T>
	vector2d<T> operator*(const S scalar, const vector2d<T>& vector) { return vector*scalar; }

	// These methods are declared in dimension2d, but need definitions of vector2d
	template<class T>
	dimension2d<T>::dimension2d(const vector2d<T>& other) : Width(other.X), Height(other.Y) { }

	template<class T>
	bool dimension2d<T>::operator==(const vector2d<T>& other) const { return Width == other.X && Height == other.Y; }

} // end namespace core
} // end namespace irr

#endif

*/