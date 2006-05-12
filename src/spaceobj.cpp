#include <math.h>
#include "defs.h"
#include "spaceobj.h"
#include "gunobj.h"
#include "hull.h"
#include "group.h"
#include "section.h"
#include <vector>
#include "bitmap.h"
#include <iostream>

using namespace std;

/* Constructor:
 * Parameters are:
 * sx - X coordinate of object
 * sy - Y coordinate of object
 * qx - X velocity of object
 * qy - Y velocity of object
 * mhull - Hullobject of the object
 * PLANE - drawing level of the object
 * ali - TEAM of the object
 */
SpaceObject::SpaceObject( int sx, int sy, double qx, double qy, HullObject * mhull, Group * _group, int _plane, int ali ):
actualx(sx),
actualy(sy),
old_x(sx),
old_y(sy),
virtualx(sx),
virtualy(sy),
dx(qx),
dy(qy),
score( 0 ),
offset_x( 0 ),
offset_y( 0 ),
plane( _plane ),
alignment( ali ) {

	hull = mhull;

	// collide_list = new vector< SpaceObject * >();

	my_group = _group;
	if ( my_group != NULL )
		my_group->add( this );
}

SpaceObject::SpaceObject( const SpaceObject & s ){
	cout<<"SpaceObject copy constructor run. This should not happen"<<endl;
}

/*
 * Hitme:
 * Returns true if the coordinates are within the hull of the object,
 * false otherwise.
 */

bool SpaceObject::HitMe( int ax, int ay ) {
	if ( !hull ) return false;
	return hull->Inside( actualx, actualy, ax, ay );
}


/* MoveMe:
 * Allows the object to move and use all of its resources.
 * It is passed the list of the ammo it can shot, a list of its enemies,
 * an object which stores its position on the screen for collision detection,
 * and a sound datafile.
 */

void SpaceObject::MoveMe( vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight, Section * onscreen ){
	MoveReal();
	if ( hull ) hull->Moved( this->getDX(), this->getDY(), this->getAccelX(), this->getAccelY() );
	// if ( hull ) hull->addSection( this, onscreen, actualx, actualy );
	// return ( actualx < -20 || actualx > screen_x + 20 || actualy < -10 || actualy > screen_y + 20 );
}

void SpaceObject::addSection( Section * onscreen ){
	if ( hull ) hull->addSection( this, onscreen, actualx, actualy );
}


/* CanbeHit:
 * Returns true if there could be a collision between the this object
 * and the object passed to it.
 * Returns true unless one of the following is true:
 * 	Hull is translucent
 * 	Teams are the same
 * 	If this doesnt accept powerups and the other object gives them
 * 	The planes are different
 */
bool SpaceObject::CanbeHit( const SpaceObject * ht ) const {
	if ( ht == NULL ) return false;
	if ( ht == this ) return false;
	if ( hull )
		if ( hull->Translucent() ) return false;
	if ( getTeam() == ht->getTeam() ) return false;
	if ( isSpecial() && !ht->acceptSpecial() ) return false;
	if ( ht->isSpecial() && !acceptSpecial() ) return false;
	return plane & ht->plane;
}
	
int SpaceObject::lookPlane() const{
	if ( !hull ) return 0;
	return hull->drawLevel;
}
	
bool SpaceObject::Destroyable() const{
	return true;
}

/* AccelX:
 * returns the X acceleration
 */
double SpaceObject::getAccelX(){
	return accel_x;
}

/* AccelY:
 * returns the Y acceleration
 */
double SpaceObject::getAccelY(){
	return accel_y;
}

/* DX:
 * returns the dx instance of the object.
 * DX is the x velocity.
 */
double SpaceObject::getDX() {
	return dx;
}


/* DY:
 * returns the dy instance of th object
 * DY is the y velocity.
 */
double SpaceObject::getDY() {
	return dy;
}


