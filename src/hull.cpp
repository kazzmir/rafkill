#include "defs.h"
#include "hull.h"
#include "trigtable.h"
#include "spaceobj.h"
#include "gunobj.h"
#include "ebox.h"
#include "section.h"
#include "bitmap.h"

#include <iostream>

using namespace std;

/* Constructor:
 * parameters are:
 * _drawNum - the drawing number of the object. Used for determing which Bitmap
 * out of the datafile to draw from.
 * _life - the amount of life of the object
 * _strength - the amount of damage the object will do when it collides with something
 * num_guns - the maximum number of guns allowed in this object
 * level - the level number of the game
 * _drawing_plane - the drawing level of the object
 * ec - an ECollide object use for collision detection.
 */
HullObject::HullObject( Bitmap * _drawBitmap, double _life, double _strength, int num_guns, int level, int _drawing_plane, bool _trans, ECollide * ec):
crash( false ),
trans( _trans ),
drawLevel( _drawing_plane ),
guns( NULL ),
strength( _strength ),
max_guns( num_guns ) {
	myBitmap = _drawBitmap;
	Shadow_Bitmap = NULL;
	if ( myBitmap != NULL )
		Shadow_Bitmap = getShadow();
	life = _life;
	original_life = _life;
	collide = ec;
	//life = (int)( (double)l * ( 1.0 + (double)level / 3.8 ) );
	guns = NULL;
	if ( max_guns != 0 ) {
		guns = new WeaponObject*[ max_guns ];
		for ( int q = 0; q < max_guns; q++ )
			guns[q] = NULL;
	}
	dx = 0;
	dy = 0;
}


/* setLife:
 * Sets the life of the object according to a parameter, zx, which
 * usually refers to the game level give in the constructor.
 */
void HullObject::setLife( double zx ) {
	life = zx;
	/*
	//life = (int)( (double)life * ( 1.0 + (double)zx / 3.1 ) );
	life = (double)life * ( 1.0 + (double)zx / 3.1 );
	original_life = life;
	*/
}


/* Moved:
 * Called the container object, spaceobject, has its method MoveMe called.
 * Default is to do nothing.
 */
void HullObject::Moved( double _dx, double _dy, double _ax, double _ay ) {

	dx = _dx;
	dy = _dy;

}


/* Hurt:
 * Returns the amount of damage the object will do when it collides with something.
 */
double HullObject::Hurt() {
	return strength;
}

/*
int HullObject::getHeight(){
	if ( Bitmap ) return Bitmap->h;
	if ( collide ) return collide->getHeight();
	return 0;
}

int HullObject::getWidth(){
	if ( Bitmap ) return Bitmap->w;
	if ( collide ) return collide->getWidth();
	return 0;
}
*/

/*
int HullObject::getLife(){
	return (int)life;
}
*/

/* Draw:
 * Draws the object onto the specified Bitmap. For most objects, this will
 * consist of drawing the Bitmap at data[ drawNum ] at the
 * X coordinate - half the width of the bitamp and the
 * Y coordinate - half the height of the Bitmap. If the object does not have a Bitmap
 * to draw from, it needs to override this method with its own drawing routine.
 */
void HullObject::Draw( const Bitmap & who, int x, int y ) {
	//int mx = ((Bitmap *)dat[ drawNum ].dat)->w/2;
	//int my = ((Bitmap *)dat[ drawNum ].dat)->h/2;
	//draw_character(who, (Bitmap *)dat[drawNum].dat, x-mx+mx*3/2, y-my+my*3/2, makecol(30,30,30) );
	//draw_trans_sprite( who, (Bitmap *)dat[ drawNum ].dat, x-mx+mx*5/4, y-my+my*3/2 );
	//draw_sprite( who, (Bitmap *)dat[ drawNum ].dat, x-mx, y-my );
	if ( myBitmap == NULL ) return;
	int mx = myBitmap->getWidth()/2;
	int my = myBitmap->getHeight()/2;

	if ( trans )
		myBitmap->drawTrans( x-mx, y-my, who );
	else
		myBitmap->draw( x-mx, y-my, who ); 
		
	/*
	if ( collide ){
		collide->draw( who, x-mx, y-my );
	}
	*/

}

