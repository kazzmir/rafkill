#include "hull.h"
#include "hulls/hull_weapon_pulse_nova.h"
#include "weaponobj.h"
#include "weapon_pulse.h"
#include "defs.h"
#include "explode.h"

Pulse::Pulse( int qx, int qy, double kx, double ky, HullObject * hnew, int al ):
WeaponNode(qx,qy,kx,ky,hnew, al){}

bool Pulse::Damage( double much ) {
	return false;
}


void Pulse::Collided( SpaceObject * who, ExplosionClass ** explr, int M_EX ) {
	addExplode( explr, M_EX, new ExplosionClass(getX(),getY(),0,0, Util::rnd(6) + 3 ) ); 
	if ( hull ) hull->Collided();
}


NovaPulse::NovaPulse(int qx, int qy, double kx, double ky, int al):
Pulse(qx,qy,kx,ky,new NovaPulse_WHull(), al ){}
	
void NovaPulse::MoveMe( vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight, Section * onscreen ){
	setDY( getDY() - 0.20 );
	MoveReal();
	if ( hull ) hull->Moved( getDX(), getDY(), getAccelX(), getAccelY() );
}

/*
void NovaPulse::MoveReal() {

	// dy -= 0.02;
	setDY( getDY() - 0.30 );
	SpaceObject::MoveReal();
	/ *
	virtualx += dx;
	virtualy += dy;
	actualx = (int)virtualx;
	actualy = (int)virtualy;
	* /

}
*/
