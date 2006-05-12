#include "level.h"
#include "shipobj.h"
#include "spaceobj.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "defs.h"
#include "strings.h"
#include "raptor.h"
#include "ebox.h"
#include "trigger.h"
#include "trigtable.h"
#include "group.h"
#include "bitmap.h"
#include "playerobj.h"
#include <vector>

#include "move.h"
#include "move_find.h"

#include "guns/gun_destruct.h"
#include "guns/gun_edfstraight.h"
#include "guns/gun_ednstraight.h"
#include "guns/gun_eflarge.h"
#include "guns/gun_efmsingle.h"
#include "guns/gun_efsingle.h"
#include "guns/gun_elarge.h"
#include "guns/gun_emissle.h"
#include "guns/gun_ecork.h"
#include "guns/gun_emlight.h"
#include "guns/gun_eside.h"
#include "guns/gun_etwirl.h"
#include "guns/gun_etwirl_find.h"
#include "guns/gun_etwirl_machine.h"
#include "guns/gun_estraight.h"
#include "guns/gun_fire.h"
#include "hulls/hull_ship_shield.h"
#include "hulls/hull_meteor.h"
#include "hulls/hull_animation.h"

using namespace std;

#define SHIP_TRIGGER 0
#define POWER_TRIGGER 1
#define METEOR_ON_TRIGGER 2
#define METEOR_OFF_TRIGGER 3
#define HEALTH_TRIGGER 4

#define MAX_ENEMY_GUNS 15
#define MAX_ENEMY_MOVE 9
#define MAX_ENEMY_HULL (SHIP_LAST-SHIP0_FIRST-1)
#define space_cracker ( sizeof(int)*6 + sizeof(double)*2 + sizeof(char)*7 )
//6 integers = x, y, gun, hull, move, life
//2 doubles = dx, dy
//7 spaces between numbers

static int gl_map( int who );

/* this is ok as long as only one LevelCreator is alive at any one time */
static vector< Bitmap > hull_money_shadows;
static ECollide ** gl_collide;
const int MAX_GL_COLLIDE = (SHIP_LAST-SHIP0_FIRST-1) + 6;

void LevelCreator::makeInfo( char * tmp, int & current ) {

	/*
	//scramble( buffer, space_cracker );
	scramble( tmp, space_cracker );

	int x1, y1;
	double dx, dy;
	int gun, move, hull_num;

	x1 = *( (int *)tmp );
	tmp += sizeof( int ) + 1;

	y1 = *( (int *)tmp );
	tmp += sizeof( int ) + 1;

	dx = *( (double *)tmp );
	tmp += sizeof( double ) + 1;

	dy = *( (double *)tmp );
	tmp += sizeof( double ) + 1;

	gun = *( (int *)tmp );
	tmp += sizeof( int ) + 1;

	move = *( (int *)tmp );
	tmp += sizeof( int ) + 1;

	hull_num = *( (int *)tmp );
	info[current] = new info_holder;
	info[current]->x = x1;
	info[current]->y = y1;
	info[current]->dx = dx;
	info[current]->dy = dy;
	info[current]->gun = gun;
	info[current]->hull = hull_num;
	info[current]->move = move;

	current++;
	*/

}


void LevelCreator::put_ship( int x, int y, double dx, double dy, int hull, int gun, int move, int life ) {

	char * buf = new char[ space_cracker ];
	char * tmp = buf;
	*(int *)tmp = x;
	tmp += sizeof( int );
	*tmp = ' ';
	tmp++;

	*(int *)tmp = y;
	tmp += sizeof( int );
	*tmp = ' ';
	tmp++;

	*(double *)tmp = dx;
	tmp += sizeof( double );
	*tmp = ' ';
	tmp++;

	*(double *)tmp = dy;
	tmp += sizeof( double );
	*tmp = ' ';
	tmp++;

	*(int *)tmp = gun;
	tmp += sizeof( int );
	*tmp = ' ';
	tmp++;

	*(int *)tmp = move;
	tmp += sizeof( int );
	*tmp = ' ';
	tmp++;

	*(int *)tmp = hull;
	tmp += sizeof( int );
	*tmp = '\n';
	tmp++;
	*(int *)tmp = life;

	//trigger * add_t = new triggerEnemy( buf, space_cracker, SHIP_TRIGGER, x, y );
	//trigger_list.push_back( add_t );

}


