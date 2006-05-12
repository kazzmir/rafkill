#ifndef _hull_weapon_rocket_normal_h_
#define _hull_weapon_rocket_normal_h_

#include "hull_weapon.h"
#include "bitmap.h"

class SpaceObject;

/*
 * NormalRocket
 *
 * normal sized rocket that cuases significant damage
 *
 */

class NormalRocket_WHull:public HullWeapon{
public:
	NormalRocket_WHull();
	virtual void Draw( const Bitmap & who, int x, int y );
	virtual bool Collide( int mx, int my, SpaceObject * check );
};

#endif
