#ifndef _hull_weapon_arc_h_
#define _hull_weapon_arc_h_

#include "hull_weapon.h"
#include "hull.h"
#include "bitmap.h"

class SpaceObject;
class ECollide;

/*
 * Arc
 *
 * a small point which has fancy colors on its tail
 *
 */

class Arc_WHull:public HullWeapon{
public:
	Arc_WHull( int str, ECollide * mycollide );
	virtual void Draw( const Bitmap & who, int x, int y );

	virtual ~Arc_WHull();

private:

	int * shade;
	Bitmap * look;

};

#endif