Group * LevelCreator::randomGroup( int x, int y ) {

	Group * who_group = new Group( y );

	int gun = Util::rnd( MAX_ENEMY_GUNS );
	int move = Util::rnd( MAX_ENEMY_MOVE );
	int hull = Util::rnd( MAX_ENEMY_HULL );
	while ( !accept_guns[ gun ] )
		gun = Util::rnd( MAX_ENEMY_GUNS );
	while ( !accept_hull[ hull ] )
		hull = Util::rnd( MAX_ENEMY_HULL );
	while ( !accept_move[ move ] )
		move = Util::rnd( MAX_ENEMY_MOVE );

	double dx = (double)Util::rnd(2000) / 200.0 - 5.0;
	double dy = (double)Util::rnd(1300) / 300.0 + 3.0;
	int pattern = Util::rnd( 9 );

	switch( pattern ) {

		case 0  : {
			new EnemyGeneric(x,y,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy),who_group);
			new EnemyGeneric( x + 60, y, getHull(hull,1,accept_hull[hull]), getWeapon(gun), getMove(move,dx,dy), who_group);
			break;

		}
		case 1  : {

			new EnemyGeneric(x,y,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group );
			new EnemyGeneric(x+60,y,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group );
			new EnemyGeneric(x+120,y,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group );

			break;

		}
		case 2  : {

			new EnemyGeneric(x,y,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group );
			new EnemyGeneric(x+140,y,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group );
			new EnemyGeneric(x+70,y+30,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group );
			new EnemyGeneric(x,y+60,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group );
			new EnemyGeneric(x+140,y+60,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group );

			break;
		}
		case 3  : {

			new EnemyGeneric(x,y,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group );
			new EnemyGeneric(x+40,y+20,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group );
			new EnemyGeneric(x+80,y+40,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group );
			new EnemyGeneric(x+120,y+20,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group );
			new EnemyGeneric(x+160,y,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group );

			break;

		}

		case 4  : {
			int spacer = Util::rnd( 2 ) * 15 + 20;

			new EnemyGeneric(x,y,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group );
			new EnemyGeneric(x,y-spacer,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group );
			new EnemyGeneric(x,y-spacer*2,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group );

			break;

		}

		case 5  : {
			int spacer = Util::rnd( 5 ) * 10 + 25;
			new EnemyGeneric(x,y,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group );
			new EnemyGeneric(x,y-spacer*1,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group );
			new EnemyGeneric(x,y-spacer*2,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group );
			new EnemyGeneric(x,y-spacer*3,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group );
			new EnemyGeneric(x,y-spacer*4,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group );

			break;

		}
		case 6  : {

			int ang = 270-20*2;
			for ( int q = 0; q < 5; q++ ) {
				new EnemyGeneric((int)(x+Tcos(ang)*85),(int)(y+Tsine(ang)*90),getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group );
				ang += 20;
			}

			break;
		}
		case 7  : {
			new EnemyGeneric(x,y,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group );
			new EnemyGeneric(x+100,y,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group );
			new EnemyGeneric(x+50,y+40,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group );

			break;

		}

		case 8  : {

			new EnemyGeneric(x,y,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group );
			new EnemyGeneric(x+100,y,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group );
			new EnemyGeneric(x,y+40,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group );
			new EnemyGeneric(x+100,y+40,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group );

			break;

		}

	}					  //switch

	return who_group;

}


void LevelCreator::randomShip( int x, int y, Group * who_group, vector< SpaceObject * > * sh ) {

	int gun = Util::rnd( MAX_ENEMY_GUNS );
	int move = Util::rnd( MAX_ENEMY_MOVE );
	int hull = Util::rnd( MAX_ENEMY_HULL );
	while ( !accept_guns[ gun ] )
		gun = Util::rnd( MAX_ENEMY_GUNS );
	while ( !accept_hull[ hull ] )
		hull = Util::rnd( MAX_ENEMY_HULL );
	while ( !accept_move[ move ] )
		move = Util::rnd( MAX_ENEMY_MOVE );

	double dx = (double)Util::rnd(2000) / 200.0 - 5.0;
	double dy = (double)Util::rnd(1300) / 300.0 + 3.0;
	int pattern = Util::rnd( 9 );

	switch( pattern ) {

		case 0  : {
			sh->push_back( new EnemyGeneric(x,y,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group ) );
			sh->push_back( new EnemyGeneric(x+60,y,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group ) );
			break;

		}
		case 1  : {

			sh->push_back( new EnemyGeneric(x,y,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group ) );
			sh->push_back( new EnemyGeneric(x+60,y,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group ) );
			sh->push_back( new EnemyGeneric(x+120,y,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group ) );

			break;

		}
		case 2  : {

			sh->push_back( new EnemyGeneric(x,y,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group ) );
			sh->push_back( new EnemyGeneric(x+140,y,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group ) );
			sh->push_back( new EnemyGeneric(x+70,y+30,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group ) );
			sh->push_back( new EnemyGeneric(x,y+60,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group ) );
			sh->push_back( new EnemyGeneric(x+140,y+60,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group ) );

			break;
		}
		case 3  : {

			sh->push_back( new EnemyGeneric(x,y,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group ) );
			sh->push_back( new EnemyGeneric(x+40,y+20,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group ) );
			sh->push_back( new EnemyGeneric(x+80,y+40,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group ) );
			sh->push_back( new EnemyGeneric(x+120,y+20,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group ) );
			sh->push_back( new EnemyGeneric(x+160,y,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group ) );

			break;

		}

		case 4  : {
			int spacer = Util::rnd( 2 ) * 15 + 20;

			sh->push_back( new EnemyGeneric(x,y,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group ) );
			sh->push_back( new EnemyGeneric(x,y-spacer,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group ) );
			sh->push_back( new EnemyGeneric(x,y-spacer*2,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group ) );

			break;

		}

		case 5  : {
			int spacer = Util::rnd( 5 ) * 10 + 25;
			sh->push_back( new EnemyGeneric(x,y,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group ) );
			sh->push_back( new EnemyGeneric(x,y-spacer*1,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group ) );
			sh->push_back( new EnemyGeneric(x,y-spacer*2,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group ) );
			sh->push_back( new EnemyGeneric(x,y-spacer*3,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group ) );
			sh->push_back( new EnemyGeneric(x,y-spacer*4,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group ) );

			break;

		}
		case 6  : {

			int ang = 270-20*2;
			for ( int q = 0; q < 5; q++ ) {
				sh->push_back( new EnemyGeneric((int)(x+Tcos(ang)*85),(int)(y+Tsine(ang)*90),getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group ) );
				ang += 20;
			}

			break;
		}
		case 7  : {
			sh->push_back( new EnemyGeneric(x,y,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group ) );
			sh->push_back( new EnemyGeneric(x+100,y,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group ) );
			sh->push_back( new EnemyGeneric(x+50,y+40,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group ) );

			break;

		}

		case 8  : {

			sh->push_back( new EnemyGeneric(x,y,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group ) );
			sh->push_back( new EnemyGeneric(x+100,y,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group ) );
			sh->push_back( new EnemyGeneric(x,y+40,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group ) );
			sh->push_back( new EnemyGeneric(x+100,y+40,getHull(hull,1,accept_hull[hull]),getWeapon(gun),getMove(move,dx,dy), who_group ) );

			break;

		}

	}					  //switch

}


