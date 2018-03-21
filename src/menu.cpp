#include <stdio.h>
#include "defs.h"
#include "menu.h"
#include "loadsave.h"
#include "trigtable.h"
#include "strings_util.h"
#include <string.h>
#include "animation.h"
#include "spaceobj.h"
#include "shipobj.h"
#include "sound.h"
#include "font.h"
#include "rmenu.h"
#include "rmenu_animation.h"
#include "raptor.h"
#include "hull.h"
#include "hulls/hull_player.h"
#include "ebox.h"
#include <time.h>
#include <sys/time.h>
#include "music.h"
#include <iostream>
#include <stdlib.h>

#include <vector>

using namespace std;

#include "guns/gun_arc.h"
#include "guns/gun_angle.h"
#include "guns/gun_beam.h"
#include "guns/gun_chain.h"
#include "guns/gun_destruct.h"
#include "guns/gun_edfstraight.h"
#include "guns/gun_ednstraight.h"
#include "guns/gun_eflarge.h"
#include "guns/gun_efmsingle.h"
#include "guns/gun_efsingle.h"
#include "guns/gun_elarge.h"
#include "guns/gun_emissle.h"
#include "guns/gun_emlight.h"
#include "guns/gun_eside.h"
#include "guns/gun_estraight.h"
#include "guns/gun_findgun.h"
#include "guns/gun_fire.h"
#include "guns/gun_follow.h"
#include "guns/gun_laser.h"
#include "guns/gun_machine.h"
#include "guns/gun_machine_circle.h"
#include "guns/gun_minimissle.h"
#include "guns/gun_missle.h"
#include "guns/gun_pulse.h"
#include "guns/gun_shatter.h"
#include "guns/gun_spread.h"
#include "guns/gun_stick.h"
#include "guns/gun_yehat.h"
#include "guns/gun_swirl.h"
#include "guns/gun_massive.h"
#include "guns/gun_saber.h"
#include "guns/gun_tractor_beam.h"
#include "guns/gun_rotate.h"

#define MENU_BUY 7
#define MENU_QUIT 843
#define MENU_NEXT 844
#define MENU_CONTINUE 4321
#define MENU_WEAPON 9002
#define MENU_HULL 9003

#define MENU_SELL_WEAPON 30
#define MENU_UPGRADE 321
#define MENU_BUY_WEAPON 56
#define MENU_BUY_ACCESSORY 600

#define MENU_SAVE 14000

#define MENU_HULL_LIFE 12000
#define MENU_HULL_SHIELD 12001
#define MENU_BUY_HULL 12005
#define MENU_HULL_MAX 12006
#define MENU_SHIELD_MAX 12007

#define HULL_LIFE_WORTH 1000
#define HULL_SHIELD_WORTH 3000

static const int INCREASE_SHIELD = 3;

#define ANIMATION_X 180

#define MENU_TITLE_COLOR (Bitmap::makeColor(240,205,7))

#ifndef debug
#define debug printf("File: %s Line: %d\n", __FILE__, __LINE__ );
#endif

static const int NO_SOUND = -1;

/* TODO:
 * This whole class needs to be rewritten. It sucks!
 */

menuClass::menuClass() {

	menuClass::gun_sticky_collide_list = NULL;

	pgun[0].mgun = 4;
	pgun[0].gunz = new int[ pgun[0].mgun ];
	pgun[0].gunz[0] = GUN_MACHINE;
	pgun[0].gunz[1] = GUN_MACHINE_CIRCLE;
	pgun[0].gunz[2] = GUN_SPREAD;
	pgun[0].gunz[3] = GUN_ANGLE;

	pgun[1].mgun = 4;
	pgun[1].gunz = new int[ pgun[1].mgun ];
	pgun[1].gunz[0] = GUN_BEAM;
	pgun[1].gunz[1] = GUN_MINIMISSLE;
	pgun[1].gunz[2] = GUN_SHATTER;
	pgun[1].gunz[3] = GUN_YEHAT;

	pgun[2].mgun = 3;
	pgun[2].gunz = new int[ pgun[2].mgun ];
	pgun[2].gunz[0] = GUN_ARC;
	pgun[2].gunz[1] = GUN_LASER;
	pgun[2].gunz[2] = GUN_STICKY;

	pgun[3].mgun = 2;
	pgun[3].gunz = new int[ pgun[3].mgun ];
	pgun[3].gunz[0] = GUN_MISSLE;
	pgun[3].gunz[1] = GUN_PULSE;

	pgun[4].mgun = 3;
	pgun[4].gunz = new int[ pgun[4].mgun ];
	pgun[4].gunz[0] = GUN_FINDGUN;
	pgun[4].gunz[1] = GUN_FOLLOW;
	pgun[4].gunz[2] = GUN_TRACTOR;

	agun.mgun = 4;
	agun.gunz = new int[ agun.mgun ];
	agun.gunz[0] = GUN_SABER;
	agun.gunz[1] = GUN_SWIRL;
	agun.gunz[2] = GUN_CHAIN;
	agun.gunz[3] = GUN_MASSIVE;

	/*
	char * font_name = Util::data_file( "vulture.fnt" );
	// menuFont = new RFont( font_name );
	free( font_name );
	*/

	if ( menuClass::gun_sticky_collide_list == NULL ){
		menuClass::gun_sticky_max_collide = 20;
		menuClass::gun_sticky_collide_list = new ECollide*[ menuClass::gun_sticky_max_collide ];
		for ( int q = 0; q < menuClass::gun_sticky_max_collide; q++ ) {
			int size = 6;
			Bitmap temp( (size + q * size)*2, (size + q * size)*2 );
			temp.fill( Bitmap::MaskColor );
			temp.circleFill( size + q * size, size + q * size, size + q * size, Bitmap::makeColor(255,0,0) );
			// menuClass::gun_sticky_collide_list[q] = new ECollide( temp, 3, mask, 35.0 );
			menuClass::gun_sticky_collide_list[q] = new ECollide( temp );
		}
	}

}


