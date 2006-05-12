#ifndef _gun_swirl_h
#define _gun_swirl_h

#include "gunobj.h"
#include <vector>
#include "bitmap.h"

using namespace std;

class ECollide;
class SpaceObject;

class WeaponSwirlGun: public WeaponObject{
public:

	WeaponSwirlGun( int z, int d, int smp, int al );
	virtual void MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );
	virtual void Idle(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );
	virtual void Draw( const Bitmap & less, int x, int y);
	virtual WeaponObject * copy();
	~WeaponSwirlGun();

protected:

	int rising;
	ECollide * diss_collide;
	int * shade;
	int * feel;
	int radius;
	int dir;
	int cur_rad;

};


#endif