/*
int LevelCreator::file_length( FILE * fv ){

	fseek( fv, 0, SEEK_END );
	int l = ftell( fv );
	fseek( fv, 0, SEEK_SET );
	return l;

}
*/

char * LevelCreator::get_token( char * list, char find ) {

	while ( *list != 0 && *list != find ) list++;
	if ( *list == 0 ) return NULL;
	return list;

}

/* processFile:
 * Reads a file to determine how the level will be set up.
 * File determines the following things:
 * - What kind of enemies can be made
 * - What kind of guns can they have
 * - What kind of movement patterns can they have
 */
int LevelCreator::processFile( const char * file_name ) {

	// This function is so obvuios, it needs no comments

	bool use_hull[ MAX_ENEMY_HULL ];
	bool use_guns[ MAX_ENEMY_GUNS ];
	bool use_move[ MAX_ENEMY_MOVE ];

	for ( int q = 0; q < MAX_ENEMY_HULL; q++ )
		use_hull[q] = false;
	for ( int q = 0; q < MAX_ENEMY_MOVE; q++ )
		use_move[q] = false;
	for ( int q = 0; q < MAX_ENEMY_GUNS; q++ )
		use_guns[q] = false;

	FILE * fv = fopen( file_name, "rb" );
	if ( !fv ) {
		printf("Playing %s without rules\n", file_name );
		return 0;
	}

	while ( !feof( fv ) ) {

		char * words = new char[ 1024 ];
		fgets( words, 1024, fv );

		if ( *words != '#' ) {

			char * line = words;
			if ( *line == '[' ) {

				line++;
				char * syntax = line;
				line = get_token( line, ']' );
				if ( line == NULL ) {
					delete[] words;
					return 1;
				}
				*line = '\0';
				line++;
				upstring( syntax );
				line = get_token( line, '=' );
				if ( line == NULL ) {
					delete[] words;
					return 1;
				}
				line++;
				while( *line != 0 ) {

					while ( *line == ' ' && *line != '\n' && *line != 0 ) line++;
					char * num = line;
					while ( *line != ' ' && *line != '\n' && *line != 0 ) line++;
					if ( *line != 0 ) {
						*line = '\0';
						line++;
					} else *line = '\0';

					int use = str2int( num );

					if ( strcasecmp(syntax,"HULL") == 0 )
						if ( use >= 0 && use < MAX_ENEMY_HULL )
							use_hull[ use ] = true;
					if ( strcasecmp(syntax,"GUNS") == 0 )
						if ( use >= 0 && use < MAX_ENEMY_GUNS )
							use_guns[ use ] = true;
					if ( strcasecmp(syntax,"MOVE") == 0 )
						if ( use >= 0 && use < MAX_ENEMY_MOVE )
							use_move[ use ] = true;

				}

			}

		}

		delete[] words;

	}

	bool cy = false;
	for ( int q = 0; q < MAX_ENEMY_GUNS; q++ )
		if ( use_guns[q] ) cy = true;

	if ( cy )
		for ( int q = 0; q < MAX_ENEMY_GUNS; q++ )
			if ( !use_guns[q] ) accept_guns[q] = 0;

	cy = false;
	for ( int q = 0; q < MAX_ENEMY_MOVE; q++ )
		if ( use_move[q] ) cy = true;

	if ( cy )
		for ( int q = 0; q < MAX_ENEMY_MOVE; q++ )
			if ( !use_move[q] ) accept_move[q] = 0;

	cy = false;
	for ( int q = 0; q < MAX_ENEMY_HULL; q++ )
		if ( use_hull[q] ) cy = true;

	if ( cy )
		for ( int q = 0; q < MAX_ENEMY_HULL; q++ )
			if ( !use_hull[q] ) accept_hull[q] = 0;

	return 0;

}


double LevelCreator::life_level( double level, int min ) {
	// Some stupid equation to determine how much life an enemy should get
	return level * fsqr(level+min) / 4.0;

	// A recursive way of doing it. Not to good!!
	if ( level == 0 ) return min;
	double d = life_level( level-1, min );
	return sqrt( fsqr( d ) * level * 2.0 ) / sqrt( level + 1 ) + d/3.0 + level*2;

}

Group * LevelCreator::Boss( int y, int _life ){

	Group * who_group = new Group( y );
	/* TODO: fix

	new EnemyGeneric( Util::screen_x/2 ,y, new HullObject( (BITMAP *)global_data[BOSS_01].dat, _life, SHIP_DAMAGE,1,1,10,false,gl_collide[gl_map(BOSS_01)] ), getWeapon(13),getMove(9,5,5), who_group );
	*/

	return who_group;
	
}

