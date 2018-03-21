/* TODO: Rewrite this entire file cuase it sucks badly
 */

#include "loadsave.h"
#include <stdio.h>
#include "spaceobj.h"
#include "strings_util.h"
#include <string>
#include <string.h>
#include <vector>
#include "gunobj.h"
#include "hull.h"
#include "hulls/hull_player.h"
#include "playerobj.h"
#include "raptor.h"
#include "ebox.h"

#include "guns/gun_arc.h"
#include "guns/gun_angle.h"
#include "guns/gun_beam.h"
#include "guns/gun_chain.h"
#include "guns/gun_destruct.h"
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
#include <iostream>

// menu.h is needed to hack around the fact that
// only one gun_sticky_collide_list should exist,
// and that is in menu.cpp
#include "menu.h"

using namespace std;
#ifndef debug
#define debug cout<<"File: "<<__FILE__<<" Line: "<<__LINE__<<endl;
#endif

/* savePlayer:
 * Saves the player in at player#.rap where # = game_slot
 */
int savePlayer( SpaceObject * player, int game_slot ){

	if ( player == NULL ) return 1;
	printf("Save player\n");

	char filename[ 64 ];
	snprintf( filename, 64, "player%d.rap", game_slot );

	// PlayerHull * hull = dynamic_cast<PlayerHull *>(player->getHull());
	PlayerHull * hull = (PlayerHull *)(player->getHull() );
	// HullObject * hull = player->getHull();

	WeaponObject ** guns = hull->Guns();
	WeaponObject ** accessories = hull->Accessories();

	int rank = hull->rank();
	int shields = hull->getShield();
	int life = hull->getLife(); 
	int score = player->getScore();
	int dif = ((PlayerObject *)player)->getDifficulty();
	int level = ((PlayerObject *)player)->getLevel();

	std::string gun_str("");
	for ( int q = 0; q < hull->maxGuns()-1; q++ ){
		if ( guns[q] != NULL ){
			gun_str += guns[q]->GetName(); 
			gun_str += ":";
			char pow[ 10 ];
			snprintf( pow, 10, "%d|", guns[q]->getPower() );
			gun_str += pow;
		}
	}

	for ( int q = 0; q < MAX_ACCESSORY; q++ ){
		if ( accessories[q] != NULL ){
			WeaponObject * ac = accessories[q];
			gun_str += ac->GetName();
			gun_str += ":";
			char pow[ 10 ];
			snprintf( pow, 10, "%d|", ac->getPower() );
			gun_str += pow;
		}
	}

	char final[ 1024 ];
	snprintf( final, 1024, "Life:%d Shields:%d Score:%d Rank:%d Difficulty:%d Level:%d |%s", life, shields, score, rank, dif, level, gun_str.c_str() );

	// printf("Save string = %s\n", final );
	FILE * fv = fopen( filename, "wb" );
	if ( fv == NULL ){
		return 1;
	}
	fwrite( final, sizeof(char), strlen(final), fv );
	fclose( fv );

	return 0;

}

struct weapon_data{
	char name[ 128 ];
	int power;
};

HullObject * newPlayerHull( int q ) {

	// Bitmap ** pics = new BITMAP*[ 9 ];
	vector< Bitmap * > pics;
	int life = 0;
	int shield = 0;
	int guns = 0;
	int hn = 0;
	int pic_number = 0;
	switch( q ) {
		case 1  : {
			pic_number = HULL_1_1;
			/*
			for ( int q = 0; q < 9; q++ )
				pics[q] = (BITMAP *)global_data[HULL_1_1+q].dat;
			*/
			life = 100;
			shield = 100;
			guns = 3;
			hn = 1;
			break;
		}
		case 2  : {
			pic_number = HULL_2_1;
			/*
			for ( int q = 0; q < 9; q++ )
				pics[q] = (BITMAP *)global_data[HULL_2_1+q].dat;
			*/
			life = 150;
			shield = 150;
			guns = 4;
			hn = 2;
			break;
		}
		case 3  : {
			pic_number = HULL_3_1;
			/*
			for ( int q = 0; q < 9; q++ )
				pics[q] = (BITMAP *)global_data[HULL_3_1+q].dat;
			*/
			life = 200;
			shield = 250;
			guns = 5;
			hn = 3;
			break;
		}
		default : {
			pic_number = HULL_1_1;
			/*
			for ( int q = 0; q < 9; q++ )
				pics[q] = (BITMAP *)global_data[HULL_1_1+q].dat;
			*/
			life = 100;
			shield = 100;
			guns = 3;
			hn = 1;
			break;

		}
	}
	// return new PlayerHull( pics, 9, life, shield, guns, hn, new ECollide( pics[4], 6, makecol(255,0,255), 52 ) );

	for ( int q = 0; q < 9; q++ )
		pics.push_back( new Bitmap( Util::getDataSprite( pic_number + q ) ) );

	return new PlayerHull( pics, life, shield, guns, hn, new ECollide( pics[4] ) );
}

