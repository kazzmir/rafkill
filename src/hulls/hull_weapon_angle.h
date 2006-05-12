#ifndef _hull_weapon_angle_h
#define _hull_weapon_angle_h

#include "hull_weapon.h"
#include "bitmap.h"

class ECollide;

class Angle_WHull: public HullWeapon{
public:

	Angle_WHull( int str, int _color, ECollide * ec );
	virtual void Draw( const Bitmap & who, int x, int y );
	virtual ~Angle_WHull();

protected:
	int color;
	
};

#endif
