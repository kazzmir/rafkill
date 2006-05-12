#ifndef _hull_weapon_light_h_
#define _hull_weapon_light_h_

#include "hull_weapon.h"
#include "bitmap.h"

class Light_WHull:public HullWeapon{
public:
	Light_WHull();
	virtual void Draw( const Bitmap & who, int x, int y );

};

#endif
