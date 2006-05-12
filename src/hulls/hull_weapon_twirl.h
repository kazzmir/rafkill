#ifndef _hull_weapon_twirl_h_
#define _hull_weapon_twirl_h_

#include "hull_weapon.h"
#include "bitmap.h"

class ECollide;

class Twirl_WHull:public HullWeapon{
public:
	Twirl_WHull( const Bitmap & who, ECollide * ec );
	virtual void Draw( const Bitmap & who, int x, int y );

	virtual ~Twirl_WHull();

protected:
	int ang;
	Bitmap bitmap;

};

#endif
