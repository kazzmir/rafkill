#ifndef _TRIGTABLE_H_
#define _TRIGTABLE_H_

#include <math.h>
#include "defs.h"

double tsqr( const double r );
double tsqrt( const double q );
long int tcube( const long int c );
double fsqr( double r );
double fcube( double r );
double dist( int x1, int y1, int x2, int y2 );
double zdist( int x, int y, int x1, int y1 );
long int area( int x1, int y1, int x2, int y2, int x3, int y3 );
bool prect( int px1, int py1, int x1, int y1, int x2, int y2 );
bool ptriangle( int tx1, int ty1, int tx2, int ty2, int tx3, int ty3, int x1, int y1 );
// int sarctan( const double tr );
// int barctan( const double tr );
int lineIntersect( int ax, int ay, int bx, int by, int cx, int cy, int dx, int dy, int *ix, int *iy );
int gang( int x1, int y1, int x2, int y2 );
int getAngle( int x1, int y1, int x2, int y2 );
int arcsine( double x );
// void set_trig();

inline double Tcos( double x ){
	return cos( x * Util::PI / 180.0 );
}

inline double Tsine( double x ){
	return -sin( x * Util::PI / 180.0 );
}

inline double Rsine( double x ){
	return sin( x * Util::PI / 180.0 );
}

inline double Tcos( int x ){
	return Tcos( (double)x );
}

inline double Tsine( int x ){
	return Tsine( (double)x );
}

inline double Rsine( int x ){
	return Rsine( (double)x );
}

/*
extern double tcos[360];
extern double tsine[360];
extern double rsine[360];
extern double ttan[360];
*/

#endif

