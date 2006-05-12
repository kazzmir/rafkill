#ifndef _hull_weapon_massive_h
#define _hull_weapon_massive_h

#include "hull_weapon.h"
#include "bitmap.h"

class ECollide;
class RGBHandle;

class Massive_WHull:public HullWeapon{
public:

	Massive_WHull( int str, int life, ECollide * ecollide );
	virtual void Draw( const Bitmap & who, int x, int y );
	virtual ~Massive_WHull();

protected:

	int side[ 10 ];
	int ang;
	int max_massive;
	RGBHandle * handle;

};

#endif
