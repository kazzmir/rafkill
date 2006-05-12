#include "playerobj.h"
#include "shipobj.h"
#include "spaceobj.h"
#include "booster.h"
#include "keyboard.h"
#include "bitmap.h"
#include "gunobj.h"
#include "hull.h"
#include "hulls/hull_player.h"

PlayerObject::PlayerObject(int qx, int qy, int _difficulty, HullObject * hnew):
ShipObject(qx,qy,0,hnew,NULL,NULL,TEAM_PLAYER),
difficulty( _difficulty ),
change_frame( 0 ),
holding_accessory( true ),
user_control( true ),
level( 1 ){
	score = 10000;
}


PlayerObject::~PlayerObject() {
}


bool PlayerObject::acceptSpecial() const {
	return true;
}


void PlayerObject::Radar( const Bitmap & rad ) const{

	int x = (int)( (float)getX() / ( (float) Util::screen_x / (float)rad.getWidth()  ) );
	int y = (int)( (float)getY() / ( (float) Util::screen_y / (float)rad.getHeight()  ) );
	rad.circleFill( x, y, 1, Bitmap::makeColor(100,200,50) );
}

void PlayerObject::setControl( bool a ){
	user_control = a;
}

void PlayerObject::Draw( const Bitmap & less, ExplosionClass ** _explr, int MAX_EXPLR, int g, int offset ) const{

	if ( g != hull->drawLevel ) return;

	WeaponObject ** myGun = hull->Guns();
	for ( int q = 0; q < hull->maxGuns(); q++ )
		if ( myGun[q] != NULL )
			myGun[q]->Draw( less, getX(), getY()+offset );

	PlayerHull * ph = (PlayerHull *)hull;
	if ( ph->life < 30 ) {

		int mx = getX();
		int my = getY();
		for ( int q = 0; q < 3; q++ ) {
			// #define garb 35
			const int garb = 35;
			if ( Util::rnd( (int)ph->life ) == Util::rnd( (int)ph->life ) ) {
				if ( _explr != NULL )
					addExplode( _explr, MAX_EXPLR, new ExplosionClass( mx + Util::rnd( garb ) - garb / 2, my + Util::rnd( garb ) - garb / 2, 0,4.8, Util::rnd( 3 ) + 5 ) );
			}
			// #undef garb
		}

	}

	engine.Draw( less, offset );
	ph->Draw( less, getX(), getY()+offset );

}


bool PlayerObject::powerUp() {
	return false;
}


void PlayerObject::MoveD( double & d, double f_max ) {

	#define move_change 3.9

	if ( f_max > 0 ) {
		d += move_change;
		if ( d > f_max ) d = f_max;
	}
	else {
		d -= move_change;
		if ( d < f_max ) d = f_max;
	}

}

bool PlayerObject::Destroyable() const{
	return false;
}

void PlayerObject::MoveMe( vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight, Section * onscreen ){

	if ( user_control )
		userInput( fight, Ammo );

	MoveReal();

	engine.Update();

	if ( hull ) hull->Moved( this->getDX(), this->getDY(), this->getAccelX(), this->getAccelY() );

	// return false;

}

void PlayerObject::joyInput(){
	/* TODO: Add joystick code */
}

