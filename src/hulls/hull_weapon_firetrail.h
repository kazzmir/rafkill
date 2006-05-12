#ifndef _hull_weapon_firetrail_h
#define _hull_weapon_firetrail_h

#include "hull_weapon.h"
#include "bitmap.h"

/*
 * FireTrail
 *
 * supposed to be a trail of flames left over from something else
 *
 */

class FireTrail_WHull:public HullWeapon{
public:

	FireTrail_WHull( int str );
	virtual void Draw( const Bitmap & who, int x, int y );
	virtual bool Collide ( int ax, int ay, SpaceObject * check );

};

#endif
