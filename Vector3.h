#ifndef VECTOR3_H
#define VECTOR3_H
#include <cmath>

struct Vector3;

// ************************************************************************************
// Anonymous namespace - helper functions local to the Vector3 structure
// 
//
// ************************************************************************************
//
namespace
{
	// Epsilon value for floating point equality testing
	//
	double Epsilon = 1.0E+6;

	// Generic integer Point2D class encourages Vector3
	// structures to be used as points
	//
	struct Point2D {int x, y; Point2D(){} Point2D(int x, int y):x(x),y(y){}};

	// Called from class members
	//
	Point2D vec_to_point2d (Vector3 const& v);
	bool is_equal (Vector3 const& l, Vector3 const& r);
}


// ************************************************************************************
// Vec namespace - External functions for operating on a Vector3 structure
//
//
// ************************************************************************************
//
namespace Vec
{
	// Magnitude squared for more efficient lenth comparisons
	//
	double MagSq (Vector3 const& v);

	// Magnitude of a vector
	//
	double Mag (Vector3 const& v);

	// Distance squared for two Vector3 objects
	//
	double DistanceSq (Vector3 const& l, Vector3 const& r);

	// Distance between two Vector3 objects
	//
	double Distance (Vector3 const& l, Vector3 const& r);

	// The dot product of two vectors
	//
	double Dot (Vector3 const& l, Vector3 const& r);

	// The cross product of two vectors
	//
	Vector3 Cross (Vector3 const& l, Vector3 const& r);

	// The zero vector
	//
	Vector3 Zero ();

	// Returns a normalized vector
	//
	Vector3 Unit (Vector3 const& v);

	// The unsigned area of the parallelogram formed by
	// two vectors. This is really the magnitude of the
	// cross product.
	//
	double Area (Vector3 const& l, Vector3 const& r);
}


// ************************************************************************************
// Vector3 structure
//
//
// ************************************************************************************
//
struct Vector3
{
	double x, y, z;

	// Constructors
	//
	Vector3 (){}
	Vector3 (Vector3 const& v) : x(v.x), y(v.y), z(v.z) {}
	Vector3 (double x, double y, double z) : x(x), y(y), z(z) {}
	~Vector3 (){}

	// Operators
	//
	// non-const
	Vector3& operator= (Vector3 const& v) {x=v.x; y=v.y; z=v.z; return *this;}
	Vector3& operator*= (double s) {x=s*x, y=s*y; z=s*z; return *this;}
	Vector3& operator/= (double s) {double t=1.0/s; x*=t; y*=t; z*=t; return *this;}
	Vector3& operator+= (Vector3 const& v) {x+=v.x; y+=v.y; z+=v.z; return *this;}
	Vector3& operator-= (Vector3 const& v) {x-=v.x; y-=v.y; z-=v.z; return *this;}
	// const
	Vector3 operator* (double s) const {Vector3 w(*this); w*=s; return w;}
	Vector3 operator/ (double s) const {Vector3 w(*this); w/=s; return w;}
	Vector3 operator+ (Vector3 const& v) const {Vector3 w(*this); w+=v; return w;}
	Vector3 operator- (Vector3 const& v) const {Vector3 w(*this); w-=v; return w;}
	Vector3 operator- () const {Vector3 w(*this); w*=-1.0; return w;}
	double operator* (Vector3 const& v) const {return x*v.x + y*v.y + z*v.z;} // dot
	bool operator== (Vector3 const& v) const {return this==&v || is_equal (*this, v);}
	bool operator!= (Vector3 const& v) const {return !(*this == v);}
	operator Point2D () const {return vec_to_point2d (*this);}
	
	// Vector length (magnitude)
	//
	double LengthSq () const {return x*x + y*y + z*z;}
	double Length () const {return sqrt (LengthSq ());}

	// Converts this vector into a unit vector (returns the previous length)
	//
	double Normalize () {double m = sqrt (x*x+y*y+z*z); double mi = 1.0/m; x*=mi; y*=mi; z*=mi; return m;}

	// Converts this vector to the zero vector
	//
	void Zero () {x=y=z=0.0;}
};

// External operators for Vector3
//
inline
Vector3 operator* (double f, Vector3 const& v) {
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
	// External vector functions
	//
	inline double MagSq (Vector3 const& v) {return v.LengthSq ();}
	inline double Mag (Vector3 const& v) {return v.Length ();}
	inline double DistanceSq (Vector3 const& l, Vector3 const& r) {return MagSq (l-r);}
	inline double Distance (Vector3 const& l, Vector3 const& r) {return Mag (l-r);}
	inline double Dot (Vector3 const& l, Vector3 const& r) {return l * r;}
	inline Vector3 Cross (Vector3 const& l, Vector3 const& r) {return Vector3 (l.y*r.z - l.z*r.y, l.z*r.x - l.x*r.z, l.x*r.y - l.y*r.x);}
	inline Vector3 Zero () {return Vector3 (0.0, 0.0, 0.0);}
	inline Vector3 Unit (Vector3 const& v) {Vector3 r(v); r.Normalize (); return r;}
	inline double Area (Vector3 const& l, Vector3 const& r) {return Mag (Cross (l, r));}
}


// ************************************************************************************
// Anonymous namespace
//
//
// ************************************************************************************
//
namespace
{
	// Helper functions
	//
	inline int round (double f) {
		return int (f + 0.5); }

	inline bool is_equal (Vector3 const& l, Vector3 const& r) {
		return ((abs(l.x-r.x) < Epsilon) && (abs(l.y-r.y) < Epsilon) && (abs(l.z-r.z) < Epsilon)); }

	inline Point2D vec_to_point2d (Vector3 const& v) {
		return Point2D (round (v.x), round (v.y)); }
}

#endif // VECTOR3_H