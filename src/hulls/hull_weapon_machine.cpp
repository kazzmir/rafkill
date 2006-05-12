#include "hull_weapon.h"
#include "hull_weapon_machine.h"
#include "ebox.h"
#include "bitmap.h"

Machine_WHull::Machine_WHull( int str ):
HullWeapon( 0, 1, str ) {
	color = Bitmap::makeColor( 180, 20, 74 );
	switch ( str ) {
		case 1  :       color = Bitmap::makeColor(200,200,200); break;
		case 2  :       color = Bitmap::makeColor(40,210,95); break;
		case 3  :       color = Bitmap::makeColor(216,133,242); break;
		default : {
			int r = (int)(strength*10+strength)%255;
			int g = (int)(strength*2+150)%255;
			int b = (int)(strength * 14 + 100 ) % 255;
			color = Bitmap::makeColor(r,g,b);
		}
	}

	collide = new ECollide( 1, 1 );
	/*
	collide = new ECollide();
	collide->setXS( 0 );
	collide->setYS( 0 );
	collide->my_size = 1;
	EBox * arch = new EBox( 0, 0, 1, 1 );
	collide->add( arch );
	collide->finalize();
	*/

}


void Machine_WHull::Draw( const Bitmap & who, int x, int y ) {
	// circlefill( who, x, y, 1, color );
	who.circleFill( x, y, 1, color );
}

Machine_WHull::~Machine_WHull(){
	delete collide;
}
