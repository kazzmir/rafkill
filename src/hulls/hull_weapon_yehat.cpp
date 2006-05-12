#include "hull_weapon.h"
#include "bitmap.h"
#include "hull_weapon_yehat.h"
#include "ebox.h"

Yehat_WHull::Yehat_WHull( int str ):
HullWeapon( 0, 1, str ) {
	strength = str;

	collide = new ECollide( 2, 2 );
	/*
	collide = new ECollide();
	collide->setXS( 1 );
	collide->setYS( 1 );
	collide->my_size = 2;
	EBox * arch = new EBox( 0, 0, 2, 2 );
	collide->add( arch );
	collide->finalize();
	*/
}


void Yehat_WHull::Draw( const Bitmap & who, int x, int y ) {

	int str = (int)strength;
	
	int col = 150+str<255?150+str:255;
	col = str*5<255?str*5:255;
	// circlefill( who, x, y, 2, makecol(250,col,str%255) );
    	who.circleFill( x, y, 2, Bitmap::makeColor(250,col,str%255) );
}
