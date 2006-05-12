#ifndef _gun_chain_h
#define _gun_chain_h

#include "gunobj.h"

class SpaceObject;
class ECollide;

class WeaponChainGun: public WeaponObject{
public:

	WeaponChainGun( int z, int d, const char * name, int wor, int smp, int al, ECollide * eb );
	virtual void MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );
	virtual void Idle(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight);
	virtual WeaponObject * copy();

	~WeaponChainGun();

protected:

	int lx, ly;
	int ox, oy;
	double fx, fy;
	double dx, dy;
	 
	int d_length;
	int draw_number;
	ECollide * chain_collide;

};

#endif