Group * LevelCreator::makeCloud( int x, int y ){

	Group * who_group = new Group( y );
	// double dy = (double)Util::rnd(120) / 50.0 - 1.0;
	/* TODO: fix 
	new ShipObject( x, y, 0, new HullObject((BITMAP *)global_data[CLOUD1].dat, 1,0,0,0,Util::rnd( 7 ) + 6, true, NULL ), who_group, new Move( 0, 3.0+dy ), TEAM_ENEMY );
	*/
	return who_group;


}

void LevelCreator::load_file( const char * file_name, SpaceObject * player ) {

	accept_guns = new int[ MAX_ENEMY_GUNS ];
	accept_hull = new int[ MAX_ENEMY_HULL ];
	accept_move = new int[ MAX_ENEMY_MOVE ];

	int dif = ( (PlayerObject *)player )->getDifficulty();
	double lev = ( (PlayerObject *)player )->getLevel();
	int min = 1;
	int max = 2;

	double life_enhance = 1;
	switch ( dif ) {
		case 1  :       life_enhance = 0.80; min = 2; max = 5;break;
		case 2  :       life_enhance = 0.90; min = 3; max = 6;break;
		case 3  :       life_enhance = 1.0; min = 4; max = 8;break;
		case 4  :       life_enhance = 1.20; min = 5; max = 10;break;
		case 5  :       life_enhance = 1.35; min = 6; max = 12;break;
	}

	for ( int q = 0; q < MAX_ENEMY_GUNS; q++ )
		accept_guns[q] = 1;
	for ( int q = 0; q < MAX_ENEMY_MOVE; q++ )
		accept_move[q] = 1;

	int min_life = (int)life_level( lev, min );
	int max_life = min_life / 2 + min_life;

	meteor_life = min_life;

	for ( int q = 0; q < MAX_ENEMY_HULL; q++ ) {
		int ml;
		ml = Util::rnd( max_life - min_life ) + min_life;
		accept_hull[q] = ml;
	}

	if ( processFile( file_name ) != 0 )
		printf("Error processing %s. Skipping..\n", file_name );

	/* length of level */
	int peak = 7000 + dif * 250;

	// peak = 500;

	/*
	for ( int ay = 70; ay < peak; ay += 160 ){

		int m = Util::rnd( dif ) + 1;
		for ( int ac = 0; ac < m; ac++ ){

			int x = Util::rnd( Util::screen_x - 100 ) + 100;
			int y = -(ay + Util::rnd( 20 ) - 10 );

			char * fake_data = new char[ 2 ];
			trigger * add_t = new trigger( fake_data, 2, SHIP_TRIGGER, x, y );
	trigger_list.push_back( add_t );
	}

	}
	*/

	// Make a bunch of groups randomly
	for ( int ay = 100; ay < peak; ay += 160 ) {
		int m = Util::rnd( dif ) + 1;
		for ( int ac = 0; ac < m; ac++ ) {
			int x = Util::rnd( Util::screen_x - 100 ) + 100;
			int y = -(ay + Util::rnd( 20 ) - 10 );
			group_list.push_back( randomGroup( x, y ) );

			//if ( Util::rnd( 3 ) == Util::rnd( 3 ) )
			//	group_list.push_back( makeCloud( x, y + Util::rnd( 30 ) ) );
		}

		if ( Util::rnd( 3 ) )
			group_list.push_back( makeCloud( Util::rnd( Util::screen_x - 100 ) + 100, -(ay + Util::rnd(30)-10) ) );
	}

	// Sup boss..
	//group_list.push_back( Boss( -(peak+200), max_life * 130 ) );

	// Make some triggers of varied type
	char * fake_data = new char[ 2 ];
	trigger * add_t = new trigger( fake_data, 2, POWER_TRIGGER, Util::rnd( Util::screen_x - 100 ) + 100, -7000 + Util::rnd( 100 ) );
	trigger_list.push_back( add_t );
	for ( int q = 0; q < Util::rnd( 5 ); q++ ) {

		fake_data = new char[ 2 ];
		*fake_data = Util::rnd( 50 ) + 5;
		add_t = new trigger( fake_data, 2, METEOR_ON_TRIGGER, Util::rnd( Util::screen_x - 100 ) + 100, -( Util::rnd( 6000 ) + 1000 ) );
		trigger_list.push_back( add_t );

	}
	for ( int q = 0; q < Util::rnd( 5 ); q++ ) {
		fake_data = new char[ 2 ];
		add_t = new trigger( fake_data, 2, METEOR_OFF_TRIGGER, Util::rnd( Util::screen_x - 100 ) + 100, -( Util::rnd( 6000 ) + 1000 ) );
		trigger_list.push_back( add_t );
	}
	for ( int q = 0; q < Util::rnd( 3 ); q++ ) {
		fake_data = new char[ 2 ];
		add_t = new trigger( fake_data, 2, HEALTH_TRIGGER, Util::rnd( Util::screen_x - 100 ) + 100, -( Util::rnd( 4000 ) + 3000 ) );
		trigger_list.push_back( add_t );
	}
}

/* LevelCreator:
 * Constructor. Creates all ECollides that enemies will use. Loads the level from a file.
 */
