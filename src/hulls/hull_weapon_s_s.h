#ifndef _hull_weapon_straight_small_h_
#define _hull_weapon_straight_small_h_

#include "hull_weapon.h"
#include "bitmap.h"

class SS_WHull:public HullWeapon{
public:
	SS_WHull();
	virtual void Draw( const Bitmap & who, int x, int y );
};

#endif
