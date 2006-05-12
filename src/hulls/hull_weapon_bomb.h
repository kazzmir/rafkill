#ifndef _hull_weapon_bomb_h_
#define _hull_weapon_bomb_h_

#include "hull_weapon.h"
#include "bitmap.h"


/*
 * Bomb
 *
 * uses the bomb image sequence in the data file to show a spinning bomb
 * does a large amount of damage to all enemys
 *
 */

class Bomb_WHull:public HullWeapon{
public:

	Bomb_WHull();
	virtual void Draw( const Bitmap & who, int x, int y );

	int frame;

};

#endif
