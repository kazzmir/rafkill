#include "defs.h"
#include "hull_weapon.h"
#include "hull_weapon_chain.h"
#include "spaceobj.h"
#include "trigtable.h"
#include "ebox.h"
#include "raptor.h"
#include "bitmap.h"

Chain_WHull::Chain_WHull( Bitmap * _pics, int str, int power, int ang, int len, ECollide * ec ):
HullWeapon( 0, 1, str ) {

	myBitmap = _pics;

	life = 1;
	strength = power/5;
	angle = ang;
	length = len;
	collide = ec;

}

Chain_WHull::~Chain_WHull() {
	delete collide;
}

void Chain_WHull::Draw( const Bitmap & who, int x, int y ) {
	if ( myBitmap == NULL ) return;

	const int max_link = 9;

	// int mx = x + getWidth() / 2;
	// int my = y + getHeight() / 2;
	
	int mx = x;
	int my = y;
	Bitmap linkCircle = Util::getDataSprite( CHAIN_LINK_CIRCLE );
	Bitmap link = Util::getDataSprite( CHAIN_LINK_LINK );

	for (int q = 0; q < max_link; q++ ) {

		double ds = (double)length / max_link;
		double fn = ds * (double)q;

		double lx = mx + Tcos( angle ) * fn;
		double ly = my + Tsine( angle ) * fn;

		linkCircle.draw( (int) lx, (int) ly, who );

		lx += Tcos( angle ) * ds / 2.0;
		ly += Tsine( angle ) * ds / 2.0;

		link.drawRotate( (int) lx, (int) ly, angle + 90, who );

	}

	HullObject::Draw( who, x, y );
}
