#ifndef _weapon_stick_h
#define _weapon_stick_h

#include "weaponobj.h"
class HullObject;
class ECollide;

class Sticky:public WeaponNode{
public:
	Sticky( int qx, int qy, double kx, double ky, HullObject * hnew, int al, ECollide ** _collide_list, int _max_collide, int _strength );
	virtual bool Damage( double much );
	virtual void Collided( SpaceObject * who, ExplosionClass ** explr, int M_EX );
	virtual bool Collide( SpaceObject * check);
	virtual void MoveMe( vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight, Section * onscreen );
	virtual ~Sticky();

protected:
	SpaceObject * station;
	ECollide ** collide_list;
	int max_collide;

	int tick;
	int bomb_rad;
	int ang, ds;
	int strength;
};

#endif

