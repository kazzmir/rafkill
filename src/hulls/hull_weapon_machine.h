#ifndef _hull_weapon_machine_h
#define _hull_weapon_machine_h

#include "hull_weapon.h"
#include "bitmap.h"

/*
 * Machine
 *
 * classic machine gun bullet that is featured in Raptor(tm) by epic megagames.
 *
 */

class Machine_WHull: public HullWeapon{
public:

	Machine_WHull( int str );
	virtual void Draw( const Bitmap & who, int x, int y );

	virtual ~Machine_WHull();
	
};

#endif