Bitmap * HullObject::getShadow(){
	
	if ( Shadow_Bitmap == NULL && myBitmap != NULL ){

		// Shadow_Bitmap = create_Bitmap( Bitmap->w, Bitmap->h );
		Shadow_Bitmap = new Bitmap( myBitmap->getWidth(), myBitmap->getHeight() );
		//clear_to_color( Shadow_Bitmap, makecol(255,0,255) );
		//draw_lit_sprite( Shadow_Bitmap, Bitmap, 0, 0, 255 );
		int m = 35;
		// clear_to_color( Shadow_Bitmap, makecol(m,m,m) );
		Shadow_Bitmap->fill( Bitmap::makeColor(m,m,m) );
		//draw_character( Shadow_Bitmap, Bitmap, 0, 0, 1 );


		// draw_mask( Shadow_Bitmap, Bitmap, 0, 0 );
		if ( myBitmap )
			myBitmap->drawMask( 0, 0, *Shadow_Bitmap );
		
	}

	return Shadow_Bitmap;
}

/* Shadow:
 * Draws a shadow of the picture almost the same as the Draw() method except
 * using draw_lit_sprite instead.
 */
void HullObject::Shadow( const Bitmap & who, int x, int y ) {
	if ( (Shadow_Bitmap = getShadow()) == NULL ) return;

	/*
		int mx = Bitmap->w/2;
		int my = Bitmap->h/2;
		int tx = (x - mx) - ( screen_x/2 - (x-mx) ) / 9;
		int ty = ( screen_y/2 + (y-my) ) / 15 + y-my;
		ty = y + my;
		draw_lit_sprite( who, Bitmap, tx, ty, 255 );
	*/

	Shadow_Bitmap = getShadow();

	int mx = Shadow_Bitmap->getWidth()/2;
	int my = Shadow_Bitmap->getHeight()/2;
	// mx = 0;
	my = Shadow_Bitmap->getHeight() / 3;
	int tx = (x - mx) - ( Util::screen_x/2 - (x-mx) ) / 9;
	int ty = y + my;

	Shadow_Bitmap->drawTrans( tx, ty, who );

	/* TODO: fix */
	// draw_trans_sprite( who, Shadow_Bitmap, tx, ty );

	//draw_lit_sprite( who, Bitmap, (int)(x-mx+dx*9), (int)(y-my+dy*9), 250 );
	//fblend_add( (Bitmap *)dat[ drawNum ].dat, who, (int)(x-mx+dx*11), (int)(y-my+dy*11), 20 );
}


/* Inside:
 * Returns true if the specified coordinate (ax,ay) is within the
 * space of the hull centered at (mx,my)
 * See ebox.cpp for further details on the Single() method.
 */
bool HullObject::Inside( int mx, int my, int ax, int ay ) {
	// if ( collide ) return collide->Single( mx, my, ax, ay );
	if ( collide ) return collide->Collision( mx, my, ax, ay );
	return ( mx == ax && my == ay );
}


/* giveWeapon:
 * Gives the hull a gunobject at the specified bay.
 * WARNING: does not delete the previous object. To do this call
 * eraseweapon.
 */
void HullObject::giveWeapon( WeaponObject * weap, int num ) {
	guns[ num ] = weap;
}


/* eraseWeapon:
 * Deletes the object at the specified bay.
 * Sets the bay to NULL.
 */
void HullObject::eraseWeapon( int num ) {
	if ( num < 0 || num >= max_guns ) return;
	if ( guns[num] != NULL ) delete guns[num];
	guns[num] = NULL;
}

bool HullObject::hullCollide( ECollide * col, int mx, int my, int ax, int ay ){

	if ( col && collide )
		return collide->Collision( col, mx-getWidth()/2, my-getHeight()/2, ax, ay );

	return Inside( mx-getWidth()/2, my-getHeight()/2, ax, ay );

}

/* Collide:
 * Can only detect a collision if this object and the other object have a
 * collide object in it. Returns true if ECollide->Collision() returns true.
 * See ebox.cpp for further details.
 */
bool HullObject::Collide( int mx, int my, SpaceObject * check ) {

	return check->hullCollide( collide, mx-getWidth()/2, my-getHeight()/2 );

	/*
	if ( collide && check->getHull() && check->getHull()->collide )
		return collide->Collision( check->getHull()->collide, mx, my, check->getX(), check->getY() );
	*/
	//return check->HitMe( mx, my );
	return false;
}


