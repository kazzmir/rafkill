#ifndef _hull_weapon_straight_large_h_
#define _hull_weapon_straight_large_h_

#include "hull_weapon.h"
#include "bitmap.h"
class SpaceObject;

class SL_WHull:public HullWeapon{
public:
	SL_WHull();

	virtual void Draw( const Bitmap & who, int x, int y );
	virtual bool Collide( int mx, int my, SpaceObject * check );

	int r1, r2;
};

#endif