/* Hurt:
 * Returns how much damage the hull will do when it collides with
 * something.
 */
double SpaceObject::Hurt() {
	if ( !hull ) return 0;
	return hull->Hurt();
}


/* PowerUp:
 * Returns true if this object will produce a powerup when destroyed
 */
bool SpaceObject::powerUp() {
	return false;
}


/* isSpecial:
 * Returns true if object is a powerup. Is only true for the powerup class.
 */
bool SpaceObject::isSpecial() const {
	return false;
}


/* Collided:
 * If the object collides with something, this method is run to do
 * any special things necessary. Default is nothing.
 */
void SpaceObject::Collided( SpaceObject * who, ExplosionClass ** explr, int M_EX ) { 
	if ( hull ) hull->Collided();
}


/* acceptSpecial:
 * Returns true if the object can accept powerups. Should only be true for
 * the player class.
 */
bool SpaceObject::acceptSpecial() const {
	return false;
}


/* Died:
 * Called when the object dies, which technically means its hull->life is below 0.
 * If it goes offscreen and is out of the 'universe', the died method is not called and
 * the object is simply destroyed. The parameter 'check' is the object that will be
 * that the object affects when destroyed. Should always be a pointer to the player object.
 */
void SpaceObject::Died( SpaceObject * check, ExplosionClass ** explr, int ME ){
}


/* lookPlane:
 * Returns the drawing level of the object.
 * The drawing level determines in what order the object will be drawn. Lower
 * numbers will be drawn first, and higher numbers last. So far, the maximum
 * drawing level is 20 and the minimum is 1.
 */
 /*
int SpaceObject::lookPlane() {
	if ( !hull ) return 0;
	return hull->drawLevel;
}
*/


/* giveHull:
 * Destroys the hull the object currently contains and give is a new one.
 */
void SpaceObject::giveHull( HullObject * hnew ) {
	if ( hull ) delete hull;
	hull = hnew;
}


/* giveWeapon:
 * Gives the hull a new weapon at the specified weapon bay.
 * See hull.cpp for further details on this method.
 */
void SpaceObject::giveWeapon( WeaponObject * weap, int num ) {

	if ( !hull ){
		delete weap;
		return;
	}
	if ( num >= hull->maxGuns() || num < 0 ) return;
	hull->giveWeapon( weap, num );

}


/* eraseWeapon:
 * Destroys a weapon at the specified weapon bay.
 * See hull.cpp for further details on this method.
 */
void SpaceObject::eraseWeapon( int num ) {
	if ( hull )
		hull->eraseWeapon( num );
}


/* IncScore:
 * increments the score of the object. Mainly only used for the player
 * object as enemies dont need score. :P
 */
void SpaceObject::IncScore( int j ) {
	score += j;
}


/* Team:
 * returns the team that the object is on. So far, there are only two teams:
 * TEAM_ENEMY and TEAM_PLAYER. When an object produces another object, it will
 * always produce an object of the same TEAM.
 */
 /*
int SpaceObject::getTeam() {
	return alignment;
}
*/

void SpaceObject::savePosition(){
	save_ax = getX();
	save_ay = getY();
	save_vx = getVX();
	save_vy = getVY();
}

void SpaceObject::restorePosition(){
	setX( save_vx );
	setY( save_vy );
}
	
bool SpaceObject::hullCollide( ECollide * col, int x, int y ){	
	if ( hull ) return hull->hullCollide( col, getX(), getY(), x, y );
	return false;
}

/* Collide:
 * Returns true if this object has actually collided with 'check'.
 * See hull.cpp for further details on this method.
 */