/* debug:
 * Debugging crap for knowing where the object is on the screen.
 */
 /*
void HullObject::debug( Bitmap * work, int x, int y ) {
	circlefill( work, x, y, 4, makecol(255,255,255) );
}
*/


/* guns:
 * Returns the array of weaponobjects the object contains.
 */
WeaponObject ** HullObject::Guns() {
	return guns;
}


/* maxGuns:
 * Returns the maximum number of guns the object can possibly contain.
 */
int HullObject::maxGuns() {
	return max_guns;
}


/* haveBeenHit:
 * Returns true if the hull has collided with something since the last call to
 * haveBeenHit. The flag is initially false, so the first call will return true
 * the first time the hull collides with something.
 */
bool HullObject::haveBeenHit() {
	bool cy = crash;
	crash = false;
	return cy;
}


/* addSection:
 * Puts the object into the Section object which is used for speeding up
 * collision detection. This is calculated by determining the upper most corner
 * and the lower most corner. Given this height, each y coordinate in a specific range
 * given by Section->spacer() will be used to add the object into the Section's database
 * of objects it should know about. The object will not add itself if it is translucent.
 * See section.cpp for further details about this method.
 */
void HullObject::addSection( SpaceObject * who, Section * onscreen, int x, int y ) {

	if ( Translucent() ) return;
	if ( onscreen == NULL ) return;

	int y1 = y;
	int y2 = y;
	int x1 = x;
	int x2 = x;
	if ( collide ) {
		/*
		y1 = collide->CY1( collide->ul_y + y );
		y2 = collide->CY1( collide->lr_y + y );
		*/
		y1 = collide->getMinHeight() + y - getHeight()/2;
		y2 = collide->getMaxHeight() + y - getHeight()/2;
		x1 = collide->getMinWidth() + x - getWidth()/2;
		x2 = collide->getMaxWidth() + x - getWidth()/2;
	}

	/*
	onscreen->add( who, x, y1 );
	for ( int q = y1+onscreen->spacer(); q < y2; q += onscreen->spacer() )
		onscreen->add( who, x, q );
	if ( y2 != y1 )
		onscreen->add( who, x, y2 );
	*/

	for ( int ay = y1; ay <= y2; ay += onscreen->spacerY() )
		for ( int ax = x1; ax <= x2; ax += onscreen->spacerX() )
			onscreen->add( who, ax, ay );
	/*
	for ( int ay = y1; ay <= y2; ay += onscreen->spacer() )
		onscreen->add( who, x, ay );
	*/

}


/* takeDamage:
 * Enforces that the hull take so much damage. This method SHOULD NOT be overwritten.
 */
void HullObject::takeDamage( double r ) {
	life -= r;
}


/* Damage:
 * Allows the hull to operate on how much damage it is going to take.
 * Default is to just take the damage specified.
 */
double HullObject::Damage( double much ) {
	return much;
}


/* GetLife:
 * Returns how much life this object has left.
 */
double HullObject::GetLife() {
	return life;
}


/* Translucent:
 * Returns true if the object is translucent. Translucent means that it cannot
 * collide with any other object.
 */
bool HullObject::Translucent() {
	return trans;
}


/* Collided:
 * Does something when hull collides with another hull
 */
void HullObject::Collided() {
}


HullObject * HullObject::copy() {

	HullObject * who = new HullObject( myBitmap, life, strength, this->maxGuns(), 1, drawLevel, trans, collide );
	for ( int q = 0; q < this->maxGuns(); q++ )
		if ( this->Guns()[q] != NULL )
			who->guns[q] = this->Guns()[q]->copy();
	else    who->guns[q] = NULL;
	return who;
}


/* Destructor:
 * Deletes all the guns the object contains.
 * WARNING: does not delete the ECollide object, this must be done elsewhere.
 */
HullObject::~HullObject() {
	
	if ( guns != NULL ) {
		for ( int q = 0; q < max_guns; q++ )
			if ( guns[q] != NULL )
				delete guns[q];
		delete[] guns;
	}
	// if ( Shadow_Bitmap ) destroy_Bitmap( Shadow_Bitmap );
	if ( Shadow_Bitmap ){
		delete Shadow_Bitmap;
	}
	if ( myBitmap ){
		delete myBitmap;
	}
}
