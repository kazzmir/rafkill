#ifndef _hull_weapon_fire_h_
#define _hull_weapon_fire_h_

#include "hull_weapon.h"
#include "bitmap.h"

class SpaceObject;

/*
 * Fire
 *
 * looks like a burning bullet
 *
 */

class Fire_WHull:public HullWeapon{
public:
	Fire_WHull();
	virtual void Draw( const Bitmap & who, int x, int y );
	virtual bool Collide( int mx, int my, SpaceObject * check );

};

#endif
