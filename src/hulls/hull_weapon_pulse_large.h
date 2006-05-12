#ifndef _hull_weapon_pulse_large_h_
#define _hull_weapon_pulse_large_h_

#include "hull_weapon.h"
#include "bitmap.h"

class SpaceObject;

/*
 * LargePulse
 *
 * bullet that has streams of plasma coming off the back
 *
 */

class LargePulse_WHull:public HullWeapon{
public:

	LargePulse_WHull();
	virtual void Draw( const Bitmap & who, int x, int y );
	virtual bool Collide( int mx, int my, SpaceObject * check );

};

#endif