menuClass::~menuClass() {
	for ( int q = 0; q < 5; q++ )
		delete[] pgun[q].gunz;
	delete[] agun.gunz;
	// delete menuFont;

	if ( menuClass::gun_sticky_collide_list != NULL ){
		for ( int q = 0; q < menuClass::gun_sticky_max_collide; q++ )
			delete menuClass::gun_sticky_collide_list[q];
		delete[] menuClass::gun_sticky_collide_list;
	}
}


void menuClass::vectorAdd( vector< SpaceObject * > * stable, vector< SpaceObject * > * state ) {

	for ( vector< SpaceObject * >::iterator it = state->begin();
		it != state->end(); it++ )
	stable->push_back( *it );

}


void menuClass::getAnimation( Animation * hold, SpaceObject * player, vector< SpaceObject * > * ammo, vector< SpaceObject * > * enemy ) {

	player->SetCoordXY( ANIMATION_X/2, 350 );

	player->setDX( 0 );
	player->setDY( 0 );
	/*
	player->getDX() = 0;
	player->getDY() = 0;
	*/
	//hold->clear();

	// for ( int z = 0; z < 1; z++ ) {

		for ( vector< SpaceObject * >::iterator it = ammo->begin(); it != ammo->end(); ) {
			(*it)->MoveMe( ammo, enemy, NULL );
			// if ( (*it)->MoveMe( ammo, enemy, NULL, NULL ) ) {
			int x = (*it)->getX();
			int y = (*it)->getY();
			if ( x < 0 || x > GRAPHICS_X || y < 0 || y > GRAPHICS_Y ){
				SpaceObject * del = *it;
				it = ammo->erase( it );
				delete del;
			} else it++;
		}


		for ( vector< SpaceObject * >::iterator it = ammo->begin(); it != ammo->end(); ) {
			if ( (*it)->getLife() <= 0 ) {
				SpaceObject * del = *it;
				it = ammo->erase( it );
				delete del;
			} else ++it;
		}
	// }


	WeaponObject ** myGun = player->getHull()->Guns();
	for ( int q = 0; q < player->getHull()->maxGuns(); q++ )
	if ( myGun[q] != NULL ) {
		if ( myGun[q]->getShotCounter() > 0 )
			myGun[q]->Wait( 1 );
		else {
			myGun[q]->MakeShot(player->getX(),player->getY()-10,ammo,enemy);
		}
	}

	// vector< SpaceObject * > * draw = new vector< SpaceObject * >();
	vector< SpaceObject * > draw;
	vectorAdd( &draw, ammo );
	draw.push_back( player );
	//BITMAP * add_b = create_bitmap( ANIMATION_X, GRAPHICS_Y );
	const Bitmap & add_b = player_animate->show();
	add_b.clear();

	int total = 0;
	for ( vector< SpaceObject * >::iterator it = draw.begin(); it != draw.end(); it++, total++ ){
		(*it)->Draw( add_b, NULL, 0, (*it)->lookPlane(), 0 );
	}

	/* draw a white fading to grey border */
	for ( int z = 0; z < 7; z++ ) {

		int d = 11;
		int col = Bitmap::makeColor(255-z*d,255-z*d,255-z*d);
		add_b.rectangle( z, z, ANIMATION_X-z-1, GRAPHICS_Y-z-1, col );

	}

	// delete draw;

}


Bitmap menuClass::menuScreen() {

	// int * shade = new int[ 100 ];
	int shade[ 100 ];

	Util::blend_palette( shade, 100, Bitmap::makeColor( Util::rnd(50)+20, Util::rnd(40)+50, Util::rnd(50)+170 ), Bitmap::makeColor( Util::rnd(40)+190, Util::rnd(128)+128, Util::rnd(30)+10 ) );
	Bitmap rec( GRAPHICS_X, GRAPHICS_Y );

	int divx = 3;
	double mmx = tsqrt( tsqr(GRAPHICS_X) + tsqr(GRAPHICS_Y) );
	for ( int x = 0; x < GRAPHICS_X / divx; x++ ){
		for ( int y = 0; y < GRAPHICS_Y / divx; y++ ) {
			double ma = (double)tsqrt( tsqr(x*divx) + tsqr(y*divx) ) / mmx * 99.0;
			rec.rectangleFill( x*divx, y*divx, x*divx+divx-1, y*divx+divx-1, shade[(int)ma] );
		}
	}

	// delete[] shade;

	return rec;
}


int menuClass::upgradeHelper( int worth, int lev ) {

	return worth * (lev+1);

	//if ( lev == 0 ) return worth*3/2;
	//return (int)( (double)upgradeHelper( worth, lev-1 ) * 7.0/4.0 );

}


int menuClass::upgradeCost( WeaponObject * gun ) {
	//int g = (int)((double)gun->Worth() * (double)tcube(gun->strength+3)*30.0/650.0);
	return upgradeHelper( gun->Worth(), gun->getPower() );
}


int menuClass::sellGun( WeaponObject * gun ) {

	//int resell = ( tcube( (gun->strength+1)*6 ) + gun->Worth() ) * 4 / 12;
	int resell = upgradeCost( gun ) / 2;
	return resell;

}


