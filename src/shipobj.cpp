#include "shipobj.h"
#include "hull.h"
#include "raptor.h"
#include "bitmap.h"
#include "trigtable.h"
#include "explode.h"
//#include "explode_slim.h"
#include "explode_animate.h"
#include "gunobj.h"
#include "sound.h"
#include "move.h"
#include "defs.h"
#include "strings.h"
#include "booster.h"
#include "section.h"

#include "hulls/hull_num_show.h"
#include "hulls/hull_player.h"

#include <stdio.h>

//{
ShipObject::ShipObject( int qx, int qy, int spc, HullObject * hnew, Group * _group, Move * movey, int al ):
SpaceObject(qx,qy, 0, 0, hnew, _group, PLANE_AIR, al ),
special( spc ) {
	style = movey;
}

void ShipObject::Died( SpaceObject * check, ExplosionClass ** explr, int ME ){
    if (check != NULL){
        check->IncScore(special + (int)(hull->original_life * 10));
        check->addPowerBonus(hull->original_life);
    }
    this->Explode(explr, ME);

    Util::playSound(SND_EXPLODE_2, 180);
}

bool ShipObject::powerUp() {
	return true;
}


double ShipObject::Hurt() {
	if ( getLife() >= hull->Hurt() ) return hull->Hurt();
	if ( getLife() > 0 ) return getLife();
	return 1;
}

/* PONDER:
 * Should I extract movement from AI?
 * Maybe they could be seperate functions which might make
 * scripting a little easier..
 */
void ShipObject::MoveMe( vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight, Section * onscreen ){

	double sdx = getDX();
	double sdy = getDY();

	if ( style )
		style->action( fight, getX(), getY(), sdx, sdy );
	setDX( sdx );
	setDY( sdy );

	MoveReal();

	if ( hull ) hull->Moved( this->getDX(), this->getDY(), this->getAccelX(), this->getAccelY() );

	int middle_x = this->getX() + this->getMaxX() / 2;
	int middle_y = this->getY() + this->getMaxY() / 2;

	middle_x = getX();
	middle_y = getY();

	if ( getY() > -10 ) {

		WeaponObject ** myGun = hull->Guns();
		if ( myGun != NULL ) {
			for ( int q = 0; q < hull->maxGuns(); q++ )
				if ( myGun[q] != NULL ){
					if ( myGun[q]->getShotCounter() > 0 )
						myGun[q]->Wait( 1 );
					else myGun[q]->MakeShot( middle_x, middle_y, Ammo, fight );
				}

		}
	}

}


void ShipObject::Explode( ExplosionClass ** explr, int ME ) {
	int mx = getX();
	int my = getY();
	ExplosionClass * w_expl = new ExplosionAnimate( mx, my, this->getDX()/2, this->getDY()/2, EXPLODE_1, EXPLODE_A_30 );
	addExplode( explr, ME, w_expl );
}


ShipObject::~ShipObject() {
	if ( style != NULL ) delete style;
}


//}
//{
MeteorObject::MeteorObject( int qx, int qy, int spc, HullObject * hnew, Move * hmove ):
ShipObject( qx, qy, spc, hnew, NULL, hmove, TEAM_ENEMY ){}

void MeteorObject::Explode( ExplosionClass ** explr, int ME ) {
	int middle_x = this->getX() + this->getMaxX() / 2;
	int middle_y = this->getY() + this->getMaxY() / 2;
	ExplosionClass * w_expl = new ExplosionAnimate( middle_x, middle_y, this->getDX()/2, this->getDY()/2, GR_EXPLODE_01, GR_EXPLODE_29 );
	addExplode( explr, ME, w_expl );
}


//{

//}
//{
EnemyGeneric::EnemyGeneric( int qx, int qy, HullObject * hnew, WeaponObject * myW, Move * movey, Group * _group ):
ShipObject(qx,qy,100,hnew, _group, movey,TEAM_ENEMY) {
	//WeaponObject ** myGun = hull->Guns();
	//if ( myGun != NULL )
	//	myGun[0] = myW;
	hull->giveWeapon( myW, 0 );
}


