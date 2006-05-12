#ifndef _shipobj_h_
#define _shipobj_h_

#include "spaceobj.h"
#include "defs.h"
#include "bitmap.h"
#include <vector>

using namespace std;

class Booster;
class Move;
class WeaponObject;
class HullObject;
class WeaponNode;
class ExplosionClass;
class Section;
class Group;

class ShipObject:public SpaceObject{
public:

	ShipObject( int qx, int qy, int spc, HullObject * hnew, Group * _group, Move * movey, int al );

	virtual void MoveMe(vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight, Section * onscreen );

	virtual void Died( SpaceObject * check, ExplosionClass ** explr, int ME );
	
	virtual void Explode( ExplosionClass ** explr, int ME );

	/*
	virtual double getDX();
	virtual double getDY();
	virtual double getAccelX();
	virtual double getAccelY();
	*/
	
	virtual double Hurt();
	
	virtual bool powerUp();
	
	//destructor
	virtual ~ShipObject();

protected:

	Move * style;
	int special;

};

class MeteorObject:public ShipObject{
public:
	MeteorObject( int qx, int qy, int spc, HullObject * hnew, Move * hmove );
	virtual void Explode( ExplosionClass ** explr, int ME );
};

//there must be a better way to implement this
class EnemyGeneric:public ShipObject{
public:
	EnemyGeneric( int qx, int qy, HullObject * hnew, WeaponObject * myW, Move * movey, Group * _group );
	virtual void Radar( const Bitmap & rad )const;
};

class PowerUp:public ShipObject{
public:
	PowerUp( int qx, int qy, HullObject * hnew, Move * movey );
	virtual bool Damage( double much );
	virtual void Died( SpaceObject * check, ExplosionClass ** explr, int ME );
	virtual bool powerUp();
	virtual bool isSpecial() const;
	virtual void Radar( const Bitmap & rad )const;
};

class Money:public PowerUp{
public:
	Money( int qx, int qy, int m, HullObject * hnew, Move * movey );
	virtual bool Damage( double much );
	virtual void Died( SpaceObject * check, ExplosionClass ** explr, int ME );
};

class Health:public PowerUp{
public:
	Health( int qx, int qy, HullObject * hnew, Move * movey );
	virtual void Died( SpaceObject * check, ExplosionClass ** explr, int ME );
};

class Cloak:public PowerUp{
public:

	Cloak( int qx, int qy, HullObject * hnew, Move * movey );
	virtual void Died( SpaceObject * check, ExplosionClass ** explr, int ME );
};

#endif
