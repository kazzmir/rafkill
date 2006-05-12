#ifndef _rotate_h
#define _rotate_h

#include "weaponobj.h"
class HullObject;

class Rotate:public WeaponNode{
public:
	Rotate( int qx, int qy, double kx, double ky, int _ang, int _max, HullObject * hnew, int al );
	
	virtual void MoveMe( vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight, Section * onscreen );

protected:
	int ang;
	int max;
	int rad;
	int dir;
};

#endif
