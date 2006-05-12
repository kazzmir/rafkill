#include "move.h"
#include "move_find.h"
#include "trigtable.h"
#include <math.h>
#include <stdio.h>
#include <deque>

using namespace std;

MoveFind::MoveFind( double _dx, double _dy ):
Move( _dx, _dy ){

	/*
	dx = 0;
	dy = 0;
	*/
	//points.push_back( new XYPoint( screen_x/2, screen_y/2 ) );
	//points.push_back( new XYPoint( 100, 100/*screen_y/3*/ ) );
	//points.push_back( new XYPoint( screen_x-100, screen_y-100 ) );
	//points.push_back( new XYPoint( rnd( screen_x ), rnd( screen_y ) ) );
	for ( int q = 0; q < 5; q++ )
		points.push_back( new XYPoint( Util::rnd( Util::screen_x ), Util::rnd( Util::screen_y / 2 ) ) );
	
}

void MoveFind::action( const vector< SpaceObject * > * fight, int x, int y, double & sdx, double & sdy){

	XYPoint * f = points.front();
	
	if ( dist( x, y, f->x, f->y ) < 15 ){

		points.pop_front();
		points.push_back( f );

	}
	f = points.front();
	int ang = gang( x, y, f->x, f->y );
	double s_dx = o_dx * Tcos(ang);
	double s_dy = o_dy * Tsine(ang);
	
	#define move_fox 0.2

	if ( s_dx + move_fox < sdx ) sdx -= move_fox;
	else if ( s_dx - move_fox > sdx ) sdx += move_fox;
	else sdx = s_dx;

	if ( s_dy + move_fox < sdy ) sdy -= move_fox;
	else if ( s_dy - move_fox > sdy ) sdy += move_fox;
	else sdy = s_dy;

	// return MoveReal();
	
}

MoveFind::~MoveFind(){
	while ( !points.empty() ){
		XYPoint * f = points.front();
		delete f;
		points.pop_front();
	}
}