bool SpaceObject::Collide( SpaceObject * check ){
	// if ( !CanbeHit( check ) ) return false;

	int mx1 = old_x;
	int my1 = old_y;
	int mx2 = getX();
	int my2 = getY();

	int ax1 = check->old_x;
	int ay1 = check->old_y;
	int ax2 = check->getX();
	int ay2 = check->getY();

	double cur_mx = mx1;
	double cur_my = my1;
	double my_slope = my2 - my1;
	double mx_slope = mx2 - mx1;

	double cur_ax = ax1;
	double cur_ay = ay1;
	double ay_slope = ay2 - ay1;
	double ax_slope = ax2 - ax1;

	int mtotal = (int)(fabs(my_slope) + fabs(mx_slope));
	int atotal = (int)(fabs(ay_slope) + fabs(ax_slope));

	int div = 1;
	if ( atotal > mtotal ){
		div = atotal / 3;
	} else {
		div = mtotal / 3;
	}
	div = atotal > mtotal ? (atotal>>1) : (mtotal>>1);
	if ( div == 0 ) div = 1;
	my_slope /= (double)div;
	mx_slope /= (double)div;
	ay_slope /= (double)div;
	ax_slope /= (double)div;

	check->savePosition();
	bool cy = false;
	// int count = 0;
	if ( div > 1 ){

		for ( int q = 0; q < div && !cy; q++ ){
			check->setX( cur_ax );
			check->setY( cur_ay );
			cy = hull->Collide( (int)cur_mx, (int)cur_my, check );
			cur_ax += ax_slope;
			cur_ay += ay_slope;
			cur_mx += mx_slope;
			cur_my += my_slope;

			// count++;
		}
	} else {
		cy = hull->Collide( (int)cur_mx, (int)cur_my, check );
	}
	// printf("Max counts = %d\n", count );
	
	check->restorePosition();
	return cy;

	// return hull->Collide( getX(), getY(), check );
}


/* getLife:
 * Returns the amount of life the hull currently has left.
 * See hull.cpp for further details about this method.
 */
double SpaceObject::getLife() const{
	if (!hull) return 0;
	return hull->GetLife();
}


/* Damage:
 * Forces the hull to take some damage. Before the hull takes the damage,
 * it is allowed to operate on the amount of damage taken with the
 * hull->Damage( int ) method. Mildly confusing, but hull->takeDamage will
 * always enforce the amount of damage taken while hull->Damage can change what
 * this number will be. Returns true if after life is less than or equal to 0
 * after damage is 0.
 */
bool SpaceObject::Damage( double much ) {
	if ( !hull ) return true;
	hull->takeDamage( hull->Damage( much ) );
	return ( getLife() <= 0 );
}


/*
void SpaceObject::Draw( const Bitmap & work, ExplosionClass ** _expl, int MAX_EXPLR, int g, int offset ) const{
	this->Draw( &work, _expl, MAX_EXPLR, g, offset );
}
*/

/* Draw:
 * Allows the object to draw itself on the specified Bitmap.
 * Will only draw if the drawLevel( g ) passed to it is equal to the
 * objects drawlevel.
 * See hull.cpp for further details on this method.
 */
void SpaceObject::Draw( const Bitmap & less, ExplosionClass ** _expl, int MAX_EXPLR, int g, int offset ) const{
	if ( hull ){
		if ( g == hull->drawLevel ) {
			// hull->Draw( less, actualx, actualy+offset );
			hull->Draw( less, getX(), getY() + offset );
		}
	}
}


/* Shadow:
 * Allows the object to draw its own shadow on the Bitmap.
 * Almost the same as the Draw method.
 */
void SpaceObject::Shadow( const Bitmap & less, int g, int offset ) const {
	if ( hull )
		if ( g == hull->drawLevel ) {
			// hull->Shadow( less, actualx, actualy+offset );
			hull->Shadow( less, getX(), getY() + offset );
		}
}


/* addCollide:
 * Adds the specified object to the list of objects this
 * object has already collided with.
 */
void SpaceObject::addCollide( SpaceObject * who ) {

	collide_list.push_back( who );

}


/* haveCollide:
 * Returns true if the object is in the list of objects
 * this object has already collided with.
 */
