#ifndef _gun_tractor_beam_h
#define _gun_tractor_beam_h

#include "gunobj.h"
#include <vector>

class ECollide;
class SpaceObject;

using namespace std;

class WeaponTractorBeam: public WeaponObject{
public:

	WeaponTractorBeam( int z, int d, int al );

	virtual void MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );
	virtual WeaponObject * copy();
	virtual ~WeaponTractorBeam();

protected:

	SpaceObject * look;
	ECollide * collide;

};


#endif
