#ifndef _level_h
#define _level_h

#include <vector>
#include "trigger.h"
#include "bitmap.h"
#include <stdlib.h>

using namespace std;

class SpaceObject;
class HullObject;
class WeaponObject;
class Move;
class ECollide;
class PCKLoader;
class Group;

#define MAX_SHIPS 2000

struct info_holder{
	int x, y;
	double dx, dy;
	int gun, hull, move;
};

class LevelCreator{
public:

	LevelCreator( const char * file_name, SpaceObject * player );
	bool done();
	bool noExist();
	void create( vector< SpaceObject * > * sh, int leva, const double & speed );
	//void emergency( vector< SpaceObject * > * sh );
	void Draw( BITMAP * work, int xfac, int yfac );
	SpaceObject * special( int x, int y, const SpaceObject * player );
        SpaceObject * createPowerUp( const int x, const int y );
	~LevelCreator();
	
	HullObject * getHull( int a, int l, int _life );
	WeaponObject * getWeapon( int a );
	SpaceObject * GetEnemy( int cx, int cy, int hu, int we, int m, double _dx, double _dy );
	Move * getMove( int a, double _dx, double _dy );

private:
	int hullNum( int a, int l );

	// int gl_map( int who );
	//int file_length( FILE * fv );

	void load_file( const char * file_name, SpaceObject * player );
	void makeInfo( char * buffer, int & current );
	void randomShip( int x, int y, Group * who_group, vector< SpaceObject * > * sh );
	Group * randomGroup( int x, int y );
	void put_ship( int x, int y, double dx, double dy, int hull, int gun, int move, int life );
	char * get_token( char * list, char find );
	double life_level( double level, int min );
	int processFile( const char * fv );

	Group * Boss( int y, int _life );
	Group * makeCloud( int x, int y );

	//SpaceObject ** ships;
	//info_holder ** info;
	int counter;
	int max_use;
	bool lerror;
	int real_level;
	// ECollide ** gl_collide;

	int num_cloud;

	int current_counter;
	int meteor_chance;

	vector< class trigger * > trigger_list;
	vector< class Group * > group_list;

	int meteor_life;
	int * accept_guns;
	int * accept_hull;
	int * accept_move;

private:
	BITMAP ** hull_meteor_shadows;
	int max_meteor_shadow;
	int max_money_shadow;
	
};

#endif
