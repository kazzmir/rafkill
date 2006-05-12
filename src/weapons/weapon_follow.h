#ifndef _follow_h
#define _follow_h

#include "weaponobj.h"
#include "spaceobj.h"
#include <vector>

using namespace std;

class Follow:public WeaponNode{
public:

	Follow( int qx, int qy, int sang, const vector< SpaceObject * > * f, int al, int _life );

	virtual void MoveReal();
	virtual bool Damage( double much );
	virtual void Collided( SpaceObject * who, ExplosionClass ** explr, int M_EX );

protected:

	SpaceObject * getFight();

	int ang;
	const vector< SpaceObject * > * fight;
	SpaceObject * murder;

};

#endif
