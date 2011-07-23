#ifndef VECTOR3_H
#define VECTOR3_H

#ifndef _USE_MATH_DEFINES
	#define _USE_MATH_DEFINES
	#include <cmath> // standard library math functions
	#undef _USE_MATH_DEFINES
#else
	#include <cmath> //
#endif

#ifndef FLOAT_TYPE
	#define FLOAT_TYPE_DEFINED
	#define FLOAT_TYPE double
#endif

#ifndef FLOAT_EPSILON
	#define FLOAT_EPSILON_DEFINED
	#define FLOAT_EPSILON 1.0E-6
#endif

struct Vector3;

// ************************************************************************************
// Vec namespace - External and helper functions for Vector3.
// 
//
// ************************************************************************************
//
namespace Vec
{
	// Epsilon value for floating point equality testing.
	//
	const FLOAT_TYPE Epsilon = (FLOAT_TYPE) FLOAT_EPSILON;
	const FLOAT_TYPE One = (FLOAT_TYPE) 1.0;

	// Generic integer Point2D class encourages Vector3
	// structures to be used as points.
	//
	struct Point2D {int x, y; Point2D(){} Point2D(int x, int y):x(x),y(y){}};

	// Called from class members.
	//
	Point2D to_point2d (Vector3 const& v);
	bool is_equal (Vector3 const& l, Vector3 const& r);

	// Magnitude squared for more efficient lenth comparisons.
	//
	FLOAT_TYPE MagSq (Vector3 const& v);

	// Magnitude of a vector.
	//
	FLOAT_TYPE Mag (Vector3 const& v);

	// Distance squared for two Vector3 objects.
	//
	FLOAT_TYPE DistanceSq (Vector3 const& l, Vector3 const& r);

	// Distance between two Vector3 objects.
	//
	FLOAT_TYPE Distance (Vector3 const& l, Vector3 const& r);

	// The dot product of two vectors.
	//
	FLOAT_TYPE Dot (Vector3 const& l, Vector3 const& r);

	// The cross product of two vectors.
	//
	Vector3 Cross (Vector3 const& l, Vector3 const& r);

	// The zero vector.
	//
	Vector3 Zero ();

	// Returns a normalized vector.
	//
	Vector3 Unit (Vector3 const& v);

	// The unsigned area of the parallelogram formed by
	// two vectors. This is really the magnitude of the
	// cross product.
	//
	FLOAT_TYPE Area (Vector3 const& l, Vector3 const& r);
}


// ************************************************************************************
// Vector3 structure
//
//
// ************************************************************************************
//
struct Vector3
{
	FLOAT_TYPE x, y, z;

	// Constructors.
	//
	Vector3 (){}
	explicit Vector3 (FLOAT_TYPE f) : x(f), y(f), z(f) {}
	Vector3 (Vector3 const& v) : x(v.x), y(v.y), z(v.z) {}
	Vector3 (FLOAT_TYPE x, FLOAT_TYPE y, FLOAT_TYPE z) : x(x), y(y), z(z) {}
	~Vector3 (){}

	// Operators.
	//
	// Non-constant.
	//
	Vector3& operator= (Vector3 const& v) {x=v.x; y=v.y; z=v.z; return *this;}
	Vector3& operator*= (FLOAT_TYPE s) {x=s*x, y=s*y; z=s*z; return *this;}
	Vector3& operator/= (FLOAT_TYPE s) {FLOAT_TYPE t=Vec::One/s; x*=t; y*=t; z*=t; return *this;}
	Vector3& operator+= (Vector3 const& v) {x+=v.x; y+=v.y; z+=v.z; return *this;}
	Vector3& operator-= (Vector3 const& v) {x-=v.x; y-=v.y; z-=v.z; return *this;}

	// Constant.
	//
	Vector3 operator* (FLOAT_TYPE s) const {Vector3 w(*this); w*=s; return w;}
	Vector3 operator/ (FLOAT_TYPE s) const {Vector3 w(*this); w/=s; return w;}
	Vector3 operator+ (Vector3 const& v) const {Vector3 w(*this); w+=v; return w;}
	Vector3 operator- (Vector3 const& v) const {Vector3 w(*this); w-=v; return w;}
	Vector3 operator- () const {Vector3 w(*this); w*=-1.0; return w;}
	FLOAT_TYPE operator* (Vector3 const& v) const {return x*v.x + y*v.y + z*v.z;} // dot
	bool operator== (Vector3 const& v) const {return this==&v || Vec::is_equal (*this, v);}
	bool operator!= (Vector3 const& v) const {return !(*this == v);}
	operator Vec::Point2D () const {return Vec::to_point2d (*this);}
	
	// Vector length (magnitude).
	//
	FLOAT_TYPE LengthSq () const {return x*x + y*y + z*z;}
	FLOAT_TYPE Length () const {return sqrt (LengthSq ());}

	// Converts this vector into a unit vector (returns the previous length).
	//
	FLOAT_TYPE Normalize () {FLOAT_TYPE m = sqrt (x*x+y*y+z*z); FLOAT_TYPE mi = Vec::One/m; x*=mi; y*=mi; z*=mi; return m;}

	// Converts this vector to the zero vector.
	//
	void Zero () {x=y=z=0.0;}
};

// External operators for Vector3.
//
inline
Vector3 operator* (FLOAT_TYPE f, Vector3 const& v) {
	return Vector3 (f*v.x, f*v.y, f*v.z);
}


// ************************************************************************************
// Vec namespace
//
//
// ************************************************************************************
//
namespace Vec
{
	// External vector functions.
	//
	inline FLOAT_TYPE MagSq (Vector3 const& v) {return v.LengthSq ();}
	inline FLOAT_TYPE Mag (Vector3 const& v) {return v.Length ();}
	inline FLOAT_TYPE DistanceSq (Vector3 const& l, Vector3 const& r) {return MagSq (l-r);}
	inline FLOAT_TYPE Distance (Vector3 const& l, Vector3 const& r) {return Mag (l-r);}
	inline FLOAT_TYPE Dot (Vector3 const& l, Vector3 const& r) {return l * r;}
	inline Vector3 Cross (Vector3 const& l, Vector3 const& r) {return Vector3 (l.y*r.z - l.z*r.y, l.z*r.x - l.x*r.z, l.x*r.y - l.y*r.x);}
	inline Vector3 Zero () {return Vector3 (0.0);}
	inline Vector3 Unit (Vector3 const& v) {Vector3 r(v); r.Normalize (); return r;}
	inline FLOAT_TYPE Area (Vector3 const& l, Vector3 const& r) {return Mag (Cross (l, r));}
}


// ************************************************************************************
// Vec namespace
//
//
// ************************************************************************************
//
namespace Vec
{
	// Helper functions.
	//
	inline int round (FLOAT_TYPE f) {
		return int ((f < 0.0) ? (f - 0.5) : (f + 0.5)); }

	inline bool is_equal (Vector3 const& l, Vector3 const& r) {
		return ((abs(l.x-r.x) < Vec::Epsilon) && (abs(l.y-r.y) < Vec::Epsilon) && (abs(l.z-r.z) < Vec::Epsilon)); }

	inline Point2D Vec::to_point2d (Vector3 const& v) {
		return Vec::Point2D (Vec::round (v.x), Vec::round (v.y)); }
}

#ifdef FLOAT_TYPE_DEFINED
	#undef FLOAT_TYPE
	#undef FLOAT_TYPE_DEFINED
#endif

#ifdef FLOAT_EPSILON_DEFINED
	#undef FLOAT_EPSILON
	#undef FLOAT_EPSILON_DIFINED
#endif

#endif // VECTOR3_H