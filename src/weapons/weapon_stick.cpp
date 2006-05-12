#include "weaponobj.h"
#include "weapon_stick.h"
#include "hull.h"
#include "hulls/hull_weapon_explode.h"
#include "ebox.h"
#include "trigtable.h"
#include <vector>
using namespace std;

Sticky::Sticky( int qx, int qy, double kx, double ky, HullObject * hnew, int al, ECollide ** _collide_list, int _max_collide, int _strength ):
WeaponNode(qx,qy,kx,ky,hnew,al),
max_collide( _max_collide ),
tick( -1 ),
bomb_rad( 0 ),
strength( _strength ) {

	collide_list = _collide_list;
	station = NULL;

}


bool Sticky::Damage( double much ) {
	return false;
}


void Sticky::Collided( SpaceObject * who, ExplosionClass ** explr, int M_EX ) {
	if ( tick == -1 ) {
		tick = 30;
		station = who;
		ang = getAngle( station->getX(), station->getY(), getX(), getY() );
		ds = (int) dist( station->getX(), station->getY(), getX(), getY() );
	}

	if ( tick == 0 ) {

		ECollide * ec = hull->getCollide();
		EQuad * e = ec->getLast();
		int x = e->getPosX();
		int y = e->getPosY();
		addExplode( explr, M_EX, new ExplosionClass(x,y,0,0,Util::rnd(6) + 3 ) );
	}
	
	setDX( 0 );
	setDY( 0 );

	/*
	station = check;
	ang = gang( station->actualx, station->actualy, actualx, actualy );
	ds = dist( station->actualx, station->actualy, actualx, actualy );
	*/

}


bool Sticky::Collide(SpaceObject * check) {
	// if ( !CanbeHit( check ) ) return false;
	
	if ( tick > 0 ) return false;
	/*
	bool cy = hull->Collide( actualx, actualy, check );
	if ( cy ){
		station = check;
		ang = gang( station->actualx, station->actualy, actualx, actualy );
		ds = dist( station->actualx, station->actualy, actualx, actualy );
	}
	*/
	return hull->Collide( getX(), getY(), check );
}


void Sticky::MoveMe( vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight, Section * onscreen ){

	if ( tick > 0 ) {
		tick--;
		if ( tick == 0 ) {

			this->giveHull( new Explode_WHull( strength, collide_list, max_collide ) );
			collide_list = NULL;

		}
	}

	if ( tick == 0 ) {
		/*
		bomb_rad = (bomb_rad+1) % 3;
		if ( bomb_rad == 0 ) hull->Moved( 0, 0, 0, 0 );
		*/
		hull->Moved( 0, 0, 0, 0 );
	}
	MoveReal();
	if ( station != NULL && tick != 0 ) {

		vector< SpaceObject * >::const_iterator it;
		for ( it = fight->begin(); station != *it && it != fight->end(); it++ );
		if ( it == fight->end() )tick = 1;
		else this->SetCoordXY( (int)(station->getX()+Tcos(ang)*ds), (int)(station->getY()+Tsine(ang)*ds) );

	}

	// if ( hull ) hull->addSection( this, onscreen, getX(), getY() );
	// return ( getX() < -20 || getX() > screen_x + 20 || getY() < -10 || getY() > screen_y + 20 );

}


Sticky::~Sticky() {
	if ( collide_list != NULL ) {
		//for ( int q = 0; q < max_collide; q++ )
		//	delete collide_list[q];
		//delete[] collide_list;
	}
}
