#ifndef _hull_weapon_rotate_h
#define _hull_weapon_rotate_h

#include "hull_weapon.h"
#include "bitmap.h"

class ECollide;

class Rotate_WHull: public HullWeapon{
public:

	Rotate_WHull( int str, ECollide * ec );
	virtual void Draw( const Bitmap & who, int x, int y );
	virtual ~Rotate_WHull();

};

#endif