void PlayerObject::keyboardInput(){

	key_UP = Keyboard::getAnyKey( Keyboard::UP,
				      Keyboard::W,
				      Keyboard::PAD_8 );

	key_DOWN = Keyboard::getAnyKey( Keyboard::DOWN,
			                Keyboard::X,
					Keyboard::S,
					Keyboard::PAD_2 );

	key_RIGHT = Keyboard::getAnyKey( Keyboard::RIGHT,
			                 Keyboard::D,
					 Keyboard::PAD_6 );

	key_LEFT = Keyboard::getAnyKey( Keyboard::LEFT,
			                Keyboard::A,
					Keyboard::PAD_4 );


	key_SHOOT = Keyboard::getAnyKey( Keyboard::SPACE,
			                 Keyboard::ENTER,
					 Keyboard::ENTER_PAD );
		
	if ( !holding_accessory ){
		if ( Keyboard::getAnyKey( Keyboard::ALT, Keyboard::ALTGR ) ){
			key_ACCESSORY = true;
			// ((PlayerHull *)hull)->NextAccessory();
			holding_accessory = true;
		}
	}

	if ( ! Keyboard::getAnyKey( Keyboard::ALT, Keyboard::ALTGR ) ){
		holding_accessory = false;
	}

	/*
	if ( key[KEY_UP] || key[KEY_W] || key[KEY_8_PAD] ) {
		setAccelY( -move_quick );
		if ( change_frame % 2 == 0 ) {
			int mx = getX() + getMaxX() / 2;
			int my = getY() + getMaxY() / 2;
			mx = getX();
			my = getY();
			engine.add( mx-7, my );
			engine.add( mx+7, my );
		}
	}
	if ( key[KEY_DOWN] || key[KEY_X] || key[KEY_S] || key[KEY_2_PAD] ) {
		setAccelY( move_quick );
	}

	if ( key[KEY_RIGHT] || key[KEY_D] || key[KEY_6_PAD] ) {
		setAccelX( move_quick );
	}
	if ( key[KEY_LEFT] || key[KEY_A] || key[KEY_4_PAD] ) {
		setAccelX( -move_quick );
	}

	if ( !holding_accessory )
	if ( key[KEY_ALT] || key[KEY_ALTGR] ) {
		((PlayerHull *)hull)->NextAccessory();
		holding_accessory = true;
	}

	if ( !key[KEY_ALT] && !key[KEY_ALTGR] ) holding_accessory = false;
	*/


}

void PlayerObject::userInput( const vector< SpaceObject * > * fight, vector< SpaceObject * > * Ammo ){

	setAccelX( 0 );
	setAccelY( 0 );
	
	if ( ++change_frame >= 10 ) change_frame = 0;

	key_UP = key_DOWN = key_RIGHT = key_LEFT = key_SHOOT = key_ACCESSORY = false;

	keyboardInput();
	
	#define move_quick 11.23
	if ( key_UP ){
		setAccelY( -move_quick );
		if ( change_frame % 2 == 0 ) {
			int mx = getX() + getMaxX() / 2;
			int my = getY() + getMaxY() / 2;
			mx = getX();
			my = getY();
			engine.add( mx-7, my );
			engine.add( mx+7, my );
		}
	}
	if ( key_DOWN ){
		setAccelY( move_quick );
	}

	if ( key_RIGHT ){
		setAccelX( move_quick );
	}

	if ( key_LEFT ){
		setAccelX( -move_quick );
	}
	#undef move_quick
	
	double mdx = getDX();
	double mdy = getDY();

	MoveD( mdx, getAccelX() );
	MoveD( mdy, getAccelY() );

	if ( getAccelX() != 0 )
		Inertia( mdx );

	if ( getAccelY() != 0 )
		Inertia( mdy );

	setDX( mdx );
	setDY( mdy );
	
	if ( key_ACCESSORY )
		((PlayerHull *)hull)->NextAccessory();
	
	if ( key_SHOOT )
		shootGuns( Ammo, fight );
	else	idleGuns( Ammo, fight );

	
}

void PlayerObject::idleGuns( vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight ){

	int mx = getX();
	int my = getY();

	WeaponObject ** myGun = hull->Guns();
	for ( int q = 0; q < hull->maxGuns(); q++ ){
		if ( myGun[q] != NULL ) {
			if ( myGun[q]->getShotCounter() > 0 )
				myGun[q]->Wait( 1 );
			else {
				myGun[q]->Idle( mx, my, Ammo, fight );
			}
		}
	}

}

void PlayerObject::shootGuns( vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight ){

	int mx = getX();
	int my = getY();

	WeaponObject ** myGun = hull->Guns();
	for ( int q = 0; q < hull->maxGuns(); q++ ){
		if ( myGun[q] != NULL ) {
			if ( myGun[q]->getShotCounter() > 0 )
				myGun[q]->Wait( 1 );
			else {
				myGun[q]->MakeShot( mx, my, Ammo, fight );
			}
		}
	}

}

int PlayerObject::getDifficulty(){
	return difficulty;
}

void PlayerObject::setDifficulty( int d ){
	difficulty = d;
	if ( difficulty < 0 ) difficulty = 0;
	if ( difficulty > 7 ) difficulty = 7;
}
	
int PlayerObject::getLevel() const{
	return level;
}

void PlayerObject::setLevel( int s ){
	level = s;
	if ( level < 0 ) level = 0;
}

void PlayerObject::Inertia( double & d ) {
	#define slowdown 1.69
	if ( d > slowdown ) d -= slowdown;
	else if ( d < -slowdown ) d += slowdown;
	else d = 0;
}
