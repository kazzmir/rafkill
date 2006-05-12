#ifndef _hull_weapon_spread_h
#define _hull_weapon_spread_h

#include "hull_weapon.h"
#include "bitmap.h"

class Spread_WHull: public HullWeapon{
public:

	Spread_WHull( int str );
	virtual void Draw( const Bitmap & who, int x, int y );

protected:
	int ang;
	
};

#endif