int menuClass::hull_price( int z ) {
	switch( z ) {
		case 1  :       return 160000;
		case 2  :       return 485000;
		case 3  :       return 700000;
		case 4  :       return 1000000;
	}
	return 0;
}


void menuClass::GunMenu( RMenu * weap, int q, WeaponObject * current, const Bitmap & intr, int score ) {
	WeaponObject ** legal = new WeaponObject*[pgun[q].mgun];
	for ( int z = 0; z < pgun[q].mgun; z++ )
		legal[z] = GetWeapon( pgun[q].gunz[z] );

	string numnum;

	if ( current != NULL ) {
		/*
		char * numnum = int2str(current->strength+1);
		char * sub = append( current->GetName()," at strength ");
		weap->addTitle( append(sub,numnum), menuFont );
		free( numnum );
		free( sub );
		*/
		weap->addTitle( current->GetName(), menuFont );
		// char * numnum = int2str( current->strength + 1 );
		int max = current->maxPower();

		char power[ 64 ];
		if ( max != -1 ) snprintf( power, 64, "%d", max+1 );
		else snprintf( power, 64, "Infinite" );

		char tmp[ 128 ];
		snprintf( tmp, 128, "Strength %d out of %s", current->getPower()+1, power );
		weap->addTitle( tmp, menuFont );

		// char * maxnum;

		/*
		if ( max != -1 ) maxnum = int2str( max+1 );
		else maxnum = strdup("Infinite");
		*/

		/*
		char * sub = append( "Strength ", numnum );
		char * sub2 = append( " out of ", maxnum );
		weap->addTitle( append(sub,sub2), menuFont );
		free( numnum);
		free( maxnum );
		free( sub );
		free( sub2 );
		*/

	} else  weap->addTitle( "No Weapon", menuFont );
	numnum = int2normal( score );
	weap->addTitle( "Score " + numnum, menuFont );
	weap->addMenu( "Return", menuFont, true, 0, NULL, NO_SOUND );
	if ( current != NULL ) {

		if ( current->getPower() < current->maxPower() || current->maxPower() == -1 ) {
			numnum = int2normal( upgradeCost(current) );
			weap->addMenu( "Upgrade " + numnum, menuFont, score>=upgradeCost(current), MENU_UPGRADE, weap, -1 );
		}

		numnum = int2normal( sellGun( current ) );
		weap->addMenu( "Sell for " + numnum, menuFont, true, MENU_SELL_WEAPON, weap, NO_SOUND );
	}
	weap->addTitle( "Purchase", menuFont );
	for ( int z = 0; z < pgun[q].mgun; z++ )
	if ( !(current != NULL && strcasecmp(legal[z]->GetName(),current->GetName())==0) ) {

		/*
		numnum = int2normal( legal[z]->Worth() );
		char * sub = append(legal[z]->GetName(),":");
		char * sub2 = append(sub,numnum);
		*/
		//weap->addMenu(strdup(sub2),menuFont,score>=legal[z]->Worth(),MENU_BUY_WEAPON+z, weap, NULL );
		char sub2[ 256 ];
		sprintf( sub2, "%s: %d", legal[z]->GetName(), legal[z]->Worth() );
		weap->addMenu(sub2,menuFont,true,MENU_BUY_WEAPON+z, weap, NO_SOUND );
		/*
		free( numnum );
		free( sub2 );
		free( sub );
		*/
	}

	for ( int z = 0; z < pgun[q].mgun; z++ )
		delete legal[z];
	delete[] legal;
}


void menuClass::GetAccessoryMenu( RMenu * weap, WeaponObject ** a_list, const Bitmap & intr, int score ) {
	WeaponObject ** legal = new WeaponObject*[agun.mgun];
	for ( int z = 0; z < agun.mgun; z++ )
		legal[z] = GetWeapon( agun.gunz[z] );

	weap->addTitle( "Accessory Bays", menuFont );
	string numnum;
	numnum = int2normal( score );
	weap->addTitle( "Score " + numnum, menuFont );
	weap->addTitle( "Currently have", menuFont );
	for ( int q = 0; q < MAX_ACCESSORY; q++ )
		if ( a_list[q] != NULL )
			weap->addTitle( a_list[q]->GetName(), menuFont );

	weap->addTitle( "Purchase", menuFont );
	for ( int q = 0; q < agun.mgun; q++ ) {
		bool cy = true;
		int total = 0;
		for ( int z = 0; z < MAX_ACCESSORY; z++ )
		if ( a_list[z] != NULL ) {
			if ( strcasecmp(a_list[z]->GetName(),legal[q]->GetName()) == 0 ) cy = false;
			total++;
		}

		if ( cy ) {

			/*
			numnum = int2normal( legal[q]->Worth() );
			char * sub = append(legal[q]->GetName(),":");
			char * sub2 = append(sub,numnum);
			*/
			char sub2[ 256 ];
			snprintf( sub2, 256, "%s: %d", legal[q]->GetName(), legal[q]->Worth() );
			weap->addMenu( sub2, menuFont, score>=legal[q]->Worth() && total < MAX_ACCESSORY, MENU_BUY_ACCESSORY+q, weap, NO_SOUND );
		}

	}

	weap->addMenu( "Return", menuFont, true, 0, NULL, NO_SOUND );

	for ( int z = 0; z < agun.mgun; z++ )
		delete legal[z];
	delete[] legal;

}

