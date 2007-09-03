#include "move.h"
#include "spaceobj.h"
#include "trigtable.h"
#include <vector>

using namespace std;

//{
Move::Move( double _dx, double _dy ):
o_dx( _dx ),
o_dy( _dy ){

	/*
	dx = _dx;
	dy = _dy;
	*/

	/*
	actualx = NULL;
	actualy = NULL;
	virtualx = NULL;
	virtualy = NULL;
	*/

	accel_x = 0;
	accel_y = 0;
}

Move::~Move(){
}

/*
int Move::AX(){
	/ *
	if ( actualx != NULL ) 
		return *actualx;
	* /
	return 0;
}

int Move::AY(){
	/ *
	if ( actualy != NULL )
		return *actualy;
	* /
	return 0;
}
*/

	/*
void Move::setP( int & ax, int & ay, double & vx, double & vy ) {
	actualx = &ax;
	actualy = &ay;
	virtualx = &vx;
	virtualy = &vy;
}
	*/


/*
double Move::Accel_X(){
	return accel_x;
}

double Move::Accel_Y(){
	return accel_y;
}

void Move::setD( double _dx, double _dy ) {
	dx = _dx;
	dy = _dy;
}
*/

void Move::action( const vector< SpaceObject * > * fight, int x, int y, double & sdx, double & sdy ) {
	sdx = o_dx;
	sdy = o_dy;
	// return MoveReal();
}

/*
double Move::DX() {
	return dx;
}


double Move::DY() {
	return dy;
}
*/

	/*
bool Move::MoveReal() {

	*virtualx += dx;
	*virtualy += dy;
	*actualx = (int)*virtualx;
	*actualy = (int)*virtualy;

	if ( *actualy >= screen_y+100 || *actualx < -100 || *actualx > screen_x+100 || *actualy < -500 ) return true;
	return false;
}
	*/


//}
//{
MoveHorizontal::MoveHorizontal( double _dx, double _dy ):
Move( _dx, _dy ) {
	dir = 1;
	//dx = 2.3;
}

MoveHorizontal::~MoveHorizontal(){
}

void MoveHorizontal::action( const vector< SpaceObject * > * fight, int x, int y, double & sdx, double & sdy ) {

	/*
	if ( *actualx > screen_x-20 ) dir = -1;
	if ( *actualx < 20 ) dir = 1;

	dx = dir * o_dx;
	dy = o_dy;
	*/
	if ( x > Util::screen_x - 20 ) dir = -1;
	if ( x < 20 ) dir = 1;
	sdx = dir * o_dx;
	sdy = o_dy;
	// return MoveReal();
}


//}
//{
MoveMine::MoveMine( double _dx, double _dy ):
Move( _dx, _dy ),
fx( -1 ),
fy( -1 ),
sx( _dx ),
sy( _dy ){}

MoveMine::~MoveMine(){
}

void MoveMine::action( const vector< SpaceObject * > * fight, int x, int y, double & sdx, double & sdy ) {

	// if ( fight->empty() ) return MoveReal();
	if ( fight->empty() ) return;

	if ( fx == -1 || fy == -1 || (Util::rnd(30) == Util::rnd(30)) ) {
		SpaceObject * attack = fight->front();
		if ( attack != NULL ) {
			fx = attack->getX() + Util::rnd(20) - 10;
			fy = attack->getY() + Util::rnd(20) - 10;
			int sang = gang( x, y, fx, fy );
			double gm = fabs( o_dx ) > fabs( o_dy ) ? fabs(o_dx) : fabs( o_dy );

			accel_x = Tcos(sang);
			accel_y = Tsine(sang);

			sdx = accel_x * gm;
			sdy = accel_y * gm;
		}
	}

	// return MoveReal();

}


//}
//{
MoveAngular::MoveAngular( double _dx, double _dy ):
Move( _dx, _dy ),
ang( 0 ),
dir( Util::rnd(10) + 2 ) {
	// if ( dx == 0 ) dx = dy;
}

MoveAngular::~MoveAngular(){
}

void MoveAngular::action( const vector< SpaceObject * > * fight, int x, int y, double & sdx, double & sdy ) {

	ang += dir;
	while ( ang >= 360 ) ang -= 360;
	while ( ang < 0 ) ang += 360;

	accel_x = Tcos(ang);
	accel_y = Tsine(ang);

	sdx = accel_x * fabs(o_dx);
	sdy = accel_y * fabs(o_dy) + 2;
	// return MoveReal();

}


//}
//{
MoveSwingRight::MoveSwingRight( double _dx, double _dy ):
Move( _dx, _dy ){
	accel_x = 0.15;
	accel_y = 0;
}

MoveSwingRight::~MoveSwingRight(){
}

void MoveSwingRight::action( const vector< SpaceObject * > * fight, int x, int y, double & sdx, double & sdy ) {
	// if ( *actualy > 0 ) dx += accel_x;
	sdx += accel_x;
	sdy = o_dy;
	// return MoveReal();
}


//}
//{
MoveSwingLeft::MoveSwingLeft( double _dx, double _dy ):
Move( _dx, _dy ){
	accel_x = -0.15;
	accel_y = 0;
}

void MoveSwingLeft::action( const vector< SpaceObject * > * fight, int x, int y, double & sdx, double & sdy ) {

	// if ( *actualy > 0 ) dx += accel_x;
	sdx += accel_x;
	sdy = o_dy;
	// return MoveReal();
}

MoveSwingLeft::~MoveSwingLeft(){
}

//}
//{
MoveSwingDown::MoveSwingDown( double _dx, double _dy ):
Move( _dx, _dy ){
	accel_x = 0;
	accel_y = 0.13;
}

MoveSwingDown::~MoveSwingDown(){
}

void MoveSwingDown::action( const vector< SpaceObject * > * fight, int x, int y, double & sdx, double & sdy ) {

	//if ( *actualy > 0 ) dy += 0.35;
	sdy += accel_y;
	sdx = o_dx;
	// return MoveReal();
}


//}
//{
MoveSine::MoveSine( double _dx, double _dy ):
Move( _dx, _dy ),
ang( 0 ){}

MoveSine::~MoveSine(){
}

void MoveSine::action( const vector< SpaceObject * > * fight, int x, int y, double & sdx, double & sdy ) {
	accel_x = Tcos(ang);
	sdx = accel_x * fabs( o_dx );
	sdy = o_dy;
	ang = (ang+6) % 360;
	// return MoveReal();
}


//}
//{
MoveCircle_Player::MoveCircle_Player( double _dx, double _dy ):
Move( _dx, _dy ),
ang( 90 ) {

	find_circle = Util::rnd( 4 ) + 3;

}

MoveCircle_Player::~MoveCircle_Player(){
}

void MoveCircle_Player::action( const vector< SpaceObject * > * fight, int x, int y, double & sdx, double & sdy ) {

	// if ( fight->empty() ) return MoveReal();
	if ( fight->empty() ) return;
	SpaceObject * s = fight->front();

	int sang = gang( s->getX(), s->getY(), x, y );
	ang = (sang + find_circle) % 360;
	int fx = (int)( s->getX() + Tcos( ang ) * 150 );
	int fy = (int)( s->getY() + Tsine(ang ) * 150 );
	sang = gang( x, y, fx, fy );
	double fmax = fabs( o_dx ) > fabs( o_dy ) ? fabs( o_dx ) : fabs( o_dy );

	accel_x = Tcos(sang);
	accel_y = Tsine(sang);
	
	sdx = accel_x * fmax;
	sdy = accel_y * fmax;

	// return MoveReal();
}


//}
