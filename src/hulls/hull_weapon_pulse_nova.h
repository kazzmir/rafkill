#ifndef _hull_weapon_pulse_nova_h_
#define _hull_weapon_pulse_nova_h_

#include "hull_weapon.h"
#include "bitmap.h"

class SpaceObject;

/*
 * NovaPulse
 *
 * big green circle of doom
 *
 */

class NovaPulse_WHull:public HullWeapon{
public:

	NovaPulse_WHull();
	
	virtual void Draw( const Bitmap & who, int x, int y );
	virtual bool Collide( int mx, int my, SpaceObject * check );
};

#endif