void menuClass::weaponMenu( RMenu * gun_menu, SpaceObject * player ) {
	//RMenu * gun_menu = new RMenu( intr, 1, 40, makecol(80,0,0),makecol(255,136,0), MENU_TITLE_COLOR );
	gun_menu->addTitle( "Buy Weapons", menuFont );
	// string numnum = int2normal( player->getScore() );
	string score = "Score ";
	score += int2normal( player->getScore() );
	// cout << "String = '" << score << "'" << endl;
	gun_menu->addTitle( score, menuFont );
	for ( int q = 0; q < player->getHull()->maxGuns()-1; q++ ) {
		// numnum = int2str(q+1);
		string bay = "Weapon Bay ";
		bay += int2normal( q + 1 );
		gun_menu->addMenu( bay, menuFont,true,MENU_BUY+q,gun_menu, NO_SOUND );
	}
	gun_menu->addMenu( "Accessories", menuFont, true, 1, gun_menu, NO_SOUND );
	gun_menu->addMenu( "Return", menuFont, true, 0, NULL, NO_SOUND );
}


HullObject * menuClass::playerHull( int q ) {

	// BITMAP ** pics = new BITMAP*[ 9 ];
	vector< Bitmap * > pics;
	int life = 0;
	int shield = 0;
	int guns = 0;
	int hn = 0;
	int startingSprite = HULL_1_1;
	switch( q ) {
		case 1  : {
			startingSprite = HULL_1_1;
			life = 100;
			shield = 100;
			guns = 3;
			hn = 1;
			break;
		}
		case 2  : {
			startingSprite = HULL_2_1;

			/*
			for ( int q = 0; q < 9; q++ ){
				pics.push_back( new Bitmap( Util::getDataSprite( HULL_2_1 + q ) ) );
			}
			*/
			life = 150;
			shield = 150;
			guns = 4;
			hn = 2;
			break;
		}
		case 3  : {
			startingSprite = HULL_3_1;
			/*
			for ( int q = 0; q < 9; q++ ){
				pics.push_back( new Bitmap( Util::getDataSprite( HULL_3_1 + q ) ) );
			}
			*/
			life = 200;
			shield = 250;
			guns = 5;
			hn = 3;
			break;
		}
	}
			
	for ( int q = 0; q < 9; q++ ){
		pics.push_back( new Bitmap( Util::getDataSprite( startingSprite + q ) ) );
	}

	// return new PlayerHull( pics, 9, life, shield, guns, hn, new ECollide( pics[4], 6, makecol(255,0,255), 52 ) );
	return new PlayerHull( pics, life, shield, guns, hn, new ECollide( pics[4] ) ); 
}

void menuClass::GetHullMenu( RMenu * hull_menu, SpaceObject * human, const Bitmap & intr ){

	PlayerHull * phull = (PlayerHull *)human->getHull();
	char tmp[ 128 ];
	snprintf( tmp, 128, "Score %d", human->getScore() );
	hull_menu->addTitle( tmp, menuFont );

	snprintf( tmp, 128, "Hull life %d out of %d", (int)human->getHull()->life, phull->getMaxLife() );
	hull_menu->addTitle( tmp, menuFont );

	snprintf( tmp, 128, "Hull Shield %d out of %d", (int)phull->getShield(), phull->getMaxShield() );
	hull_menu->addTitle( tmp, menuFont );

	bool can_buy;

	can_buy = ( human->getScore() >= HULL_LIFE_WORTH ) && ( human->getHull()->life < phull->getMaxLife() );
	hull_menu->addMenu( "Buy Life 1000", menuFont, can_buy, MENU_HULL_LIFE, hull_menu, NO_SOUND );

	can_buy = (human->getScore() >= HULL_SHIELD_WORTH) && (phull->getShield() < phull->getMaxShield() );
	hull_menu->addMenu( "Buy Shield 3000", menuFont, can_buy, MENU_HULL_SHIELD, hull_menu, NO_SOUND );

	hull_menu->addMenu( "Maxout life", menuFont, true, MENU_HULL_MAX, hull_menu, NO_SOUND );
	hull_menu->addMenu( "Maxout shield", menuFont, true, MENU_SHIELD_MAX, hull_menu, NO_SOUND );
	
	snprintf( tmp, 128, "Buy next hull for %d", hull_price( phull->rank() ) );
	if ( phull->rank() < 3 ){
		can_buy = human->getScore() >= hull_price( phull->rank() );

		hull_menu->addMenu( tmp, menuFont, can_buy, MENU_BUY_HULL, hull_menu, NO_SOUND );
	}

	hull_menu->addMenu( "Return", menuFont, true, 0, NULL, NO_SOUND );

}


SpaceObject * menuClass::copySpace( SpaceObject * player ) {

	/* TODO: fix
	SpaceObject * who = new SpaceObject( 0, 0, 0, 0, new HullObject( player->getHull()->Bitmap, 1, 1, player->getHull()->maxGuns(), 1, 10, false, NULL ), NULL, 10, 1 );
	for ( int q = 0; q < player->getHull()->maxGuns(); q++ )
		who->giveWeapon( player->getHull()->Guns()[q], q );
	return who;
	*/

	return NULL;

}


