#include "defs.h"
#include "hull_player.h"
#include "hull_rotate.h"
#include "ebox.h"
#include "section.h"
#include "bitmap.h"
#include "gunobj.h"
#include <vector>
#include <stdio.h>
#include <iostream>

#ifndef debug
#define debug cout << "File: " << __FILE__ << " Line: " << __LINE__ << endl
#endif

using namespace std;

// #define MAX_INTERNAL_DAMAGE 30

PlayerHull::PlayerHull( const vector< Bitmap * > & _pics, int _maxlife, int _maxshield, int _number_of_guns, int _hull_number, ECollide * eb ):
HullObject( NULL, _maxlife, SHIP_DAMAGE, _number_of_guns, 1, 10, false, eb ),
shield( 0 ),
cloak( 0 ),
MAX_SHIELD( _maxshield ),
MAX_LIFE( _maxlife ),
hull_num( _hull_number ),
internal_damage( 0 ),
current_accessory( 0 ),
animation_pic( pics.size()/2 ){
	pics = _pics;
	max_pics = pics.size();

	// pics_shadow = new Bitmap*[ max_pics ];
	for ( vector< Bitmap * >::iterator it = pics.begin(); it != pics.end(); it++ ){
		Bitmap * o = *it;
		Bitmap * s = new Bitmap( o->getWidth(), o->getHeight() );
		s->fill( Bitmap::makeColor(22,22,22) );
		o->drawMask( 0, 0, *s );
		pics_shadow.push_back( s );
	}
	
	myBitmap = NULL;

	if ( ! pics.empty() ){
		myBitmap = pics[ max_pics / 2 ];
	}

	for ( int q = 0; q < MAX_ROTATE; q++ ) {
		rotate[q] = NULL;
		rotate_damage[q] = NULL;
	}

	// shade_damage = new int[ MAX_INTERNAL_DAMAGE ];
	Util::blend_palette( shade_damage, MAX_INTERNAL_DAMAGE*3/5, Bitmap::makeColor(5,5,20), Bitmap::makeColor(60,60,250) );
	Util::blend_palette( shade_damage+MAX_INTERNAL_DAMAGE*3/5, MAX_INTERNAL_DAMAGE-MAX_INTERNAL_DAMAGE*3/5, Bitmap::makeColor(60,60,250), Bitmap::makeColor(255,255,255) );

	for ( int q = 0; q < MAX_ACCESSORY; q++ )
		accessory[q] = NULL;

	true_guns = new WeaponObject*[ _number_of_guns + 1 ];
}


PlayerHull::~PlayerHull() {


	for ( int q = 0; q < MAX_ROTATE; q++ ) {

		if ( rotate[q] != NULL ){
			delete rotate[q];
		}

		if ( rotate_damage[q] != NULL ){
			delete rotate_damage[q];
		}
	}

	for ( int q = 0; q < MAX_ACCESSORY; q++ ){
		if ( accessory[q] != NULL ){
			delete accessory[q];
		}
	}
	
	for ( vector< Bitmap * >::iterator it = pics.begin(); it != pics.end(); it++ ){
		delete *it;
	}

	for ( vector< Bitmap * >::iterator it = pics_shadow.begin(); it != pics_shadow.end(); it++ ){
		delete *it;
	}
	
	if ( collide ){
		delete collide;
	}

	// delete[] shade_damage;
	delete[] true_guns;

	// delete[] pics;
	// delete pics;
	/*
	Util::debug;
	*/

	/* dont let ~Hull() delete these special member variables */
	Shadow_Bitmap = NULL;
	myBitmap = NULL;
}


HullObject * PlayerHull::copy() {

	/*
	Bitmap ** s_pics = new Bitmap*[ max_pics ];
	for ( int q = 0; q < max_pics; q++ )
		s_pics[q] = pics[q];
	*/

	vector< Bitmap * > newPics;
	for ( vector< Bitmap * >::iterator it = pics.begin(); it != pics.end(); it++ ){
		Bitmap * bitmap = *it;
		newPics.push_back( new Bitmap( *bitmap, false ) );
	}

	HullObject * who = new PlayerHull( newPics, MAX_LIFE, MAX_SHIELD, this->maxGuns()-1, hull_num, collide->copy() );
	PlayerHull * playerHull = (PlayerHull *) who;

	playerHull->life = getLife();
	playerHull->shield = getShield();

	for ( int q = 0; q < this->maxGuns()-1; q++ ){
		if ( this->Guns()[q] != NULL ){
			playerHull->giveWeapon( this->Guns()[q]->copy(), q );
		}
	}

			// who->Guns()[q] = this->Guns()[q]->copy();
	// else    who->Guns()[q] = NULL;

	for ( int q = 0; q < MAX_ACCESSORY; q++ ){
		if ( this->accessory[q] != NULL ){
			playerHull->accessory[q] = this->accessory[q]->copy();
		}
	}
	// else    ((PlayerHull *)who)->accessory[q] = NULL;

	return who;
}

