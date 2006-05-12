#ifndef _hull_weapon_shatter_h_
#define _hull_weapon_shatter_h_

#include "hull_weapon.h"
#include "spaceobj.h"
#include "bitmap.h"


/*
 *
 * Shatter
 *
 * big red ball that will eventually shatter
 *
 */

class Shatter_WHull:public HullWeapon{
public:

	Shatter_WHull( int str );
	virtual void Draw( const Bitmap & who, int x, int y );
	virtual bool Collide( int mx, int my, SpaceObject * check );

};

#endif