bool menuClass::accept_sell(){

	// BITMAP * sell_screen = create_bitmap( GRAPHICS_X, GRAPHICS_Y );
	// Bitmap sell_screen( GRAPHICS_X, GRAPHICS_Y );
	Bitmap sell_screen( GRAPHICS_X, GRAPHICS_Y );
	sell_screen.CopyScreen();
	sell_screen.BlitToScreen();
	Bitmap::transBlender( 0, 0, 0, 210 );
	Bitmap::drawingMode( Bitmap::MODE_TRANS );
	sell_screen.rectangleFill( 120, 80, 450, 235, Bitmap::makeColor(0,0,0) );
	sell_screen.rectangle( 120, 80, 450, 235, Bitmap::makeColor(255,255,255) );
	Bitmap::drawingMode( Bitmap::MODE_SOLID );
	RMenu sell( sell_screen, 130, 100, 1000, Bitmap::makeColor(80,0,0), Bitmap::makeColor(255,136,0), MENU_TITLE_COLOR );
	sell.addTitle( "Sell weapon", menuFont );
	sell.addMenu( "Yes", menuFont, true, 1, &sell, NO_SOUND );
	sell.addMenu( "No", menuFont, true, 0, &sell, NO_SOUND );
	sell.init();

	int call = -1;
	RMenu * current = &sell;
	while( call == -1 ) {
		call = current->procMenu( &current );
		if ( !sell.Selected() ) call = -1;
		Util::YIELD();
		// al_poll_duh( dumb_player );
		// dumb_player->play();

	}

	// delete sell;
	// destroy_bitmap( sell_screen );
	
	return call;

}

char * menuClass::getFileInfo( int number ){

	char * temp = (char *)malloc( sizeof(char) * 1024 );
	char buf[ 64 ];
	sprintf( buf, "player%d.rap", number+1 );
	FILE * fv = fopen( buf, "rb" );
	if ( !fv ){
		sprintf( temp, "Slot %d Empty", number+1 );
	} else {
		
		time_t tl = Util::fileTime( buf );
		struct tm * real_time = localtime( &tl );

		// strftime( date, 64, "%A %F %r", real_time );
		char xbuf[ 128 ];
		strftime( xbuf, 64, "%A %F", real_time );
		sprintf( temp, "Slot %d %s", number+1, xbuf );

		fclose( fv );
	}

	return temp;

}

void menuClass::getSaveMenu( RMenu * save_menu ){
	
	save_menu->clear();

	for ( int q = 0; q < 6; q++ ){
		save_menu->addMenu( getFileInfo(q), menuFont, true, MENU_SAVE+q, NULL, NO_SOUND ); 
	}
	save_menu->addMenu( "Return", menuFont, true, 345345, NULL, NO_SOUND ); 

}


