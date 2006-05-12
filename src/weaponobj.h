#ifndef _weaponnode_h_
#define _weaponnode_h_

#include "spaceobj.h"

class ExplosionClass;
class HullObject;

class WeaponNode:public SpaceObject{
public:
	WeaponNode(int qx, int qy, double kx, double ky, HullObject * hnew, int alignment );

	virtual bool hullCollide( ECollide * col, int x, int y );
	virtual bool Damage( double much );
	virtual void Died( SpaceObject * check, ExplosionClass ** explr, int ME );
	virtual void Explode( ExplosionClass ** explr, int ME );
	virtual bool CanbeHit( const SpaceObject * ht ) const;

	virtual ~WeaponNode();

};

#endif
