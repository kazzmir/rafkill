#ifndef _pulse_h
#define _pulse_h

#include <vector>

using namespace std;

#include "weaponobj.h"
class SpaceObject;
class HullObject;
class ExplosionClass;

class Pulse:public WeaponNode{
public:
	Pulse( int qx, int qy, double kx, double ky, HullObject * hnew, int al );
	virtual bool Damage( double much );
	virtual void Collided( SpaceObject * who, ExplosionClass ** explr, int M_EX );
};

class NovaPulse:public Pulse{
public:

	NovaPulse(int qx, int qy, double kx, double ky, int al );
	virtual void MoveMe( vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight, Section * onscreen );
};

#endif
