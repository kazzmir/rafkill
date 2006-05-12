#ifndef _hull_weapon_tractor_beam_h
#define _hull_weapon_tractor_beam_h

#include "hull_weapon.h"
#include "bitmap.h"

class ECollide;

class Tractor_WHull: public HullWeapon{
public:

	Tractor_WHull( int str, int _color, ECollide * ec );
	virtual void Draw( const Bitmap & who, int x, int y );
	virtual ~Tractor_WHull();

protected:
	int color;
	
};

#endif
