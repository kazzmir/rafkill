#ifndef _hull_weapon_chain_h
#define _hull_weapon_chain_h

#include "hull_weapon.h"
#include "bitmap.h"

/*
 * Chain
 *
 * a spinning iron ball attached by a chain link
 *
 */

class Chain_WHull:public HullWeapon{
public:

	Chain_WHull( Bitmap * _pics, int str, int power, int angle, int length, ECollide * ec );
	virtual void Draw( const Bitmap & who, int x, int y );
	virtual ~Chain_WHull();

protected:

	int mx, my;
	int angle, length;
	Bitmap ** pics;
	int max_pics;

};

#endif
