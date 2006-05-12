#ifndef _hull_weapon_saber_h
#define _hull_weapon_saber_h

#include "hull_weapon.h"
#include "bitmap.h"

class Saber_WHull:public HullWeapon{
public:

	Saber_WHull( int str, int xf, int yf );
	virtual void Draw( const Bitmap & who, int x, int y );

	virtual ~Saber_WHull();

protected:

	int count_down;
	int x_size, y_size;
	int * shade;
	
};

#endif