bool menuClass::activate( SpaceObject * player ){

	Font _menuFont = Util::getMenuFont();
	this->menuFont = &_menuFont;
	
	/* Give the player some default minimum amount of life */
	if ( player->getLife() <= 0 ){
		player->getHull()->life = ((PlayerHull *)player->getHull())->getMaxLife()/2;
	}

	//cheat line
	// player->IncScore( 1000000 );

	//BITMAP * intr = menuScreen();
	char buyMenuFile[ 4096 ];
	// char * buy_menu_file = Util::data_file( "buy-scene.pcx" );
	#ifdef PANDORA
	Util::getDataPath( buyMenuFile, "buy-scene-pandora.pcx" );
	#else
	Util::getDataPath( buyMenuFile, "buy-scene.pcx" );
	#endif
	Bitmap intr( buyMenuFile );
	// free( buy_menu_file );
	if ( intr.getError() ) {
		printf("Supreme error with menu screen\n");
		return true;
	}

	// SAMPLE * menu_sound = (SAMPLE *)Util::global_snd[ INTRO_MENU_SELECT ].dat;
	int menu_sound = INTRO_MENU_SELECT;

	SpaceObject * human = player;

	SpaceObject * alias;			  //used for animation in menu
	alias = player->copy();

	vector< SpaceObject * > * ammo = new vector< SpaceObject * >;
	vector< SpaceObject * > * enemy = new vector< SpaceObject * >;
	SpaceObject * enemy_guy = new SpaceObject( 320, -800, 0, 0,  new HullObject(NULL,0,0,0,0,0,false,NULL), NULL, PLANE_AIR, TEAM_ENEMY );
	enemy->push_back( enemy_guy );

	int num_guns = human->getHull()->maxGuns()-1;

	player_animate = new Animation( GRAPHICS_X-ANIMATION_X, 0 );
	Bitmap pa( ANIMATION_X, GRAPHICS_Y );
	player_animate->add( pa );

	RMenu intro_menu( intr, 1, 40, 1000, Bitmap::makeColor(90,0,0), Bitmap::makeColor(255,136,0), MENU_TITLE_COLOR );
	RMenu gun_menu( intr, 1, 40, 1000, Bitmap::makeColor(90,0,0), Bitmap::makeColor(255,136,0), MENU_TITLE_COLOR );
	RMenu hull_menu( intr, 1, 40, 1000, Bitmap::makeColor(90,0,0), Bitmap::makeColor(255,136,0), MENU_TITLE_COLOR );
	RMenu save_menu( intr, 1, 40, 1000, Bitmap::makeColor(90,0,0), Bitmap::makeColor(255,136,0), MENU_TITLE_COLOR );
	RMenu * accessory_menu = new RMenuAnimation( intr, 1, 40, 1000, Bitmap::makeColor(90,0,0), Bitmap::makeColor(255,136,0), MENU_TITLE_COLOR, player_animate );
	weaponMenu( &gun_menu, human );
	gun_menu.nextMenu( gun_menu.askPos( "Accessories" ), accessory_menu );
	GetHullMenu( &hull_menu, human, intr );
	GetAccessoryMenu( accessory_menu, ((PlayerHull *)human->getHull())->Accessories(), intr, human->getScore() );

	RMenu ** weapon_menu = new RMenu*[ num_guns ];
	for ( int q = 0; q < num_guns; q++ ) {
		weapon_menu[q]=new RMenuAnimation(intr, 1, 40, 1000, Bitmap::makeColor(120,0,0), Bitmap::makeColor(255,0,0),MENU_TITLE_COLOR,player_animate);
		GunMenu(weapon_menu[q], q, human->getHull()->Guns()[q], intr, human->getScore() );
		gun_menu.nextMenu( q+3, weapon_menu[q] );
	}

	intro_menu.addTitle( "Buy Menu", menuFont );
	string numnum = int2normal( human->getScore() );
	intro_menu.addTitle( "Score " + numnum, menuFont );
	intro_menu.addMenu( "Weapon Menu", menuFont, true, MENU_WEAPON, &gun_menu, menu_sound );
	intro_menu.addMenu( "Hull Menu", menuFont, true, MENU_HULL, &hull_menu, menu_sound );
	intro_menu.addMenu( "Save Game", menuFont, true, MENU_HULL, &save_menu, menu_sound );
	intro_menu.addMenu( "Next Level", menuFont, true, MENU_NEXT, NULL, menu_sound );
	intro_menu.addMenu( "Main Menu", menuFont, true, MENU_QUIT, NULL, menu_sound );

	getSaveMenu( &save_menu );

	/*
	for ( int q = 0; q < 6; q++ )
		save_menu.addMenu( getFileInfo(q), Util::raptor_font, true, MENU_SAVE+q, NULL, NULL ); 
	save_menu.addMenu( "Return", Util::raptor_font, true, 345345, NULL, NULL ); 
	*/

	/** END INIT **/

	RMenu * current = &intro_menu;
	current->init();
	int call = -1;
	int cur_weapon = 0;
	Util::speed_counter = 0;
	while ( call != MENU_QUIT && call != MENU_NEXT ) {

		Util::YIELD();
		// al_poll_duh( dumb_player );
		// dumb_player->play();

		bool score_change = false;
		if ( Util::speed_counter ){
			getAnimation( player_animate, alias, ammo, enemy );
		}

		RMenu * temp = current;
		call = current->procMenu( &current );
		if ( !temp->Selected() ) {

			if ( temp->changed() ) {

				//delete alias;
				//alias = player->copy();

				if ( call == 0 ) {
					delete alias;
					alias = player->copy();
				}

				if ( call-MENU_BUY >= 0 && call-MENU_BUY < num_guns )
					cur_weapon = call-MENU_BUY;

				if ( call == MENU_SELL_WEAPON ) {

					delete alias;
					alias = player->copy();
					alias->eraseWeapon( cur_weapon );
				}

				if ( call == MENU_UPGRADE ) {
					delete alias;
					alias = player->copy();
					WeaponObject * up = alias->getHull()->Guns()[ cur_weapon ];
					if ( up )
						up->IncreasePower( 1 );
				}

				if ( call-MENU_BUY_WEAPON >= 0 && call-MENU_BUY_WEAPON < pgun[cur_weapon].mgun ) {
					delete alias;
					alias = player->copy();
					int w_buy = call-MENU_BUY_WEAPON;

					WeaponObject * legal = GetWeapon( pgun[cur_weapon].gunz[w_buy] );
					alias->eraseWeapon( cur_weapon );
					alias->giveWeapon( GetWeapon( pgun[cur_weapon].gunz[w_buy] ), cur_weapon );

					delete legal;
				}

				if ( call-MENU_BUY_ACCESSORY >= 0 && call-MENU_BUY_ACCESSORY < agun.mgun ) {
					delete alias;
					alias = player->copy();
					int w_buy = call - MENU_BUY_ACCESSORY;
					alias->eraseWeapon( alias->getHull()->maxGuns()-1 );
					alias->giveWeapon( GetWeapon( agun.gunz[w_buy] ), alias->getHull()->maxGuns()-1 );
				}

			}

			call = -1;

		}
		
		if ( call >= MENU_SAVE && call <= MENU_SAVE+6 ){
			int save_game = call - MENU_SAVE + 1;
			if ( savePlayer( player, save_game ) != 0 ){
				printf( "Could not save game\n" );
			}
			getSaveMenu( &save_menu );
		}

		if ( call-MENU_BUY >= 0 && call-MENU_BUY < num_guns )
			cur_weapon = call-MENU_BUY;

		if ( call == MENU_SELL_WEAPON ) {
			WeaponObject * sl = human->getHull()->Guns()[ cur_weapon ];
			if ( sl ) {

				if ( accept_sell() ) {
					// human->score += sellGun( sl );
					human->IncScore( sellGun( sl ) );
					human->eraseWeapon( cur_weapon );
					human->giveWeapon( NULL, cur_weapon );
					score_change = true;
				}
			}

			delete alias;
			alias = player->copy();
		}

		if ( call-MENU_BUY_WEAPON >= 0 && call-MENU_BUY_WEAPON < pgun[cur_weapon].mgun ) {
			int w_buy = call-MENU_BUY_WEAPON;

			WeaponObject * legal = GetWeapon( pgun[cur_weapon].gunz[w_buy] );
			WeaponObject ** guns = human->getHull()->Guns();
			if ( human->getScore() >= legal->Worth() ) {
				// human->score -= legal->Worth();
				human->IncScore( -(legal->Worth()) );
				if ( guns[cur_weapon] != NULL ) {
					// human->score += sellGun( guns[cur_weapon] );
					human->IncScore( sellGun( guns[cur_weapon] ) );
					human->eraseWeapon( cur_weapon );
					human->giveWeapon( NULL, cur_weapon );
				}
				WeaponObject * nw = GetWeapon( pgun[ cur_weapon].gunz[w_buy] );
				human->giveWeapon( nw, cur_weapon );
				score_change = true;
			}

			delete legal;

			delete alias;
			alias = player->copy();

		}

		if ( call-MENU_BUY_ACCESSORY >= 0 && call-MENU_BUY_ACCESSORY < agun.mgun ) {
			int w_buy = call - MENU_BUY_ACCESSORY;
			WeaponObject * a_give = GetWeapon( agun.gunz[w_buy] );
			if ( human->getScore() >= a_give->Worth() ) {
				// human->score -= a_give->Worth();
				human->IncScore( -(a_give->Worth()) );
				human->giveWeapon( GetWeapon(agun.gunz[w_buy]), human->getHull()->maxGuns()-1 );
				score_change = true;
			}
			delete a_give;

			delete alias;
			alias = player->copy();
		}

		if ( call == MENU_HULL_LIFE ) {
			// human->score -= HULL_LIFE_WORTH;
			human->IncScore( -HULL_LIFE_WORTH );
			human->getHull()->life += 3;
			if ( human->getHull()->life > ((PlayerHull *)human->getHull())->getMaxLife() )
				human->getHull()->life = ((PlayerHull *)human->getHull())->getMaxLife();
			score_change = true;
		}

		if ( call == MENU_HULL_SHIELD ) {
			// human->score -= HULL_SHIELD_WORTH;
			human->IncScore( -HULL_SHIELD_WORTH );
			// ((PlayerHull *)human->getHull())->getShield() += 3;
			((PlayerHull *)human->getHull() )->incShield( INCREASE_SHIELD );

			/*
			if ( ((PlayerHull *)human->getHull())->getShield() > ((PlayerHull *)human->getHull())->getMaxShield() )
				((PlayerHull *)human->getHull())->getShield() = ((PlayerHull *)human->getHull())->getMaxShield();
			*/

			score_change = true;
		}

		if ( call == MENU_BUY_HULL && ((PlayerHull *)human->getHull())->rank() < 3 ) {
			if ( human->getScore() >= hull_price( ((PlayerHull *)human->getHull())->rank() ) ) {
				// human->score -= hull_price( ((PlayerHull *)human->hull)->rank() );
				human->IncScore( -hull_price( ((PlayerHull *)human->getHull())->rank() ) );
				HullObject * bh = playerHull( ((PlayerHull *)human->getHull())->rank()+1 );

				WeaponObject ** save_weapons = new WeaponObject*[ human->getHull()->maxGuns()-1 ];
				for ( int q = 0; q < human->getHull()->maxGuns()-1; q++ ) {
					save_weapons[q] = human->getHull()->Guns()[q];
					human->giveWeapon( NULL, q );
				}
				int old_guns = human->getHull()->maxGuns()-1;

				human->giveHull( bh );
				for ( int q = 0; q < old_guns; q++ )
					human->giveWeapon( save_weapons[q], q );

				score_change = true;

				delete[] save_weapons;
				for ( int q = 0; q < num_guns; q++ )
					delete weapon_menu[q];
				delete[] weapon_menu;

				num_guns = human->getHull()->maxGuns()-1;
				gun_menu.clear();
				weaponMenu( &gun_menu, human );
				weapon_menu = new RMenu*[ num_guns ];
				for ( int q = 0; q < num_guns; q++ ) {

					weapon_menu[ q ] = new RMenuAnimation( intr, 1, 40, 1000, Bitmap::makeColor( 120, 0, 0 ), Bitmap::makeColor( 255, 0, 0), MENU_TITLE_COLOR, player_animate );
					GunMenu(weapon_menu[q],q,human->getHull()->Guns()[q], intr, human->getScore() );
					gun_menu.nextMenu( q + 3, weapon_menu[ q ] );
				}
				gun_menu.nextMenu( gun_menu.askPos( "Accessories" ), accessory_menu );

				delete alias;
				alias = player->copy();
			}
		}

		if ( call == MENU_HULL_MAX ) {

			PlayerHull * ph = (PlayerHull *)human->getHull();
			while ( human->getScore() > HULL_LIFE_WORTH && ph->life < ph->getMaxLife() ) {
				if ( ph->getMaxLife()-ph->life < 3 ){
					ph->life += ph->getMaxLife()-ph->life;
				} else {
					ph->life += 3;
				}
				// human->score -= HULL_LIFE_WORTH;
				human->IncScore( -HULL_LIFE_WORTH );
				score_change = true;
			}

		}

		if ( call == MENU_SHIELD_MAX ) {

			PlayerHull * ph = (PlayerHull *)human->getHull();

			while ( human->getScore() > HULL_SHIELD_WORTH && ph->getShield() < ph->getMaxShield() ) {
				ph->incShield( INCREASE_SHIELD );

				/*
				if ( ph->getMaxShield() - ph->getShield() < 3 )
					// ph->getShield() += ph->max(1) - ph->shield;
					ph->incShield( ph->max(1) - ph->shield );

				else    / *ph->shield += 3;* /ph->incShield( 3 );
				*/
				// human->score -= HULL_SHIELD_WORTH;
				human->IncScore( -HULL_SHIELD_WORTH );
				score_change = true;
			}

		}

		if ( call == MENU_UPGRADE ) {
			WeaponObject * up = human->getHull()->Guns()[cur_weapon];
			if ( up ) {
				if ( human->getScore() >= upgradeCost( up ) && (up->getPower() < human->getHull()->Guns()[cur_weapon]->maxPower() || human->getHull()->Guns()[cur_weapon]->maxPower() == -1) ) {
					// human->score -= upgradeCost( up );
					human->IncScore( -upgradeCost( up ) );
					up->IncreasePower( 1 );
					score_change = true;
				}
			}
		}

		if ( score_change ) {

			numnum = int2normal( human->getScore() );
			intro_menu.replaceTitle( 2, "Score " + numnum, menuFont );
			gun_menu.clear();
			weaponMenu( &gun_menu, human );

			for ( int q = 0; q < num_guns; q++ ) {
				weapon_menu[q]->clear();
				GunMenu(weapon_menu[q],q, human->getHull()->Guns()[q],intr,human->getScore() );
				gun_menu.nextMenu( q+3, weapon_menu[q] );
			}
			hull_menu.clear();
			GetHullMenu( &hull_menu, human, intr );
			accessory_menu->clear();
			GetAccessoryMenu( accessory_menu, ((PlayerHull *)human->getHull())->Accessories(), intr, human->getScore() );
			gun_menu.nextMenu( gun_menu.askPos( "Accessories" ), accessory_menu );

		}

	}

	/** END  **/

	// destroy_bitmap( intr );
	/*
	delete intro_menu;
	delete gun_menu;
	delete hull_menu;
	*/
	delete accessory_menu;
	for ( int q = 0; q < num_guns; q++ ){
		delete weapon_menu[q];
	}
	delete[] weapon_menu;
	delete player_animate;
	delete ammo;
	delete enemy;
	delete enemy_guy;
	delete alias;

	return ( call == MENU_QUIT );
	/*
	if ( call == MENU_QUIT ) return true;
	return false;
	*/

}


