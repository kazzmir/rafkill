#include "vector.h"

Vector::Vector():
xMag( 0 ),
yMag( 0 ){
}

Vector::Vector( const double _xMag, const double _yMag ):
xMag( _xMag ),
yMag( _yMag ){
}
	
Vector::Vector( const Vector & copy ){
	setXMagnitude( copy.getXMagnitude() );
	setYMagnitude( copy.getYMagnitude() );
}

Vector::~Vector(){
}

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

Vector & Vector::operator= ( const Vector & rhs ){
	this->setXMagnitude( rhs.getXMagnitude() );
	this->setYMagnitude( rhs.getYMagnitude() );
}

const Vector & Vector::operator+ ( const Vector & lhs, const Vector & rhs ){
	Vector v;
	v.setXMagnitude( lhs.getXMagnitude() + rhs.getXMagnitude() );
	v.setXMagnitude( lhs.getYMagnitude() + rhs.getYMagnitude() );
	return v;
}

const Vector & Vector::operator- ( const Vector & lhs, const Vector & rhs ){
	Vector v;
	v.setXMagnitude( lhs.getXMagnitude() - rhs.getXMagnitude() );
	v.setXMagnitude( lhs.getYMagnitude() - rhs.getYMagnitude() );
	return v;
}
