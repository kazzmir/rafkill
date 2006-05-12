#include "defs.h"
#include "explode.h"
#include "explode_animate.h"
#include "raptor.h"
#include "bitmap.h"

ExplosionAnimate::ExplosionAnimate( int cx, int cy, double dx, double dy, int _first_pic, int _last_pic ):
ExplosionClass( cx, cy, dx, dy, 99 ) {
	first_pic = _first_pic;
	radius = first_pic;
	last_pic = _last_pic;
}


bool ExplosionAnimate::update() {
	vx += wx;
	vy += wy;
	x = (int)vx;
	y = (int)vy;

	if ( ++radius > last_pic ) return true;
	return false;
}


void ExplosionAnimate::Draw( Bitmap * who, int offset ) {
	Bitmap frame = Util::getDataSprite( radius );
	int mx = frame.getWidth() / 2;
	int my = frame.getHeight() / 2;
	// draw_sprite( who, (BITMAP *)global_data[ radius ].dat, x-mx, y-my+offset );
	// Bitmap c( (BITMAP *)Util::global_data[ radius ].dat );
	// who->draw( 
	frame.draw( x-mx, y-my+offset, *who );
}
