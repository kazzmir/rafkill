#ifndef _hull_weapon_beam_h
#define _hull_weapon_beam_h

#include "bitmap.h"
#include "hull_weapon.h"

/*
 * Beam
 *
 * just another simple hull that looks like a line
 *
 */

class Beam_WHull:public HullWeapon{
public:

	Beam_WHull( double str, int xf, int yf, int ang );
	virtual void Draw( const Bitmap & who, int x, int y );

	virtual ~Beam_WHull();

protected:

	int count_down;
	int x_size, y_size;
	int shade[6];
	int angle;
	
};

#endif
