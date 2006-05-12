#ifndef _hull_weapon_rocket_heavy_h_
#define _hull_weapon_rocket_heavy_h_

#include "hull_weapon.h"
#include "bitmap.h"

class SpaceObject;

/*
 * HeavyRocket
 *
 * giant rocket that should cuase significant damage to all who get in its path
 *
 */

class HeavyRocket_WHull:public HullWeapon{
public:

	HeavyRocket_WHull();
	virtual void Draw( const Bitmap & who, int x, int y );
	virtual bool Collide( int mx, int my, SpaceObject * check );

};

#endif
