#include "gunobj.h"
#include "weaponobj.h"
#include "gun_etwirl_machine.h"
#include "hulls/hull_weapon_twirl.h"
#include "defs.h"
#include "trigtable.h"
#include "spaceobj.h"
#include "ebox.h"
#include "raptor.h"
#include <vector>

using namespace std;

EnemyTwirlMachine::EnemyTwirlMachine( int d, int al ):
WeaponObject( d, "Twirl Machine", 0, al, 0, 0 ),
tear( 5 ) {
	
	Bitmap tmp( 6, 12 );
	tmp.fill( Bitmap::MaskColor );
	tmp.ellipseFill( 3, 6, 3, 6, Bitmap::makeColor( 255, 255, 255 ) );
	ecollide = new ECollide( tmp );

	/*
	BITMAP * temp = create_bitmap( 6, 12 );
	clear_to_color( temp, makecol(255,0,255) );
	ellipsefill( temp, 3, 6, 3, 6, makecol(255,255,255) );
	// ecollide = new ECollide( temp,2,makecol(255,0,255), 52 );
	ecollide = new ECollide( temp );
	destroy_bitmap( temp );
	*/
}

EnemyTwirlMachine::~EnemyTwirlMachine() {
	delete ecollide;
}

void EnemyTwirlMachine::MakeShot(int x, int y,vector< SpaceObject * > * Ammo, const vector< SpaceObject * >  * fight ) {
	shot_counter = 40;
	if ( fight == NULL ) return;
	if ( tear > 0 ) {
		tear--;
		shot_counter = 10;
	} else tear = 5;

	if ( fight->empty() ) return;

	SpaceObject obj( 0, 0, 0, 0, NULL, NULL, PLANE_AIR, this->getTeam() );
	const SpaceObject * use = getCollidableObject( fight, &obj );

	const double speed = 8;
	if ( use != NULL ) {
		int sang = gang( x, y, use->getX(), use->getY()+7 );
		double sx = Tcos(sang) * speed;
		double sy = Tsine(sang) * speed;
		Ammo->push_back( new WeaponNode(x,y,sx,sy,new Twirl_WHull( Util::getDataSprite( BULLET_TWIRL ), ecollide->copy() ), alignment ) );
	}
}
