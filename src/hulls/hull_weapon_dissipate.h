#ifndef _hull_weapon_dissipate_h_
#define _hull_weapon_dissipate_h_

#include "hull_weapon.h"
#include "bitmap.h"

class SpaceObject;
class ECollide;

/*
 * Dissipate
 * 
 * loses energy as it moves
 * given an initial life, strength is computed as life/(USE_AMMO*C)
 *
 */

class Dissipate_WHull:public HullWeapon{
public:
	Dissipate_WHull( int str, ECollide * ec );
	virtual void Draw( const Bitmap & who, int x, int y );
	virtual void Moved( double _dx, double _dy, double _ax, double _ay );
	//virtual bool Collide( int mx, int my, SpaceObject * check );

	virtual ~Dissipate_WHull();

private:

	int * shade;
	int mlife;

};

#endif
