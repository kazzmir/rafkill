#ifndef _Vector_h
#define _Vector_h

class Vector{
public:

	Vector();
	Vector( const double xMag, const double yMag );
	Vector( const Vector & copy );

	~Vector();

	inline void setXMagnitude( const double x ){
		xMag = x;
	}

	inline void setYMagnitude( const double y ){
		yMag = y;
	}

	inline const double getXMagnitude() const {
		return xMag;
	}

	inline const double getYMagnitude() const {
		return yMag;
	}

	const Vector & operator+ ( const Vector & lhs, const Vector & rhs );
	const Vector & operator- ( const Vector & lhs, const Vector & rhs );
	Vector & operator= ( const Vector & rhs ){

protected:

	double xMag, yMag;

};

#endif
