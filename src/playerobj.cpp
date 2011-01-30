#include "playerobj.h"
#include "shipobj.h"
#include "spaceobj.h"
#include "booster.h"
#include "keyboard.h"
#include "mouse.h"
#include "bitmap.h"
#include "gunobj.h"
#include "hull.h"
#include "hulls/hull_player.h"

PlayerObject::PlayerObject(int qx, int qy, int _difficulty, HullObject * hnew):
ShipObject(qx,qy,0,hnew,NULL,NULL,TEAM_PLAYER),
difficulty(_difficulty),
change_frame(0),
holding_accessory(true),
user_control(true),
level(1),
powerBonus(0),
powerBonusLevel(500 * difficulty){
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

    const double move_change = 3.9;

    if ( f_max > 0 ) {
        d += move_change;
        if ( d > f_max ) d = f_max;
    } else {
        d -= move_change;
        if ( d < f_max ) d = f_max;
    }

}

bool PlayerObject::Destroyable() const{
	return false;
}

void PlayerObject::MoveMe( vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight, Section * onscreen ){

    if (powerBonus > 0){
        powerBonus -= (double) powerBonusLevel / 50000.0;
        if (powerBonus < 0){
            powerBonus = 0;
        }
    }

	if ( user_control )
		userInput( fight, Ammo );

	MoveReal();

	engine.Update();

	if ( hull ) hull->Moved( this->getDX(), this->getDY(), this->getAccelX(), this->getAccelY() );

	// return false;

}

static struct input emptyInput(){
	struct input i;
	i.dx = 0;
	i.dy = 0;
	i.shoot = false;
	i.change_weapons = false;
	return i;
}

struct input PlayerObject::joyInput(){
	struct input joy = emptyInput();
	/* TODO: Add joystick code */
	return joy;
}

struct input PlayerObject::keyboardInput(){
	struct input all = emptyInput();
	
	const double move = 11.23;

	if ( Keyboard::getAnyKey( Keyboard::UP,
				  Keyboard::W,
				  Keyboard::PAD_8 ) ){
		all.dy = -move;
	}

	if ( Keyboard::getAnyKey( Keyboard::DOWN,
				  Keyboard::X,
				  Keyboard::S,
				  Keyboard::PAD_2 ) ){
		all.dy = move;
	}

	if ( Keyboard::getAnyKey( Keyboard::RIGHT,
				  Keyboard::D,
				  Keyboard::PAD_6 ) ){
		all.dx = move;
	}

	if ( Keyboard::getAnyKey( Keyboard::LEFT,
				  Keyboard::A,
				  Keyboard::PAD_4 ) ){
		all.dx = -move;
	}


	if ( Keyboard::getAnyKey( Keyboard::SPACE,
				  Keyboard::ENTER,
				  Keyboard::ENTER_PAD ) ){
		all.shoot = true;
	}
		
	#ifdef PANDORA
	if ( Keyboard::getAnyKey( Keyboard::LCONTROL, Keyboard::RCONTROL ) ){
	#else
	if ( Keyboard::getAnyKey( Keyboard::ALT, Keyboard::ALTGR ) ){
	#endif
		all.change_weapons = true;
	}

	/*
	if ( !holding_accessory ){
		if ( Keyboard::getAnyKey( Keyboard::ALT, Keyboard::ALTGR ) ){
			all.change_weapons = true;
			holding_accessory = true;
		}
	}

	if ( ! Keyboard::getAnyKey( Keyboard::ALT, Keyboard::ALTGR ) ){
		holding_accessory = false;
	}
	*/

	return all;
}

struct input PlayerObject::mouseInput(){
	struct input all = emptyInput();

	int x, y;
	mouse::get_mickeys( &x, &y );
	all.dx = (double) x * mouse::getSensitivity();
	all.dy = (double) y * mouse::getSensitivity();
	all.shoot = mouse::leftClick();
	all.change_weapons = mouse::rightClick();

	return all;
}

void PlayerObject::userInput( const vector< SpaceObject * > * fight, vector< SpaceObject * > * Ammo ){

	struct input keyboard = keyboardInput();
	struct input mouse = mouseInput();
	struct input joy = joyInput();

	struct input all;
	all.dx = keyboard.dx + mouse.dx + joy.dx;
	all.dy = keyboard.dy + mouse.dy + joy.dy;
	all.shoot = keyboard.shoot || mouse.shoot || joy.shoot;
	all.change_weapons = keyboard.change_weapons || mouse.change_weapons || joy.change_weapons;

	if ( ++change_frame >= 10 ) change_frame = 0;

	// key_UP = key_DOWN = key_RIGHT = key_LEFT = key_SHOOT = key_ACCESSORY = false;

	setAccelY( all.dy );
	setAccelX( all.dx );
	if ( all.dy < 0.0 ){
		if ( change_frame % 2 == 0 ) {
			int mx = getX() + getMaxX() / 2;
			int my = getY() + getMaxY() / 2;
			mx = getX();
			my = getY();
			engine.add( mx-7, my );
			engine.add( mx+7, my );
		}
	}

	
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
	
	if ( !holding_accessory && all.change_weapons ){
		((PlayerHull *)hull)->NextAccessory();
		holding_accessory = true;
	}

	if ( ! all.change_weapons ){
		holding_accessory = false;
	}
	
	if ( all.shoot ){
		shootGuns( Ammo, fight );
	} else {
		idleGuns( Ammo, fight );
	}
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
	
std::map<WeaponObject*,int> PlayerObject::gunStrengths(){
	map<WeaponObject*,int> all;

	WeaponObject ** myGun = hull->Guns();
	for ( int q = 0; q < hull->maxGuns(); q += 1 ){
		if ( myGun[q] != NULL ){
			all[ myGun[q] ] = myGun[q]->getPower();
		}
	}

	return all;
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
    const double slowdown = 1.69;
    if ( d > slowdown ) d -= slowdown;
    else if ( d < -slowdown ) d += slowdown;
    else d = 0;
}
        
void PlayerObject::addPowerBonus(double amount){
    powerBonus += amount;
    if (powerBonus > powerBonusLevel){
        powerBonus = powerBonusLevel;
    }
}

bool PlayerObject::powerBonusReady(){
    return powerBonus >= powerBonusLevel;
}

void PlayerObject::nextPowerBonus(){
    powerBonus = 0;
    powerBonusLevel *= 3;
}
        
double PlayerObject::getPowerBonus() const {
    return powerBonus;
}

double PlayerObject::getMaxPowerBonus() const {
    return powerBonusLevel;
}
