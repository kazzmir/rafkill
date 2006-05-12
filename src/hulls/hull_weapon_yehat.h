#ifndef _hull_weapon_yellow_h
#define _hull_weapon_yellow_h

#include "hull_weapon.h"
#include "bitmap.h"

class Yehat_WHull: public HullWeapon{
public:

	Yehat_WHull( int str );
	virtual void Draw( const Bitmap & who, int x, int y );
	
};

#endif
