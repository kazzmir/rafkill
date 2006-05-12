#ifndef _gun_findgun_h
#define _gun_findgun_h

#include "gunobj.h"
#include <vector>
#include "spaceobj.h"

using namespace std;

class WeaponFindGun: public WeaponObject{
public:

	WeaponFindGun( int z, int d, int al );

	virtual void MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );
	virtual WeaponObject * copy();

protected:

	//process: returns quick formula for distance
	int mdist( int x1, int y1, int x2, int y2 );

	SpaceObject * look[ 5 ];

};


#endif
