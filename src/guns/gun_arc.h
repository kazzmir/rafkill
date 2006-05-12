#ifndef _gun_arc_h
#define _gun_arc_h

#include "gunobj.h"
#include <vector>
// #include "ebox.h"

using namespace std;

class ECollide;

class WeaponArc: public WeaponObject{
public:

	WeaponArc( int z, int d, int smp, int al );

	virtual void MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );
	virtual WeaponObject * copy();

	virtual ~WeaponArc();

protected:
	ECollide * arc_collide;

};


#endif