void EnemyGeneric::Radar( const Bitmap & rad ) const{
	//putpixel( rad, (int)( (float)actualx / ( (float)screen_x / (float)rad->w  ) ), (int)( (float)actualy / ( (float)screen_y / (float)rad->h  ) ), makecol(200,100,0) );
	// circlefill( rad, (int)( (float)getX() / ( (float)screen_x / (float)rad->w  ) ), (int)( (float)getY() / ( (float)screen_y / (float)rad->h  ) ), 1, makecol(200,100,0) );
	int x = (int)( (float)getX() / ( (float) Util::screen_x / (float)rad.getWidth() ) );
	int y = (int)( (float)getY() / ( (float) Util::screen_y / (float)rad.getHeight() ) );

	rad.circleFill( x, y, 1, Bitmap::makeColor(200,100,0) );
	/* test */

}


//}
//{
Money::Money( int qx, int qy, int m, HullObject * hnew, Move * movey ):
PowerUp( qx, qy, hnew, movey ) {
	str = 0;
	special = m;
}

void Money::Died( SpaceObject * check, ExplosionClass ** explr, int ME ){
	if ( check != NULL ){
		check->IncScore( special );
	}

	Util::playSound( SND_POWER, 255 );
}

bool Money::Damage( double much ) {
	delete hull;
	hull = new HullShow( special );
	// style->setD( 0, 0 );
	delete style;
	style = NULL;
	return true;
}


//}
//{
PowerUp::PowerUp( int qx, int qy, HullObject * hnew, Move * movey ):
ShipObject( qx, qy, 0, hnew, NULL, movey,TEAM_ENEMY ) {
	str = 0;
}


void PowerUp::Died( SpaceObject * check, ExplosionClass ** explr, int ME ){
	if ( check != NULL ) {

		/*
		WeaponObject ** gz = check->hull->Guns();
		if ( pcount( (char **)gz, check->hull->maxGuns()-1 ) == 0 ) return;
		int q = rnd( check->hull->maxGuns()-1 );
		while ( gz[q] == NULL ) q = rnd(check->hull->maxGuns()-1);
		gz[q]->IncreasePower( 1 );
		*/
		WeaponObject * gz[ check->getHull()->maxGuns() - 1 ];
		for ( int q = 0; q < check->getHull()->maxGuns()-1; q++ ) {
			gz[q] = NULL;
			if ( check->getHull()->Guns()[q] != NULL && (check->getHull()->Guns()[q]->getPower() < check->getHull()->Guns()[q]->maxPower() || check->getHull()->Guns()[q]->maxPower() == -1) )
				gz[q] = check->getHull()->Guns()[q];
		}
		int q = Util::rnd( check->getHull()->maxGuns()-1 );
		if ( Util::pcount( (char **)gz, check->getHull()->maxGuns()-1 ) == 0 ) {
			// delete[] gz;
			return;
		}
		while ( gz[q] == NULL ) q = Util::rnd( check->getHull()->maxGuns()-1 );
		gz[q]->IncreasePower( 1 );

	}

	Util::playSound( SND_POWER, 255 );
}


bool PowerUp::Damage( double much ) {
	getHull()->takeDamage( getLife()+1 );
	return true;
}


void PowerUp::Radar( const Bitmap & rad ) const{
}


bool PowerUp::isSpecial() const {
	return true;
}


bool PowerUp::powerUp() {
	return false;
}


//}
Health::Health( int qx, int qy, HullObject * hnew, Move * movey ):
PowerUp( qx, qy, hnew, movey ) {
}

void Health::Died( SpaceObject * check, ExplosionClass ** explr, int ME ){
	if ( check != NULL ) {

		check->getHull()->life += 20;
		if ( check->getHull()->life > ((PlayerHull *)check->getHull())->getMaxLife() )
			check->getHull()->life = ((PlayerHull *)check->getHull())->getMaxLife();

	}

	Util::playSound( SND_HEALTH, 255 );
}


Cloak::Cloak( int qx, int qy, HullObject * hnew, Move * movey ):
PowerUp( qx, qy, hnew, movey ) {
}

void Cloak::Died( SpaceObject * check, ExplosionClass ** explr, int ME ){
	if ( check != NULL ) {
		((PlayerHull *)check->getHull())->cloak = 300;
	}

	Util::playSound( SND_POWER, 255 );
}
