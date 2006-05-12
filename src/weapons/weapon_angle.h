#ifndef _angle_h
#define _angle_h

#include "weaponobj.h"

class HullObject;

class Angle:public WeaponNode{
public:
	Angle( int qx, int qy, double kx, double ky, double speed, HullObject * hnew, int al, int _ang );
	// virtual void MoveReal();
	
	virtual void MoveMe( vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight, Section * onscreen );

protected:
	double center_x, center_y;
	int ang_vel;
	int ang_accel;
	double speed;
};

#endif
