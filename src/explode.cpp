#include "defs.h"
#include "explode.h"
#include "bitmap.h"

int last_explode = 0;

ExplosionClass::ExplosionClass( int cx, int cy, double walkx, double walky, int rad ):
x( cx ),
y( cy ),
vx( cx ),
vy( cy ),
wx( walkx ),
wy( walky ),
radius( rad ),
max_rad( rad ){}

bool ExplosionClass::update() {
	vx += wx;
	vy += wy;
	x = (int)vx;
	y = (int)vy;

	radius--;
	if ( radius <= 0 ) return true;
	return false;
}


void ExplosionClass::Draw( Bitmap * who, int offset ) {

	int color = Util::e_color[(int)((double)radius / (double)max_rad * (double)(MAX_E_COLOR-1))];
	who->circleFill( x, y+offset, radius, color );
}


void addExplode( ExplosionClass ** explode_array, int MAX_EXPL_ARRAY, ExplosionClass * who ) {
	if ( explode_array == NULL ) {
		delete who;
		return;
	}

	if ( last_explode >= MAX_EXPL_ARRAY ){
		last_explode = 0;
	}

	if ( explode_array[ last_explode ] != NULL )
		delete explode_array[ last_explode ];
	explode_array[ last_explode ] = who;
	last_explode = (last_explode+1) % MAX_EXPL_ARRAY;

}
