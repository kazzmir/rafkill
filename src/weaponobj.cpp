#include "weaponobj.h"
#include "spaceobj.h"
#include "hull.h"
#include "trigtable.h"
#include "sound.h"
#include "defs.h"
#include "raptor.h"
#include "explode.h"

WeaponNode::WeaponNode(int qx, int qy, double kx, double ky, HullObject * hnew, int alignment):
SpaceObject(qx,qy,kx,ky, hnew, NULL, PLANE_AIR | PLANE_GROUND, alignment ){}

bool WeaponNode::Damage( double much ) {
	hull->takeDamage( getLife() );
	hull->takeDamage( NO_EXPLODE );
	return true;
}

bool WeaponNode::hullCollide( ECollide * col, int x, int y ){
	return false;
}
	
bool WeaponNode::CanbeHit( const SpaceObject * ht ) const{
	return false;
}

void WeaponNode::Died( SpaceObject * check, ExplosionClass ** explr, int ME ){
	Util::playSound( SND_SUSTAIN, 50 );
	Explode( explr, ME );
}

void WeaponNode::Explode( ExplosionClass ** explr, int ME ) {
	//double a = (double)( Util::rnd( 45 ) + 15 ) / -10.0;
	//addExplode( explr, ME, new ExplosionClass(actualx,actualy,0,a,Util::rnd(6) + 3 ) );
	addExplode( explr, ME, new ExplosionClass(getX(),getY(),this->getDX()/2,this->getDY()/2,Util::rnd(6) + 3 ) );

}

WeaponNode::~WeaponNode() {
}