LevelCreator::LevelCreator( const char * file_name, SpaceObject * player ) {
	//info = new info_holder*[ MAX_SHIPS ];
	counter = 0;
	lerror = false;
	max_use = 0;

	num_cloud = 0;
	meteor_chance = 0;

	trigger_list.clear();


	//total collide objects = total ships + meteor + money + powerup + weaponup + health + boss
	gl_collide = new ECollide*[ MAX_GL_COLLIDE ];
	for ( int q = 0; q < MAX_GL_COLLIDE; q++ )
		gl_collide[q] = NULL;
	for ( int q = SHIP0_FIRST+1; q < SHIP_LAST; q++ ){
		// gl_collide[ gl_map( q ) ] = new ECollide((BITMAP *)global_data[q].dat,6,makecol(255,0,255),42);
		Bitmap l = Util::getDataSprite( q );
		gl_collide[ gl_map( q ) ] = new ECollide( &l );
	}

	// gl_collide[ gl_map(METEOR_1) ] = new ECollide((BITMAP *)global_data[METEOR_1].dat);
	gl_collide[ gl_map(METEOR_1) ] = new ECollide( Util::getDataSprite( METEOR_1 ) );
	gl_collide[ gl_map(COIN_1) ] = new ECollide( Util::getDataSprite( COIN_1 ) );
	gl_collide[ gl_map(POWERUP_1)] = new ECollide( Util::getDataSprite( POWERUP_1 ) );
	gl_collide[ gl_map(WEAPONUP_001) ] = new ECollide( Util::getDataSprite( WEAPONUP_001 ) );
	gl_collide[ gl_map(HEALTH_001) ] = new ECollide( Util::getDataSprite( HEALTH_001 ) );
	gl_collide[ gl_map(BOSS_01) ] = new ECollide( Util::getDataSprite( BOSS_01 ) );
	/*
	gl_collide[ gl_map(METEOR_1) ] = new ECollide((BITMAP *)Util::global_data[METEOR_1].dat,6,makecol(255,0,255),45);
	gl_collide[ gl_map(COIN_1) ] = new ECollide((BITMAP *)Util::global_data[COIN_1].dat,6,makecol(255,0,255),52);
	gl_collide[ gl_map(POWERUP_1)] = new ECollide((BITMAP *)Util::global_data[POWERUP_1].dat,6,makecol(255,0,255),52);
	gl_collide[ gl_map(WEAPONUP_001) ] = new ECollide((BITMAP *)Util::global_data[WEAPONUP_001].dat,6,makecol(255,0,255),52);
	gl_collide[ gl_map(HEALTH_001) ] = new ECollide( (BITMAP *)Util::global_data[HEALTH_001].dat,6,makecol(255,0,255),52);
	gl_collide[ gl_map(BOSS_01) ] = new ECollide( (BITMAP *)Util::global_data[BOSS_01].dat,6,makecol(255,0,255),52);
	*/

	char final_file[ 4096 ];
	Util::getDataPath( final_file, file_name );
	// char * final_file = Util::data_file( file_name );

	group_list.clear();
	load_file( final_file, player );
	// free( final_file );

	current_counter = 0;

	int mpics = COIN_A_20 - COIN_1 + 1;
	for ( int q = 0; q < mpics; q++ ){

		Bitmap bitmap = Bitmap( Util::getDataSprite( COIN_1 + q ), true );
		Bitmap use = Util::getDataSprite( COIN_1 + q );

		hull_money_shadows.push_back( bitmap );
		int m = 22;
		bitmap.fill( Bitmap::makeColor( m, m, m ) );
		use.drawMask( 0, 0, bitmap );
	}
}

/* noExist:
 * Return an error cuase we screwed up somewhere
 */
bool LevelCreator::noExist() {
	return lerror;
}

/* Draw:
 * What was I thinking? Maybe ill put some code here eventually
 */
void LevelCreator::Draw( BITMAP * work, int xfac, int yfac ) {
}

/* gl_map:
 * Recursive call to find the appropriate value for a defined constant
 */
static int gl_map( int who ) {

	if ( who >= SHIP0_FIRST && who <= SHIP_LAST )
		return who-(SHIP0_FIRST+1);
	if ( who == METEOR_1 )
		return gl_map(SHIP_LAST-1)+1;
	if ( who == COIN_1 )
		return gl_map(METEOR_1)+1;
	if ( who == POWERUP_1 )
		return gl_map(COIN_1)+1;
	if ( who == WEAPONUP_001 )
		return gl_map(POWERUP_1)+1;
	if ( who == HEALTH_001 )
		return gl_map(WEAPONUP_001)+1;
	if ( who == BOSS_01 )
		return gl_map(HEALTH_001)+1;
	return 0;

}

/* done:
 * Returns true if level is done making things.
 * Whoa, look at all those return statements. They are there for beauty and ambieance( sp? ).
 */
bool LevelCreator::done() {

	return group_list.empty();

	return trigger_list.empty();

	if ( counter == 0 ) {
		int total = 0;
		//for ( int q = 0; q <= max_use; q++ )
		//	if ( info[q] != NULL ) total++;
		if ( total == 0 )
			counter = 500;
	} else if( counter > 1 )counter--;
	return counter == 1;
}