bool SpaceObject::haveCollide( const SpaceObject * who ) {
	for ( vector< SpaceObject * >::iterator it = collide_list.begin(); it != collide_list.end(); it++ ){
		if ( *it == who ) return true;
	}
	return false;
}


/* clearCollide:
 * Clears the list of objects this object has collided with.
 */
void SpaceObject::clearCollide() {

	collide_list.clear();

}


/* MoveReal:
 * Moves the object relative to its velocity. The equation is simple:
 * new x = old x + velocity x
 * new y = old y + velocity y
 */
void SpaceObject::MoveReal() {

	old_x = actualx;
	old_y = actualy;

	virtualx += dx;
	virtualy += dy;
	actualx = (int)virtualx;
	actualy = (int)virtualy;

}


/* SetCoordXY:
 * Sets the X and Y coordinates of the object in the universe.
 */
void SpaceObject::SetCoordXY( int ax, int ay ) {
	virtualx = ax;
	virtualy = ay;
	actualx = ax;
	actualy = ay;
}


/* group:
 * Returns the group associated with this object
 */
Group * SpaceObject::getGroup() {
	return my_group;
}


/* Radar:
 * Draws self on radar
 * Defualt is to not draw
 */
void SpaceObject::Radar( const Bitmap & rad ) const{
}


/* copy:
 * Returns a copy of the object with all the same points as this object
 */
SpaceObject * SpaceObject::copy() {
	return new SpaceObject( actualx, actualy, dx, dy, hull->copy(), my_group, plane, alignment );
	// return new SpaceObject( actualx, actualy, dx, dy, NULL, NULL, plane, alignment );
}

/* Independent:
 * Forces object to have no group
 */
void SpaceObject::Independent(){
	my_group = NULL;
}

/*
void SpaceObject::setX( int x ){
	actualx = x;
	virtualx = x;
}

void SpaceObject::setY( int y ){
	actualy = y;
	virtualy = y;
}

void SpaceObject::setX( double x ){
	actualx = (int)x;
	virtualx = x;
}

void SpaceObject::setY( double y ){
	actualy = (int)y;
	virtualy = y;
}
*/

void SpaceObject::setDX( double x ){
	dx = x;
}

void SpaceObject::setDY( double y ){
	dy = y;
}

void SpaceObject::setAccelX( double x ){
	accel_x = x;
}

void SpaceObject::setAccelY( double y ){
	accel_y = y;
}

void SpaceObject::setScore( int s ){
	score = s;
}

void SpaceObject::setStrength( int s ){
	str = s;
}

void SpaceObject::setPlane( int p ){
	plane = p;
}

void SpaceObject::setAlignment( int a ){
	alignment = a;
}
	
HullObject * SpaceObject::getHull() const{
	return hull;
}
	
int SpaceObject::getMaxX(){
	if ( hull )
		return hull->getWidth();
	return 0;
}

int SpaceObject::getMaxY(){
	if ( hull )
		return hull->getHeight();
	return 0;
}

/*
int SpaceObject::getX(){
	return actualx;
}

int SpaceObject::getY(){
	return actualy;
}

double SpaceObject::getVX(){
	return virtualx;
}

double SpaceObject::getVY(){
	return virtualy;
}

int SpaceObject::getScore(){
	return score;
}

int SpaceObject::getStrength(){
	return str;
}

int SpaceObject::getPlane(){
	return plane;
}

int SpaceObject::getAlignment(){
	return alignment;
}
*/

/* Destructor:
 * Deletes the hull and the collide list.
 */
SpaceObject::~SpaceObject() {
	if ( hull != NULL ) delete hull;	  //delete hull
	//collide_list->clear();
	// delete collide_list;

	//delete the group that contains this object if there is one
	if ( my_group != NULL ) {
		my_group->drop( this );

		//if group is empty, delete the group
		if ( my_group->size() == 0 ) {
			delete my_group;
		}
	}
}