const int PlayerHull::getShield() const{
	return (int)shield;
}
	
void PlayerHull::setShields( int s ){
	shield = s;
	if ( shield < 0 ) shield = 0;
	if ( shield > getMaxShield() ) shield = getMaxShield();
}

void PlayerHull::incShield( int q ){
	shield += q;
	if ( shield > getMaxShield() ) shield = getMaxShield();
}

void PlayerHull::Moved( double _dx, double _dy, double _ax, double _ay ) {
	if ( cloak > 0 ) cloak--;

	/*
	if ( _dx < 0 && animation_pic > 0 )
		animation_pic--;
	if ( _dx > 0 && animation_pic < max_pics-1 )
		animation_pic++;
	if ( _dx == 0 ){

		if ( animation_pic < max_pics/2 ) animation_pic++;
		else if ( animation_pic > max_pics/2 ) animation_pic--;
		
	}
	*/
	if ( _ax > 0 && animation_pic < max_pics-1 )
		animation_pic++;
	if ( _ax < 0 && animation_pic > 0 )
		animation_pic--;
	if ( _ax == 0 ){
		if ( animation_pic < max_pics/2 ) animation_pic++;
		else if ( animation_pic > max_pics/2 ) animation_pic--;
	}
	
	HullObject::Moved(_dx,_dy,_ax,_ay);
}

int PlayerHull::getMaxLife(){
	return MAX_LIFE;
}

int PlayerHull::getMaxShield(){
	return MAX_SHIELD;
}

/*
int PlayerHull::max( int q ) {
	switch( q ) {
		case 0  :       return MAX_LIFE;
		case 1  :       return MAX_SHIELD;
	}
	return 0;
}
*/


int PlayerHull::rank() {
	return hull_num;
}


void PlayerHull::addSection( SpaceObject * who, Section * onscreen, int x, int y ) {
	if ( cloak > 0 ) return;
	HullObject::addSection( who, onscreen, x, y );

	/*

	if ( Translucent() ) return;
	if ( onscreen == NULL ) return;

	int y1 = y;
	int y2 = y;
	if ( collide ) {
		y1 = collide->CY1( collide->ul_y + y );
		y2 = collide->CY1( collide->lr_y + y );
	}

	onscreen->add( who, x, y1 );
	for ( int q = y1+onscreen->spacer(); q < y2; q += onscreen->spacer() )
	onscreen->add( who, x, q );
	if ( y2 != y1 )
	onscreen->add( who, x, y2 );
	*/

}


int PlayerHull::maxGuns() {
	return max_guns+1;
}


WeaponObject ** PlayerHull::Guns() {
	for ( int q = 0; q < maxGuns()-1; q++ ){
		true_guns[q] = HullObject::Guns()[q];
	}
	true_guns[ maxGuns()-1 ] = accessory[ current_accessory ];

	return true_guns;
}


WeaponObject ** PlayerHull::Accessories() {
	return accessory;
}


void PlayerHull::NextAccessory() {

	//if ( pcount( (char **)accessory, MAX_ACCESSORY ) == 0 ) return;

	int old = current_accessory;
	for ( old = current_accessory+1; old != current_accessory; old %= MAX_ACCESSORY ) {
		if ( accessory[old] != NULL ) {
			current_accessory = old;
		} else old++;
	}

}


void PlayerHull::giveWeapon( WeaponObject * weap, int num ) {

	if ( num < maxGuns()-1 ) {
		guns[ num ] = weap;
		return;
	}

	for ( int q = 0; q < MAX_ACCESSORY; q++ )
	if ( accessory[q] == NULL ) {
		accessory[q] = weap;
		return;
	}
}

Bitmap * PlayerHull::getShadow(){
	return pics_shadow[ animation_pic ];
}

