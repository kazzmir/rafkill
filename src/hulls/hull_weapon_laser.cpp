#include "defs.h"
#include "spaceobj.h"
#include "hull_weapon.h"
#include "hull_weapon_laser.h"
#include "ebox.h"

static const int LASER_DIST = 4;

Laser_WHull::Laser_WHull( int str ):
HullWeapon( 0, 1, 1 ) {
	shade = new int[ LASER_DIST ];
	switch( str ) {
		case 0  : {
			life = 21;
			strength = 3;
			color = Bitmap::makeColor( 0,240,130 );
			break;
		}
		case 1  : {
			life = 21;
			strength = 6;
			color = Bitmap::makeColor( 250,120,50 );
			break;
		}
	}
	Util::blend_palette( shade, LASER_DIST, color, Bitmap::makeColor( 255, 255, 255 ) );

	int length = getLife() * 3 / 2;
	collide = new ECollide( LASER_DIST * 2, length );

	// Bitmap = create_bitmap(1,1);
	myBitmap = new Bitmap();
	drawSelf();
}
	
void Laser_WHull::Collided(){
	
	int length = getLife() * 3 / 2;
	delete collide;
	collide = new ECollide( LASER_DIST * 2, length );

	drawSelf();
}

/*
bool Laser_WHull::Collide( int mx, int my, SpaceObject * check ) {
	for ( int qy = my; qy <= my + GetLife() * 3/2; qy+=5 )
		for ( int qx = mx - LASER_DIST; qx <= mx+LASER_DIST; qx += 3 )
			if ( check->HitMe( qx, qy ) )
				return true;
	return false;
}
*/

void Laser_WHull::drawSelf(){

	int length = getLife() * 3 / 2;
	if ( length < 1 ){
		length = 1;
	}
	
	// destroy_bitmap( Bitmap );
	delete myBitmap;
	// Bitmap = create_bitmap( LASER_DIST*2, length );
	myBitmap = new Bitmap( LASER_DIST*2, length );

	/*
	int x1 = x-LASER_DIST;
	int y1 = y - length/2;
	int x2 = x+LASER_DIST;
	int y2 = y + length/2;
	*/

	int x1 = 0;
	int x2 = LASER_DIST*2-1;
	int y1 = 0;
	int y2 = length;

	myBitmap->rectangleFill( x1, y1+1, x2, y2-1, shade[0] );

	for ( int q = 1; q < LASER_DIST; q++ )
		myBitmap->rectangleFill( x1+q, y1, x2-q, y2, shade[q] );

	/*
	rectfill( Bitmap, x1, y1+1, x2, y2-1, shade[0] );

	for ( int q = 1; q < LASER_DIST; q++ )
		rectfill( Bitmap, x1+q, y1, x2-q, y2, shade[q] );
	*/

}

/*
void Laser_WHull::Draw( BITMAP * who, int x, int y ) {

	int length = getLife() * 3 / 2;

	int x1 = x-LASER_DIST;
	int y1 = y - length/2;
	int x2 = x+LASER_DIST;
	int y2 = y + length/2;

	rectfill( who, x1, y1+1, x2, y2-1, shade[0] );

	for ( int q = 1; q < LASER_DIST; q++ )
		rectfill( who, x1+q, y1, x2-q, y2, shade[q] );

	// collide->draw( who, x-LASER_DIST, y - length / 2 );

}
*/


Laser_WHull::~Laser_WHull() {
	delete[] shade;
	delete collide;
}
