#include "trigtable.h"
#include "weaponobj.h"
#include "weapon_follow.h"
#include "hulls/hull_weapon_follow.h"
#include "spaceobj.h"
#include <vector>

using namespace std;

#define FOLLOW_SPEED 2.1

Follow::Follow(int qx, int qy, int sang, const vector< SpaceObject * > * f, int al, int _life ):
WeaponNode( qx, qy, 0, 0, new Follow_WHull( _life ), al ),
ang( sang ) {
	fight = f;
	murder = NULL;
}


void Follow::Collided( SpaceObject * who, ExplosionClass ** explr, int M_EX ) {
	addExplode( explr, M_EX, new ExplosionClass(getX(),getY(),0,0,Util::rnd(6) + 3 ) );
}


SpaceObject * Follow::getFight() {

	if ( fight->empty() ) {
		murder = NULL;
		return murder;
	}

	SpaceObject * gay = new SpaceObject(0,0,0,0,NULL,NULL,PLANE_AIR|PLANE_GROUND, alignment );
	bool cy = false;

	for ( vector< SpaceObject * >::const_iterator it = fight->begin(); it != fight->end(); it++ )
		if ( (*it)->CanbeHit( gay ) ) cy = true;
	if ( !cy ) {
		delete gay;
		murder = NULL;
		return murder;
	}

	cy = true;
	if ( murder != NULL ) {
		for ( vector< SpaceObject * >::const_iterator it = fight->begin(); it != fight->end(); ) {
			if ( murder == (*it) ) {
				cy = false;
				it = fight->end();
			} else it++;
		}
	}

	if ( cy ) {
		murder = (*fight)[ Util::rnd( fight->size() ) ];
		while ( !murder->CanbeHit( gay ) ) murder = (*fight)[ Util::rnd( fight->size() ) ];
	}

	delete gay;
	return murder;

}


bool Follow::Damage( double much ) {
	return SpaceObject::Damage( much );
}


/*
void Follow::Explode( ExplosionClass ** explr, int ME ) {
	int q = 0;
	while ( q < ME && explr[q] != NULL )
		q++;
	if ( q >= ME )
		return;
	double a = (double)( Util::rnd( 45 ) + 15 ) / -10.0;
	explr[q] = new ExplosionClass( actualx, actualy, 0, a, Util::rnd( 9 ) + 6 );
}
*/

void Follow::MoveReal() {

	getFight();

	if ( murder != NULL && Util::rnd( 3 ) ) {
		int bang = gang( getX(), getY(), murder->getX(), murder->getY() );
		for ( int q = 0; q < 2; q++ ) {
			if ( abs( bang - ang ) <= 180 ) {
				if ( ang < bang ) ang++;
				else ang--;
			}
			else if ( abs( bang - ang ) >= 270 ) {
				if ( bang > ang )
					ang--;
				else    ang++;
			}
			else {
				if( bang > ang ) ang--;
				else ang++;
			}
			ang += 360;
			ang %= 360;
		}
	}

	/*
	dx = tcos[ ang ] * FOLLOW_SPEED;
	dy = tsine[ ang ] * FOLLOW_SPEED;
	*/
	setDX( Tcos( ang ) * FOLLOW_SPEED );
	setDY( Tsine( ang ) * FOLLOW_SPEED );

	setX( getVX() + getDX() );
	setY( getVY() + getDY() );
	/*
	virtualx += getDX();
	virtualy += getDY();
	*/
	/*
	actualx = (int)virtualx;
	actualy = (int)virtualy;
	*/

}
