#ifndef _hull_weapon_enemy_missle_h_
#define _hull_weapon_enemy_missle_h_

#include "hull_weapon.h"
class SpaceObject;
class Bitmap;

class EMissle_WHull:public HullWeapon{
public:
	EMissle_WHull();

	virtual void Draw( const Bitmap & who, int x, int y );
	virtual bool Collide( int mx, int my, SpaceObject * check );

};

#endif