int filesize( FILE * f ){
	fseek( f, 0, SEEK_END );
	int x = ftell( f );
	fseek( f, 0, SEEK_SET );
	return x;
}
	
void getAllWeapons( vector< vector< WeaponObject * > > & all_weapons ){


	vector< WeaponObject * > bay_1;
	bay_1.push_back( new WeaponMachineGun( 0, -1, -1, TEAM_PLAYER ) );
	bay_1.push_back( new WeaponMachineCircleGun( 0, -1, -1, TEAM_PLAYER ) );
	bay_1.push_back( new WeaponSpreadGun( 0, -1, -1, TEAM_PLAYER ) );
	bay_1.push_back( new WeaponAngle( 0, -1, TEAM_PLAYER ) );

	all_weapons.push_back( bay_1 );

	vector< WeaponObject * > bay_2;

	bay_2.push_back( new WeaponBeam( 0, -1, TEAM_PLAYER ) );
	bay_2.push_back( new WeaponMiniMissle( 0, -1, TEAM_PLAYER ) );
	bay_2.push_back( new WeaponShatter( 0, -1, -1, TEAM_PLAYER ) );
	bay_2.push_back( new WeaponYehatGun( 0, -1, -1, TEAM_PLAYER ) );
	
	all_weapons.push_back( bay_2 );

	vector< WeaponObject * > bay_3;

	bay_3.push_back( new WeaponArc( 0, -1, -1, TEAM_PLAYER ) );
	bay_3.push_back( new WeaponLaser( 0, -1, TEAM_PLAYER ) );
	bay_3.push_back( new WeaponStick( 0, -1, TEAM_PLAYER, menuClass::gun_sticky_collide_list, menuClass::gun_sticky_max_collide ) );

	all_weapons.push_back( bay_3 );

	vector< WeaponObject * > bay_4;

	bay_4.push_back( new WeaponMissle( 0, -1, TEAM_PLAYER ) );
	bay_4.push_back( new WeaponPulse( 0, -1, TEAM_PLAYER ) );

	all_weapons.push_back( bay_4 );

	vector< WeaponObject * > bay_5;

	bay_5.push_back( new WeaponFindGun( 0, -1, TEAM_PLAYER ) );
	bay_5.push_back( new WeaponFollow( 0, -1, TEAM_PLAYER ) );
	bay_5.push_back( new WeaponTractorBeam( 0, -1, TEAM_PLAYER ) );

	all_weapons.push_back( bay_5 );
	
	vector< WeaponObject * > accessory;

	accessory.push_back( new WeaponSaber( 0, -1, -1, TEAM_PLAYER ) );
	accessory.push_back( new WeaponSwirlGun( 0, -1, -1, TEAM_PLAYER ) );
	// accessory.push_back( new WeaponChainGun( 0, -1, "Iron Chain", 65500, NULL, TEAM_PLAYER, new ECollide((BITMAP *)global_data[IRON_000].dat,6,makecol(255,0,255),52)  ) );
	accessory.push_back( new WeaponChainGun( 0, -1, "Iron Chain", 65500, -1, TEAM_PLAYER, new ECollide( Util::getDataSprite( IRON_000 ) ) ) );
	accessory.push_back( new WeaponMassiveGun( 0, -1, -1, TEAM_PLAYER ) );

	all_weapons.push_back( accessory );
		
}

