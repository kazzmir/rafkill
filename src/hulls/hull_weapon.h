#ifndef _hull_general_weapon_h
#define _hull_general_weapon_h

#include "hull.h"

class SpaceObject;

class HullWeapon: public HullObject{
public:

	HullWeapon( int drawing, int life, double str );
	// virtual bool Collide ( int mx, int my, SpaceObject * check );
	// virtual bool hullCollide( ECollide * col, int mx, int my, int ax, int ay );

};

#endif