/*
void PlayerHull::Shadow( Bitmap * who, int x, int y ) {
	//int mx = ((Bitmap *)dat[ drawNum ].dat)->w/2;
	//int my = ((Bitmap *)dat[ drawNum ].dat)->h/2;
	//draw_lit_sprite( who, (Bitmap *)dat[ drawNum ].dat, (int)(x-mx+dx), (int)(y-my+dy), 250 );
	Bitmap = pics[ animation_pic ];
	//int mx = Bitmap->w/2;
	//int my = Bitmap->h/2;
	//draw_lit_sprite( who, Bitmap, (int)(x-mx+dx), (int)(y-my+dy), 250 );
	HullObject::Shadow( who, x, y );
}
*/

void PlayerHull::Draw( const Bitmap & who, int x, int y ) {

	if ( pics.empty() ){
		return;
	}

	//int xpl = ((Bitmap *)dat[ drawNum ].dat)->w;
	//int ypl = ((Bitmap *)dat[ drawNum ].dat)->h;
	
	myBitmap = pics[ animation_pic ];
	int xpl = myBitmap->getWidth();
	int ypl = myBitmap->getHeight();

	if ( internal_damage ) {
		internal_damage--;

		for ( int q = 0; q < MAX_ROTATE; q++ ) {
			if ( rotate_damage[q] == NULL )
				rotate_damage[q] = new RotateHull(MAX_INTERNAL_DAMAGE,xpl,ypl,7,shade_damage);
			if ( rotate_damage[q] )
				rotate_damage[q]->color = internal_damage;
		}

	} else {
		for ( int q = 0; q < MAX_ROTATE; q++ ){
			if ( rotate_damage[q] ) {
				delete rotate_damage[q];
				rotate_damage[q] = NULL;
			}
		}
	}

	for ( int q = 0; q < MAX_ROTATE; q++ ){
		if ( shield <= MAX_SHIELD*q/MAX_ROTATE && rotate[q] != NULL ) {
			delete rotate[q];
			rotate[q] = NULL;
		}
	}

	for ( int q = 0; q < MAX_ROTATE; q++ ){
		if ( shield > MAX_SHIELD*q/MAX_ROTATE && rotate[q] == NULL )
			rotate[q] = new RotateHull( ( MAX_E_COLOR - 1 ) * ( q + 1 ) / MAX_ROTATE, xpl, ypl, 15, Util::e_color );
	}

	if ( cloak == 0 ){
		HullObject::Draw( who, x, y );
	} else {
		//int mx = ((Bitmap *)dat[ drawNum ].dat)->w/2;
		//int my = ((Bitmap *)dat[ drawNum ].dat)->h/2;
		//draw_trans_sprite( who, (Bitmap *)dat[ drawNum ].dat, x-mx, y-my );
		//draw_lit_sprite( who, (Bitmap *)dat[ drawNum ].dat, x-mx, y-my, 150 );
		int mx = xpl/2;
		int my = ypl/2;

		// draw_lit_sprite( who, Bitmap, x-mx, y-my, 150 );
		myBitmap->drawLit( x-mx, y-my, 150, who );
	}
	
	for ( int q = 0; q < MAX_ROTATE; q++ ) {
		if ( rotate[q] != NULL ){
			rotate[q]->Draw( who, x, y );
		}
		if ( rotate_damage[q] != NULL ){
			rotate_damage[q]->Draw( who, x, y );
		}
	}

}


void PlayerHull::frameLeft() {
	if ( animation_pic > 0 ) animation_pic--;
}


void PlayerHull::frameRight() {
	if ( animation_pic < max_pics-1 ) animation_pic++;
}


void PlayerHull::frameStable() {
	if ( animation_pic < max_pics / 2 ) animation_pic++;
	if ( animation_pic > max_pics / 2 ) animation_pic--;
}


double PlayerHull::Damage( double r ) {

	double dam = 0;
	if ( r > shield ) {
		shield = 0;
		dam = r-shield;
	} else shield -= r;

	if ( dam > 0 )
		internal_damage = MAX_INTERNAL_DAMAGE;
	return dam;
	//life -= dam;

}


void PlayerHull::drawGun( const Bitmap & who, int x, int y ) {
}


/*
void PlayerHull::showAttribute( Bitmap * who, int amount, int MAX, int start_x, int offset ) {
	#define start_attr 470
	for ( int z = 0; z < amount; z++ ) {
		int base = expl_color - 60;
		base += z * 60 / MAX;
		int start = start_attr * z / MAX;
		base = (int)( (double)z / (double)MAX * (double)(MAX_E_COLOR-15) + 15 );
		rectfill( who, start_x, start_attr-start+offset, start_x+9, start_attr-start+1+offset, e_color[base] );
	}
}
*/