WeaponObject * menuClass::GetWeapon( int q ) {

	switch( q ) {
		case GUN_MACHINE        :       return new WeaponMachineGun( 0, -1, -1, TEAM_PLAYER );
		case GUN_MACHINE_CIRCLE :       return new WeaponMachineCircleGun( 0, -1, -1, TEAM_PLAYER  );
		case GUN_BEAM           :       return new WeaponBeam( 0, -1, TEAM_PLAYER  );
		case GUN_MINIMISSLE     :       return new WeaponMiniMissle( 0, -1, TEAM_PLAYER  );
		case GUN_FINDGUN        :       return new WeaponFindGun( 0, -1, TEAM_PLAYER  );
		case GUN_PULSE          :       return new WeaponPulse( 0, -1, TEAM_PLAYER  );
		case GUN_LASER          :       return new WeaponLaser( 0, -1, TEAM_PLAYER  );
		case GUN_MISSLE         :       return new WeaponMissle( 0, -1, TEAM_PLAYER  );
		case GUN_FOLLOW         :       return new WeaponFollow( 0, -1, TEAM_PLAYER  );
		case GUN_ARC            :       return new WeaponArc( 0, -1, -1, TEAM_PLAYER  );
		// case GUN_CHAIN          :       return new WeaponChainGun( 0, -1, "Iron Chain", 65500, NULL, TEAM_PLAYER, new ECollide((BITMAP *)global_data[IRON_000].dat,6,makecol(255,0,255),52)  );
		case GUN_CHAIN          :       return new WeaponChainGun( 0, -1, "Iron Chain", 65500, -1, TEAM_PLAYER, new ECollide( Util::getDataSprite( IRON_000 ) ) );
		// case GUN_CHAIN_FIRE     :       return new WeaponChainGun( 1, -1, "Fire Chain", 153000, NULL, TEAM_PLAYER, new ECollide((BITMAP *)Util::global_data[IRON_000].dat,6,makecol(255,0,255),52)  );
		case GUN_CHAIN_FIRE     :       return new WeaponChainGun( 1, -1, "Fire Chain", 153000, -1, TEAM_PLAYER, new ECollide( Util::getDataSprite( IRON_000 ) ) );
		case GUN_SHATTER        :       return new WeaponShatter( 0, -1, -1, TEAM_PLAYER );
		case GUN_SWIRL          :       return new WeaponSwirlGun(0,-1,-1,TEAM_PLAYER);
		case GUN_SPREAD         :       return new WeaponSpreadGun( 0, -1, -1, TEAM_PLAYER );
		case GUN_MASSIVE        :       return new WeaponMassiveGun( 0, -1, -1, TEAM_PLAYER );
		case GUN_SABER          :       return new WeaponSaber( 0, -1, -1, TEAM_PLAYER );
		case GUN_ANGLE          :       return new WeaponAngle( 0, -1, TEAM_PLAYER );
		case GUN_TRACTOR        :       return new WeaponTractorBeam( 0, -1, TEAM_PLAYER );
		case GUN_ROTATE         :       return new WeaponRotateGun( 0, -1, -1, TEAM_PLAYER );
		//case GUN_STICKY		:	return new WeaponStick( 0, -1, TEAM_PLAYER );
		case GUN_STICKY         : {
						  //ECollide ** temp_list = new ECollide*[ gun_sticky_max_collide ];
						  //for ( int q = 0; q < gun_sticky_max_collide; q++ )
						  //	temp_list[q] = gun_sticky_collide_list[q]->copy();
						  //return new WeaponStick( 0, -1, TEAM_PLAYER, temp_list, gun_sticky_max_collide );
			return new WeaponStick( 0, -1, TEAM_PLAYER, menuClass::gun_sticky_collide_list, menuClass::gun_sticky_max_collide );
		}
		case GUN_YEHAT          :       return new WeaponYehatGun( 0, -1, -1, TEAM_PLAYER );
	}
	return NULL;
}

ECollide ** menuClass::gun_sticky_collide_list;
int menuClass::gun_sticky_max_collide;
