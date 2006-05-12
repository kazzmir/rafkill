#include "trigtable.h"
#include "defs.h"
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/*
double tcos[360];
double tsine[360];
double rsine[360];
double ttan[360];
*/

double tsqr( const double r ) {
	return r*r;
}


long int tcube( const long int c ) {
	return c*c*c;
}


double fsqr( double r ) {
	return r*r;
}


double fcube( double r ) {
	return r*r*r;
}


double tsqrt( const double q ) {

	return sqrt( q );

	if ( q <= 0 )
		return 0;

	long int min = 0;

	while ( tsqr( min ) < q )
		min += 30;

	while ( tsqr( min ) > q )
		min -= 10;

	while ( tsqr( min ) < q )
		min++;

	if ( tsqr( min ) > q )
		min--;
	return min;

}


double dist( const int x1, const int y1, const int x2, const int y2 ) {

	double a = tsqr( y1 - y2 );
	double b = tsqr( x1 - x2 );

	return tsqrt( a + b );

}

double zdist( int x, int y, int x1, int y1 ) {

	double a = tsqr(x-x1);
	double b = tsqr(y-y1);
	return sqrt( a+b );
}


long int area( int x1, int y1, int x2, int y2, int x3, int y3 ) {
	double d1 = zdist(x1,y1,x2,y2);
	double d2 = zdist(x1,y1,x3,y3);
	double d3 = zdist(x2,y2,x3,y3);
	double s = ( d1 + d2 + d3 ) / 2.0;
	// area = sqrt( s * (s-d1) * (s-d2) * (s-d3) )
	long int atotal = (long int)(sqrt(s*(s-d1)) * sqrt((s-d2)*(s-d3)));
	return atotal;
}


bool ptriangle( int tx1, int ty1, int tx2, int ty2, int tx3, int ty3, int x1, int y1 ) {
	long int atotal = area( tx1, ty1, tx2, ty2, tx3, ty3 )+2;
	long int a1 = area( tx1, ty1, tx2, ty2, x1, y1 );
	if ( a1 > atotal ) return false;
	long int a2 = area( tx1, ty1, tx3, ty3, x1, y1 );
	if ( a2 > atotal ) return false;
	long int a3 = area( tx2, ty2, tx3, ty3, x1, y1 );
	if ( a3 > atotal ) return false;
	if ( a1+a2+a3 > atotal )
		return false;
	return true;
}


bool prect( int px1, int py1, int x1, int y1, int x2, int y2 ) {

	if ( px1 >= x1 && px1 <= x2 && py1 >= y1 && py1 <= y2 )
		return true;
	return false;
}

/*
int sarctan( const double tr ) {

	if ( tr == 0.0 )
		return 0;
	int my_ang = 0;
	double precision = fabs(ttan[0] - tr );
	for ( int r = 1; r < 180; r++ ) {

		double dif = fabs( ttan[r] - tr );
		if ( dif == 0 )
			return r;

		if ( dif < precision ) {
			precision = dif;
			my_ang = r;

		}

	}
	return my_ang;

}
*/

/*
int barctan( const double tr ) {

	int my_ang = 180;
	double precision = fabs(ttan[180] - tr );
	for ( int r = 181; r < 360; r++ ) {

		double dif = fabs( ttan[r] - tr );
		if ( dif <= precision ) {
			precision = dif;
			my_ang = r;

		}

	}
	return my_ang;

}
*/


int lineIntersect( int ax, int ay, int bx, int by, int cx, int cy, int dx, int dy, int *ix, int *iy ) {
	float r, s;
	float denom = (bx-ax)*(dy-cy)-(by-ay)*(dx-cx);

	r = (float)((ay-cy)*(dx-cx)-(ax-cx)*(dy-cy))/denom;
	s = (float)((ay-cy)*(bx-ax)-(ax-cx)*(by-ay))/denom;

	if ( r < 0.0 || s < 0.0 || r > 1.0 || s > 1.0 )
		return 0;

	*ix=ax+(int)(r*(float)(bx-ax)+0.5);
	*iy=ay+(int)(r*(float)(by-ay)+0.5);

	return 1;

}						  // end lineIntersect

/* nicer name for gang */
int getAngle( int x1, int y1, int x2, int y2 ){
	return gang( x1, y1, x2, y2 );
}

int gang( int x1, int y1, int x2, int y2 ) {

	int tang = 0;
	if ( x1 == x2 ) {
		if ( y1 < y2 )
			tang = 90;
		else
			tang = 270;
	}
	if ( y1 == y2 ) {

		if ( x1 < x2 )
			tang = 0;
		else
			tang = 180;

	} else
	tang = (int)(0.5+atan2( (double) -(y2-y1), (double) (x2 - x1) ) * 180.0 / M_PI );

	while ( tang < 0 )
		tang += 360;
	return tang % 360;

}


int arcsine( double x ) {

	int tang = (int)(0.5 + asin( x * 180.0 / M_PI) );
	while ( tang < 0 )
		tang += 360;
	return tang % 360;

}


/*
int find_sin_pos( double q, bool side )
{

   double low = 9999;
   int keep;
   for ( int x = side*90; x <= side*90+90; x++ )
   {

      if ( fabs(tsine[x]-q) < low )
      {
low = fabs(tsine[x]-q);
keep = x;
}

}
return keep;

}

int find_sin_neg( double q, bool side )
{

double low = 9999;
int keep;
for ( int x = side*90+180; x < side*90+270; x++ )
{

if ( fabs(tsine[x]-q) < low )
{
low = fabs(tsine[x]-q);
keep = x;
}

}
return keep;

}

int mang( int x1, int y1, int x2, int y2 )
{

if ( x1 == x2 )return 0;
if ( y1 == y2 )return 0;

int t1 = dist( x1, y1, x2, y2 );
if ( y2 > y1 )
{
double cr = (double)t1 / (double)( y2 - y1 );
return find_sin_pos( cr, x1>x2 );
}
else
{
double cr = (double)t1 / (double)( y1 - y2 );
return find_sin_neg( cr, x1>x2 );
}

}
*/

/*
void set_trig() {
	for ( int r = 0; r<360; r++ ) {

		tcos[ r ] = cos( (double)(r) * AL_PI / 180.0 );
		tsine[ r ] = -sin( (double)(r) * AL_PI / 180.0 );
		rsine[ r ] = sin( (double)(r) * AL_PI / 180.0 );

		if ( tcos[r] == 0.0 )
			ttan[r] = 99999.0;
		else
			ttan[ r ] = tsine[r] / tcos[r];

	}
}
*/
