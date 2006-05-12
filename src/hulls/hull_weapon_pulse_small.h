#ifndef _hull_weapon_pulse_small_h_
#define _hull_weapon_pulse_small_h_

#include "hull_weapon.h"
#include "bitmap.h"

/*
 * SmallPulse
 *
 * this sucks, i have to change it soon.
 *
 */

class SmallPulse_WHull:public HullWeapon{
public:

	SmallPulse_WHull();
	virtual void Draw( const Bitmap & who, int x, int y );

};

#endif