/*
void LevelCreator::emergency( vector< SpaceObject * > * sh ){

	if ( Util::rnd( 260 ) == Util::rnd( 260 ) ){

		int x = Util::rnd( Util::screen_x - 50 ) + 50;
		int y = -100;

		int mpics = HEALTH_021 - HEALTH_001 + 1;
		BITMAP ** pics = new BITMAP*[ mpics ];
		for ( int q = 0; q < mpics; q++ )
pics[ q ] = (BITMAP *)Util::global_data[ HEALTH_001 + q ].dat;

sh->push_back(new Health(x,y,new HullAnimation( pics, mpics,1,0,0,0,10,false,gl_collide[gl_map(HEALTH_001)]),new Move(0,4.5)));
}
}
*/

static SpaceObject * createCloak( const int x, const int y ){
	vector< Bitmap > pics;
	int mpics = 0;

	mpics = WEAPONUP_020 - WEAPONUP_001 + 1;
	for ( int q = 0; q < mpics; q++ ){
		pics.push_back( Util::getDataSprite( WEAPONUP_001 + q ) );
	}
	return new Cloak( x, y, new HullAnimation(pics, vector< Bitmap >(), 1, 0, 0, 0, 10, false, gl_collide[gl_map(WEAPONUP_001)]), new Move(0,2.5) );

}

static SpaceObject * createPowerUp( const int x, const int y ){
	vector< Bitmap > pics;

	int mpics = POWERUP_A_14 - POWERUP_1 + 1;
	for ( int q = 0; q < mpics; q++ ){
		pics.push_back( Util::getDataSprite( POWERUP_1 + q ) );
	}
	return new PowerUp( x, y, new HullAnimation( pics, vector< Bitmap >(), 1, 0, 0, 0, 10, false, gl_collide[gl_map(POWERUP_1)]), new Move(0,2.5) );

}

static SpaceObject * createHealth( const int x, const int y ){

	vector< Bitmap > pics;
	int mpics = HEALTH_021 - HEALTH_001 + 1;
	for ( int q = 0; q < mpics; q++ ){
		pics.push_back( Util::getDataSprite( HEALTH_001 + q ) );
	}
	return new Health( x, y, new HullAnimation(pics,vector< Bitmap >(), 1, 0, 0, 0, 10, false, gl_collide[gl_map(HEALTH_001)]), new Move( 0, 2.5 ) );

}

static SpaceObject * createMoney( const int x, const int y, const SpaceObject * player ){

	vector< Bitmap > pics;
	int mpics = COIN_A_20 - COIN_1 + 1;
	for ( int q = 0; q < mpics; q++ ){
		pics.push_back( Util::getDataSprite( COIN_1 + q ) );
	}

	int lev = -1;
	int min = 10;
	int max = 4000;
	if ( player != NULL ) {
		lev = ( (PlayerObject *)player )->getLevel();
		min = 10*lev;
		max = 2000*lev;
	}

	int q = Util::rnd( max - min ) + min;

	return new Money( x, y, q, new HullAnimation( pics, hull_money_shadows, 1, 0, 0, 0, 10, false, gl_collide[gl_map(COIN_1)] ), new Move( 0, 2 ) );

}

/* special:
 * Makes a special item. Can be one of the following:
 * - Powerup
 * - Cloak
 * - Health
 * - Money
 */
SpaceObject * LevelCreator::special( int x, int y, const SpaceObject * player ) {


	if ( Util::rnd( 50 ) == Util::rnd( 50 ) ) {
		return createCloak( x, y );
	}

	if ( Util::rnd( 60 ) == Util::rnd( 60 ) ) {
		return createPowerUp( x, y );
	}

	/* if the player has low life increase the chances a health will appear */
	int h_rnd = 21;
	if ( player != NULL ){
		if ( player->getLife() < 30 ) h_rnd = 4;
	}

	if ( Util::rnd( h_rnd ) == Util::rnd( h_rnd ) ) {
		return createHealth( x, y );
	}

	return createMoney( x, y, player );
	// return NULL;

}

/* getHull:
 * Some of the enemies have special hulls associated with them, so they need their own class
 */
HullObject * LevelCreator::getHull( int a, int l, int _life ) {
	a++;

	/* TODO: fix
	switch( a ) {
		//case 0  :       return new OrbHull( l );
		//case 1  :       return new ShardHull( l );
		//case 2  :       return new TangoHull( Util::rnd(32) + 32, l );
		//case 3  :       return new HeliHull( (BITMAP *)Util::global_data[SHIP_003].dat, _life, l, gl_collide[gl_map(SHIP_003)] );
		case 5  :       return new ShieldHull( (BITMAP *)Util::global_data[SHIP_005].dat, _life, l, gl_collide[gl_map(SHIP_005)] );
		//case 5	:	return new StrongHull( Util::rnd(32) + 32, l );
		//case 6	:	return new SplitHull( Util::rnd(32) + 32, l );
		//case 7	:	return new HullObject( BLOCK, 100, 0, 0, 0, 8, NULL );
		//case 8	:	return new Ship6(l);
		//case 9	:	return new Ship7(l);
		case 8 : {
			HullObject * h = new HullObject( (BITMAP *)Util::global_data[SHIP_008].dat,_life,SHIP_DAMAGE,2,l,10,false,gl_collide[gl_map(SHIP0_FIRST+a)] );
			h->giveWeapon( new GunDestruct(1,TEAM_ENEMY), 1 );
			return h;
		}
		case 9  : {

			int mpics = HELICOPTER_6 - HELICOPTER_1 + 1;
			BITMAP ** pics = new BITMAP*[ mpics ];
			for ( int q = 0; q < mpics; q++ )
				pics[q] = (BITMAP *)Util::global_data[ HELICOPTER_1 + q ].dat;

			return new HullAnimation( pics, mpics, NULL,_life, SHIP_DAMAGE, 1, l, 10, false, gl_collide[gl_map(SHIP0_FIRST+a)] );

		}
	}
	*/
	return new HullObject( new Bitmap( Util::getDataSprite( SHIP0_FIRST + a ) ), _life, SHIP_DAMAGE,1,l,10,false,gl_collide[gl_map(SHIP0_FIRST+a)] );
}


