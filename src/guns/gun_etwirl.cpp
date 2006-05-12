#include "gunobj.h"
#include "weaponobj.h"
#include "gun_etwirl.h"
#include "hulls/hull_weapon_twirl.h"
#include "defs.h"
#include "spaceobj.h"
#include "ebox.h"
#include "raptor.h"
#include <vector>

using namespace std;

EnemyTwirlStraight::EnemyTwirlStraight( int d, int al ):
WeaponObject( d, "Twirl Straight", 0, al, 0, 0 ) {

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

EnemyTwirlStraight::~EnemyTwirlStraight() {
	delete ecollide;
}

void EnemyTwirlStraight::MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * >  * fight ) {
	shot_counter = 45;
	const double speed = 8;
	Ammo->push_back( new WeaponNode(x,y,0,speed, new Twirl_WHull( Util::getDataSprite( BULLET_TWIRL ), ecollide->copy() ), alignment ) ); 
}
