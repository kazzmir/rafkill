#include "hull_weapon.h"
#include "bitmap.h"
#include "hull_weapon_twirl.h"
#include "ebox.h"

Twirl_WHull::Twirl_WHull( const Bitmap & who, ECollide * ec ):
HullWeapon( 0, 1, 3 ) {
	collide = ec;
	ang = 0;
	// *Bitmap = who;
	bitmap = who;
	myBitmap = &bitmap;
}

Twirl_WHull::~Twirl_WHull() {
	delete collide;
	myBitmap = NULL;
}

void Twirl_WHull::Draw( const Bitmap & who, int x, int y ) {

	int mx = myBitmap->getWidth()/2;
	int my = myBitmap->getHeight()/2;

	bitmap.drawRotate( x-mx, y-my, ang, who );
	ang = ( ang + 8 ) % 360;

}