int LevelCreator::hullNum( int a, int l ) {
	a++;
	return SHIP0_FIRST+a;
	switch( a ) {
		case 1  :       return SHIP_001;
		case 2  :       return SHIP_002;
		case 4  :       return SHIP_004;
		case 6  :       return SHIP_006;
		case 7  :       return SHIP_007;
	}
	return -1;
}

/* getWeapon:
 * Return a weapon depending on its number
 */
WeaponObject * LevelCreator::getWeapon( int a ) {
	switch( a ) {
		case 0  :       return new EnemyStraightShooter( 1, TEAM_ENEMY );
		case 1  :       return new EnemyLargeStraightShooter( 1, TEAM_ENEMY );
		case 2  :       return new EnemyDoubleNearStraightShooter( 1, TEAM_ENEMY );
		case 3  :       return new EnemyDoubleFarStraightShooter( 1, TEAM_ENEMY );
		case 4  :       return new EnemyFindSingle( 1, TEAM_ENEMY );
		case 5  :       return new WeaponFire( 1, 1, TEAM_ENEMY );
		case 6  :       return new EnemyFindSingleMachine( 1, TEAM_ENEMY );
		case 7  :       return new EnemyFindLarge( 1, TEAM_ENEMY );
		case 8  :       return new EnemyMachineLight( 1, TEAM_ENEMY );
		case 9  :       return new EnemyMissle( 1, TEAM_ENEMY );
		case 10 :       return new EnemySide( 1, TEAM_ENEMY );
		case 11 :       return new EnemyTwirlStraight( 1, TEAM_ENEMY );
		case 12 :       return new EnemyTwirlFind( 1, TEAM_ENEMY );
		case 13 :       return new EnemyTwirlMachine( 1, TEAM_ENEMY );
		case 14 :       return new EnemyCork( 1, TEAM_ENEMY );
	}
	return NULL;
}

/* getMove:
 * Return a movement style depending on its number
 */
Move * LevelCreator::getMove( int a, double _dx, double _dy ) {
	if ( _dy <= 0 )
		_dy = 1;
	switch( a ) {
		case 0  :       return new Move( _dx, _dy );
		case 1  :       return new MoveHorizontal( _dx, _dy );
		case 2  :       return new MoveMine( _dx, _dy );
		case 3  :       return new MoveAngular( _dx, _dy );
		case 4  :       return new MoveSwingRight( _dx, _dy );
		case 5  :       return new MoveSwingLeft( _dx, _dy );
		case 6  :       return new MoveSine( _dx, _dy );
		case 7  :       return new MoveSwingDown( _dx, _dy );
		case 8  :       return new MoveCircle_Player( _dx, _dy );
		case 9	:	return new MoveFind( _dx, _dy );
	}
	return new Move( 0, 2 );
}

/* GetEnemy:
 * Returns NULL. Whoa
 */
SpaceObject * LevelCreator::GetEnemy( int cx, int cy, int hu,int we,int m,double _dx,double _dy ) {

	//HullObject * can;
	/*
	if ( hullNum( hu, 1 ) == -1 ) can = GetHull(hu,1);
	else can = new HullObject( hullNum(hu,1), 20+Util::rnd(15), SHIP_DAMAGE, 1, 1, 10,gl_collide[gl_map(hullNum(hu,1))]);
	*/
	//can = GetHull( hu, 1 );

	//return new EnemyGeneric(cx,cy,can,GetWeapon(we),GetMove(m,_dx,_dy) );
	return NULL;
}

/* create:
 * Puts new enemies into the enemy list.
 */
