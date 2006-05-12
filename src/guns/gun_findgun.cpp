#include "gunobj.h"
#include "gun_findgun.h"
#include "spaceobj.h"
#include "trigtable.h"
#include "weaponobj.h"
#include "hulls/hull_weapon_machine.h"
#include "spaceobj.h"
#include <vector>
#include <math.h>

using namespace std;

WeaponFindGun::WeaponFindGun( int z, int d, int al ):
WeaponObject( d, "Find Gun", 38500, al, z, -1 ) {
	strength = z;
	for ( int q = 0; q < 5; q++ )
		look[q] = NULL;
}


WeaponObject * WeaponFindGun::copy() {
	return new WeaponFindGun( strength, dir, alignment );
}


int WeaponFindGun::mdist( int x1, int y1, int x2, int y2 ) {
	return ( abs(x1-x2) + abs(y1-y2) );
}


void WeaponFindGun::MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight ) {

	if ( fight == NULL ) return;
	if ( fight->empty() ) {
		for ( int q = 0; q < 5; q++ )
			look[q] = NULL;
		return;
	}

	// SpaceObject * gay = new SpaceObject(0,0,0,0,NULL,NULL,PLANE_AIR|PLANE_GROUND, alignment );
	SpaceObject gay(0,0,0,0,NULL, NULL, PLANE_AIR|PLANE_GROUND, alignment );
	bool cy = false;

	for ( vector< SpaceObject * >::const_iterator it = fight->begin(); it != fight->end(); it++ )
		if ( (*it)->CanbeHit( &gay ) ) cy = true;

	if ( !cy ) {
		for ( int q = 0; q < 5; q++ )
			look[q] = NULL;
		// delete gay;
		return;
	}

	shot_counter = Util::rnd( 2 );

	int mp = strength;
	if ( mp > 4 ) mp = 4;

	vector< SpaceObject * >::const_iterator find_next = fight->begin();

	for ( int q = 0; q <= mp; q++ ) {

		cy = true;
		if ( look[q] != NULL ) {
			for ( vector< SpaceObject * >::const_iterator it = fight->begin(); it != fight->end(); ) {
				if ( look[q] == (*it) ) {
					cy = false;
					it = fight->end();
				} else it++;
			}
		}
		if ( cy ) look[q] = NULL;
		else {
			if ( look[q]->getX()>640||look[q]->getX()<0||look[q]->getY()>480||
				look[q]->getY()<0 )
				cy = true;
			if ( !look[q]->CanbeHit( &gay ) )
				cy = true;
		}

		if ( cy ) {

			look[q] = *find_next;
			while ( !look[q]->CanbeHit( &gay ) ) {

				find_next++;
				if ( find_next == fight->end() ) find_next = fight->begin();
				look[q] = *find_next;

			}
			find_next++;
			if ( find_next == fight->end() ) find_next = fight->begin();

		}

		SpaceObject * choose = look[q];
		if ( choose != NULL ) {

			/*
			double odx = choose->DX();
			double ody = choose->DY();
			double speed = sqrt( odx*odx + ody*ody );
			double gamma = M_PI/2.0;
			double omega = M_PI/2.0;
			if ( choose->actualx - x != 0 ) gamma = atan2( (y-choose->actualy),x-choose->actualx);
			if ( odx != 0 ) omega = atan2( ody, odx );
			double theta = gamma + asin( speed * sin( gamma - omega ) / 4.0 );
			int ang = (int)( 0.5 + theta * 180 / M_PI );
			*/

			int d = (int) dist( x, y, choose->getX(), choose->getY() );

			int fx, fy;

			fx = (int)(choose->getX() + choose->getDX()*tsqrt(d)*2.0/3.0 );
			fy = (int)(choose->getY() + choose->getDY()*tsqrt(d)*2.0/3.0 );

			int ang = getAngle( x, y, fx, fy );

			/*
			double odx = choose->DX();
			double ody = choose->DY();
			double Aspeed = sqrt( odx*odx + ody*ody );

			//int alpha = gang( choose->actualx, choose->actualy, x, y );
			double alpha = atan2( -(choose->actualy-y), choose->actualx-x );
			double beta = asin( Aspeed * sin(alpha) / 4.0 );

			printf("Object A dx = %0.5f dy = %0.5f\n", odx, ody );*/

			/*
			fixed odx = ftofix( (float)choose->DX() );
			fixed ody = ftofix( (float)choose->DY() );
			fixed speed = fixsqrt( fixadd( fixmul(odx,odx),fixmul(ody,ody) ) );
			fixed x1 = itofix( choose->actualx );
			fixed y1 = itofix( choose->actualy );
			fixed x2 = itofix( x );
			fixed y2 = itofix( y );
			fixed alpha = fixatan2( -fixsub(y2,y1), fixsub(x2,x1) );
			fixed beta = fixasin( fixdiv( fixmul(speed,fixsin(alpha) ), ftofix(4.0) ) );

			int ang = (int)(0.5 + fixtof(beta) * 180.0 / M_PI);
			ang = (ang+3600)%360;
			printf("Object A = %0.5f. Beta = %0.5f Object b = %d.\n", fixtof(alpha), ftofix(beta), ang );
			if ( choose->actualx < x ){
			if ( ang < 90 ) ang = 180 - ang;
			else ang = 360 - ang + 180;
			}
			printf("Beta = %d\n", ang );*/
			double dx = Tcos(ang) * 18.0;
			double dy = Tsine(ang) * 18.0;

			int final = strength/2+1;
			if ( final > 2 ) final = 2;
			if ( strength == 4 ) final = 3;

			final = strength / 3 + q + 1;

			Ammo->push_back(new WeaponNode(x,y,dx,dy,new Machine_WHull(final), alignment ) );

		}
	}
	// delete gay;

}
