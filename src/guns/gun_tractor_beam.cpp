#include "gunobj.h"
#include "gun_tractor_beam.h"
#include "trigtable.h"
#include "weapons/weapon_damage.h"
#include "hulls/hull_weapon_tractor_beam.h"
#include "spaceobj.h"
#include "ebox.h"
#include <vector>
#include <math.h>

using namespace std;

WeaponTractorBeam::WeaponTractorBeam( int z, int d, int al ):
WeaponObject( d, "Tractor Beam", 405000, al, z, 4 ) {
	look = NULL;

	Bitmap temp( 8, 8 );
	temp.fill( Bitmap::makeColor(255,0,255) );
	temp.circleFill( 4, 4, 3, Bitmap::makeColor(255,0,0) );
	collide = new ECollide( &temp );

}


WeaponObject * WeaponTractorBeam::copy() {
	return new WeaponTractorBeam( strength, dir, alignment );
}


WeaponTractorBeam::~WeaponTractorBeam() {
	delete collide;
}


void WeaponTractorBeam::MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight ) {

	if ( fight == NULL ) return;
	if ( fight->empty() ) {
		look = NULL;
		return;
	}

	// SpaceObject * gay = new SpaceObject(0,0,0,0,NULL,NULL,PLANE_AIR|PLANE_GROUND, alignment );
	SpaceObject gay(0,0,0,0, NULL, NULL, PLANE_AIR|PLANE_GROUND, alignment );
	bool cy = false;

	for ( vector< SpaceObject * >::const_iterator it = fight->begin(); it != fight->end(); it++ )
		if ( (*it)->CanbeHit( &gay ) ) cy = true;

	if ( !cy ) {
		look = NULL;
		// delete gay;
		return;
	}

	shot_counter = 0;

	vector< SpaceObject * >::const_iterator find_next = fight->begin();

	cy = true;
	if ( look != NULL ) {
		for ( vector< SpaceObject * >::const_iterator it = fight->begin(); it != fight->end(); ) {
			if ( look == (*it) ) {
				cy = false;
				it = fight->end();
			} else it++;
		}
	}
	if ( cy ) look = NULL;
	else {
		if ( look->getX()>640||look->getX()<0||look->getY()>480||
			look->getY()<0 )
			cy = true;
		if ( !look->CanbeHit( &gay ) )
			cy = true;
	}

	if ( cy ) {

		look = *find_next;
		while ( !look->CanbeHit( &gay ) ) {

			find_next++;
			if ( find_next == fight->end() ) find_next = fight->begin();
			look = *find_next;

		}
		find_next++;
		if ( find_next == fight->end() ) find_next = fight->begin();

	}

	int r, g, b;
	int h = ( (strength + 2 ) * 50 ) % 360;
	Bitmap::hsvToRGB( (float)h, 1.0, 1.0, &r, &g, &b );

	SpaceObject * choose = look;
	if ( choose != NULL ) {

		int d = (int) dist( x, y, choose->getX(), choose->getY() );

		int fx, fy;
		fx = choose->getX();
		fy = choose->getY();
		int ang = getAngle( x, y, fx, fy );

		for ( int s = 0; s < d; s += 5 ) {
			int qx = (int)( (double)x + Tcos(ang)*(double)s );
			int qy = (int)( (double)y + Tsine(ang)*(double)s );
			Ammo->push_back(new Damage_Weapon(qx,qy,0,0,1, new Tractor_WHull(strength*2+1, Bitmap::makeColor(r,g,b), collide->copy() ),alignment ) );
		}

	}
	// delete gay;

}