void LevelCreator::create( vector< SpaceObject * > * sh, int leva, const double & speed ) {

	current_counter -= 2;

	/* Search through all the groups. If group is close enough to the player, put
	 * all the ships the group contains into the object list passed to create via `sh'.
	 */
	for ( vector< class Group * >::iterator it = group_list.begin(); it != group_list.end(); ) {

		Group * group = *it;

		if ( group->pos() + 100 >= current_counter ) {
			for ( vector< class SpaceObject * >::const_iterator vv = group->members()->begin(); vv != group->members()->end(); vv++ ) {
				SpaceObject * object = *vv;
				object->SetCoordXY( object->getX(), object->getY() - group->pos() - 100 );
				sh->push_back( object );
			}
			it = group_list.erase( it );
		} else ++it;

	}

	/* Search through all triggers and activate them if they are close enough to the player */
	for ( vector< class trigger * >::iterator it = trigger_list.begin(); it != trigger_list.end(); it++ ) {

		if ( (*it)->CY()+100 >= current_counter ) {
			switch( (*it)->kind() ) {

				//case SHIP_TRIGGER	:	sh->push_back((SpaceObject *)(*it)->get(this));break;
				/*case SHIP_TRIGGER	:	{

									Group * mg = new Group();
									randomShip( (*it)->CX(), -100, mg, sh );
									break;

								}
				*/
				// Power_Trigger: Creates a powerup
				case POWER_TRIGGER      : {
					/* TODO: fix
					int mpics = POWERUP_A_14 - POWERUP_1 + 1;
					BITMAP ** pics = new BITMAP * [ mpics ];
					for ( int q = 0; q < mpics; q++ )
						pics[q] = (BITMAP *)global_data[ POWERUP_1 + q ].dat;
					sh->push_back( new PowerUp( (*it)->CX(), -100, new HullAnimation(pics,mpics,NULL,1,0,0,0,10,false,gl_collide[gl_map(POWERUP_1)]), new Move(0,5) ) );
					*/
					break;

				}
				// Meteor_on_trigger: Sets the meteor random number to be greater
				// than 0 so that meteors are created during gameplay.
				case METEOR_ON_TRIGGER  : {
					char * num = (char *)(*it)->get( NULL );
					meteor_chance = *num;
					break;
				}
				// Meteor_off_trigger: Sets meteor random number to 0 so that
				// no meteors are created during gameplay.
				case METEOR_OFF_TRIGGER :       meteor_chance = 0; break;

				// Health_trigger: Creates a health.
				case HEALTH_TRIGGER     : {

					/* TODO: fix
					int mpics = HEALTH_021 - HEALTH_001 + 1;
					BITMAP ** pics = new BITMAP * [ mpics ];
					for ( int q = 0; q < mpics; q++ )
						pics[q] = (BITMAP *)global_data[ HEALTH_001 + q ].dat;
					sh->push_back( new Health( (*it)->CX(), -100, new HullAnimation(pics,mpics,NULL,1,0,0,0,10,false,gl_collide[gl_map(HEALTH_001)]), new Move(0,4.5) ) );
					*/

					break;
				}

			}

			// We have used the trigger, so we must kill it
			(*it)->kill();
		}

	}

	/* Delete all triggers that have been killed */
	for ( vector< class trigger * >::iterator it = trigger_list.begin(); it != trigger_list.end(); ){
		if ( (*it)->kind() == -1 ) {
			trigger * temp = *it;
			it = trigger_list.erase( it );
			delete temp;
		} else ++it;
	}

	/* Game isnt over, so make some whacky things for your amusement! */
	if ( !done() ) {

		if ( num_cloud ) num_cloud--;

		// Make a meteor with some velocity
		if ( Util::rnd( meteor_chance ) == Util::rnd( meteor_chance ) && meteor_chance > 0 ) {

			/* TODO: fix
			double dx = (double)( Util::rnd(90) ) / (double)( 25 ) * (Util::rnd(2)*2-1);
			double dy = (double)( Util::rnd(200) ) / (double)( 25 ) + 2.3;
			//int lv = (int)( 25.0 + real_level * 2 );
			//SpaceObject * use =  new ShipObject( Util::rnd( 640 ), Util::rnd( 30 ) - 50, 40, new MeteorHull(leva,lv,gl_collide[ gl_map(METEOR_1) ] ), NULL, new Move(dx,dy), TEAM_ENEMY );
			int mpics = METEOR_9_20 - METEOR_1 + 1;
			BITMAP ** pics = new BITMAP*[ mpics ];
			for ( int q = 0; q < mpics; q++ )
				pics[ q ] = (BITMAP *)global_data[ METEOR_1 + q ].dat;

			SpaceObject * use = new MeteorObject(Util::rnd(640),Util::rnd(30)-50,-meteor_life*3, new HullAnimation( pics, mpics,NULL,meteor_life,0,0,0,10,false,gl_collide[gl_map(METEOR_1)]), new Move(dx,dy) );

			sh->push_back( use );
			*/
		}

		/*
		else if ( Util::rnd( 80 ) == Util::rnd( 80 ) && !num_cloud ) {

			// Make a fancy cloud!
			num_cloud = 60;

			double dy = (double)Util::rnd(120) / 50.0 - 1.0;
			SpaceObject * use = new ShipObject( Util::rnd(640), -200, 0, new HullObject((BITMAP *)global_data[CLOUD1].dat, 1,0,0,0,Util::rnd( 7 ) + 6, true, NULL ), NULL, new Move( 0, 3.0+dy ), TEAM_ENEMY );
			sh->push_back( use );
		}
		*/
	}

}

/* destructor
 */
LevelCreator::~LevelCreator() {

	// Delete all triggers
	for ( vector< class trigger * >::iterator it = trigger_list.begin(); it != trigger_list.end(); ) {
		trigger * temp = *it;
		it = trigger_list.erase( it );
		delete temp;
	}

	// Delete all groups and their associated ships
	for ( vector< class Group * >::iterator it = group_list.begin(); it != group_list.end(); ){
		Group * del = *it;
		it = group_list.erase( it );
		delete del;
	}

	// Delete all ECollides that were stored for optimization
	for ( int q = 0; q < MAX_GL_COLLIDE; q++ )
		if ( gl_collide[q] != NULL )
			delete gl_collide[q];
	delete[] gl_collide;
	delete[] accept_hull;
	delete[] accept_guns;
	delete[] accept_move;
	
	hull_money_shadows.clear();

	/*
	for ( int q = 0; q < max_money_shadow; q++ )
		destroy_bitmap( hull_money_shadows[q] );
	delete[] hull_money_shadows;
	*/
}
