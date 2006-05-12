#include "gunobj.h"
#include "weaponobj.h"
#include "gun_etwirl_find.h"
#include "hulls/hull_weapon_twirl.h"
#include "defs.h"
#include "trigtable.h"
#include "spaceobj.h"
#include "ebox.h"
#include "raptor.h"
#include <vector>

using namespace std;

EnemyTwirlFind::EnemyTwirlFind( int d, int al ):
WeaponObject( d, "Twirl Find", 0, al, 0, 0 ) {

	Bitmap tmp( 6, 12 );
	tmp.fill( Bitmap::MaskColor );
	tmp.ellipseFill( 3, 6, 3, 6, Bitmap::makeColor( 255, 255, 255 ) );
	ecollide = new ECollide( tmp );

}

EnemyTwirlFind::~EnemyTwirlFind() {
	delete ecollide;
}

void EnemyTwirlFind::MakeShot(int x, int y,vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight ){
	shot_counter = 40;
	if ( fight == NULL ) return;
	if ( fight->empty() ) return;

	// SpaceObject * use = fight->front();
	SpaceObject obj( 0, 0, 0, 0, NULL, NULL, PLANE_AIR, this->getTeam() );
	const SpaceObject * use = getCollidableObject( fight, &obj );

	const double speed = 8;
	if ( use != NULL ) {
		int sang = getAngle( x, y, use->getX(), use->getY()+7 );
		double sx = Tcos(sang)* speed;
		double sy = Tsine(sang) * speed;
		Ammo->push_back( new WeaponNode(x,y,sx,sy,new Twirl_WHull( Util::getDataSprite( BULLET_TWIRL ), ecollide->copy() ), alignment ) );
	}
}
