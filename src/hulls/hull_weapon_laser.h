#ifndef _hull_weapon_laser_h
#define _hull_weapon_laser_h

#include "hull_weapon.h"

/*
 * Laser
 *
 * A laser beam like you see in other cool games.
 *
 */

class SpaceObject;
class Laser_WHull:public HullWeapon{
public:
	Laser_WHull( int str );
	// virtual bool Collide( int mx, int my, SpaceObject * check );
	// virtual void Draw( Bitmap * who, int x, int y );
	virtual void Collided();


	virtual ~Laser_WHull();

protected:

	void drawSelf();

	int * shade;
};

#endif
