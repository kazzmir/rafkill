#ifndef _hull_weapon_mini_missle_h_
#define _hull_weapon_mini_missle_h_

#include "hull_weapon.h"
#include "bitmap.h"

/*
 * Mini
 *
 * minimissle that is featured in Raptor(tm) by epic megagames
 *
 */

class Mini_WHull:public HullWeapon{
public:

	Mini_WHull( );
	virtual void Draw( const Bitmap & who, int x, int y );

private:
	int lx, ly;

};

#endif