SpaceObject * loadPlayer( int game_slot ){

	FILE * fv;
	
	char filename[ 64 ];
	snprintf( filename, 64, "player%d.rap", game_slot );
	fv = fopen( filename, "rb" );
	if ( fv == NULL ){
		printf("Could not open %s\n", filename );
		return NULL;
	}

	int size = filesize( fv );

	// printf("Size = %d\n", size );
	SpaceObject * player;
	char final[ size+1 ];
	fread( final, sizeof(char), size, fv );
	final[ size ] = '\0';
	fclose( fv );

	int life;
	int shields;
	int rank;
	int score;
	int dif;
	int level;

	sscanf( final, "Life:%d Shields:%d Score:%d Rank:%d Difficulty:%d Level:%d", &life, &shields, &score, &rank, &dif, &level );
	debug

	/*
	printf("Life = %d\n", life );
	printf("Shields = %d\n", shields );
	printf("Score = %d\n", score );
	printf("Rank = %d\n", rank );
	printf("Difficulty = %d\n", dif );
	*/

	HullObject * hwho;
	player = NULL;
	
	PlayerObject * pp;
	PlayerHull * ph;

	debug
	
	vector< vector< WeaponObject * > > all_weapons;
	getAllWeapons( all_weapons );

	char * weapon_begin = strchr( final, '|' );
	vector< weapon_data * > weapons;

	if ( weapon_begin == NULL ) goto evil_end;
	weapon_begin++;
	// printf("Final: %s\n", final );
	while ( weapon_begin != NULL && (*weapon_begin) != 0 ){
		char * weapon_end = strchr( weapon_begin, '|' );
		if ( weapon_end == NULL ){
			printf("Error parsing %s. You tried to hack it, didnt you?\n", filename );
			goto evil_end;
		}
		*weapon_end = '\0';
		weapon_data * wd = new weapon_data;

		char wname[ 128 ];
		strcpy( wname, weapon_begin );
		char * power = strchr( wname, ':' );
		if ( power == NULL ){
			printf("Error parsing %s. You tried to hack it, didnt you?\n", filename );
			goto evil_end;
		}
		*power = '\0';
		power++;
		strcpy( wd->name, wname );
		wd->power = str2int( power );

		weapons.push_back( wd );

		weapon_begin = weapon_end+1;
	}

	hwho = newPlayerHull( rank );
	debug
	player = new PlayerObject(320,450, dif, hwho );
	
	// a little c++ never hurt anyone
	pp = (PlayerObject *)(player);
	ph = (PlayerHull *)(hwho);
	pp->setLevel( level );
	ph->setShields( shields );
	ph->setLife( life );
	pp->setScore( score );
	pp->setLevel( level );
	pp->setDifficulty( dif );

	debug
	for ( vector< weapon_data * >::iterator cur_data = weapons.begin(); cur_data != weapons.end(); cur_data++ ){
		weapon_data * mine = *cur_data;

		// 6 is the max number of slots a gun could be in
		// 0-4 for regular guns and 5 for accessories
		for ( int q = 0; q < 6; q++ ){
			vector< WeaponObject * > & wv = all_weapons[ q ];
			for ( vector< WeaponObject * >::iterator it = wv.begin(); it != wv.end(); ){
				WeaponObject * sofar = *it;

				if ( strcasecmp( sofar->GetName(), mine->name ) == 0 ){
					sofar->IncreasePower( mine->power );
					pp->giveWeapon( sofar, q );
					it = wv.erase( it );
				} else it++;
			}
		}
	}

	debug
	cout<<"All weapons: "<<all_weapons.size()<<endl;
	for ( vector< vector< WeaponObject * > >::iterator it = all_weapons.begin(); it != all_weapons.end(); it++ ){
		// vector< WeaponObject * > & wv = *it;
		debug
		for ( vector< WeaponObject * >::iterator k = it->begin(); k != it->end(); k++ ){
			cout<<"Weapon: "<<(*k)->getName()<<endl;
			delete *k;
		}
	}
	debug

	// evil cuase its a goto!
	evil_end:
	debug

	for ( vector< weapon_data * >::iterator it = weapons.begin(); it != weapons.end(); it++ ){
		delete *it;
	}

	debug
	return player;
}
// im tired and angry
