#ifndef _def_h_
#define _def_h_

#ifndef NULL
#define NULL 0
#endif

#include "font.h"

const double missle_speed = -0.56;
// #define missle_speed -0.56

const int MAX_ENEMY = 50;
// #define MAX_ENEMY 50

// #define USE_AMMO 8
// #define MAX_EXPL 200

const int expl_color = 254;
// #define expl_color 254
const int PLAYER_TOTAL = 1;
// #define PLAYER_TOTAL 1
const int MAX_PLANE = 20;
// #define MAX_PLANE 20
const int NO_EXPLODE = 4000;
// #define NO_EXPLODE 4000

const int GRAPHICS_X = 640;
// #define GRAPHICS_X 640
const int GRAPHICS_Y = 480;
// #define GRAPHICS_Y 480

const int SCALE_X = GRAPHICS_X;
const int SCALE_Y = GRAPHICS_Y;

const int TEAM_ENEMY = 1;
// #define TEAM_ENEMY 1
const int TEAM_PLAYER = 2;
// #define TEAM_PLAYER 2

const int SHIP_DAMAGE = 4;
// #define SHIP_DAMAGE 4

/*
#define SMALL_BULLET 1.6
#define LARGE_BULLET 1.6
#define FIND_BULLET 1.2
#define ENEMY_MISSLE 1.9
*/

const int PLANE_AIR = 1;
// #define PLANE_AIR 1
const int PLANE_GROUND = 2;
// #define PLANE_GROUND 2



// #define Y_BLIT_OFFSET 500

//#define MAX_GAMMO 350
//#define MAX_BAMMO 100

const int MAX_E_COLOR = 100;
// #define MAX_E_COLOR 100

const int MAX_EX = 6;
// #define MAX_EX 6

/*
#ifdef UNIX
#define DATADIR ./data
#else
#define DATADIR .\data
#endif
*/

#include "explode.h"
#include "bitmap.h"
#include "rfont.h"
#include <stdio.h>
#include <vector>

using namespace std;

struct DATAFILE;
struct SAMPLE;

namespace Util{

/*
	class ECollide;
	class ExplosionClass;
*/

	extern int screen_x;
	extern int screen_y;

	// extern RFont * raptor_font;

	extern int * e_color;
	extern float sound_vol;
	// extern float music_vol;

	extern DATAFILE * global_fonts;
	extern DATAFILE * global_data;
	extern DATAFILE * global_snd;

	const double TPI = 3.141592654;
	const double PI = TPI;

	extern volatile unsigned int speed_counter;

	Font getNormalFont();
	Font getMenuFont();
	Font getDefaultFont();

	vector< string > getFiles( string datapath, string find );

	void loadGlobals();
	void unloadGlobals();

	const char * getOS();

	Bitmap getDataSprite( int num );

	int rnd( int q );
	int pcount( char ** p, const int m );
	int readnum( FILE * fv, int num );
	int addcol( int c1, int c2 );

	bool exists( const char * filename );

	time_t fileTime( const char * filename );

	void alert( const char * message );

	unsigned int getTicks( unsigned int * tick );

	void playSound( int m, int vol );
	void play_sound( DATAFILE * snd, int m, int vol );
	void play_sound( SAMPLE * snd, int vol );
	void blend_palette( int * pal, int mp, int sc, int ec );
	void explColor();
	void MakeExplosion( ExplosionClass ** expl, int M_EX, int x, int y );
	unsigned char getByte( unsigned char q, int byte );
	unsigned char setByte( unsigned char n, int byte, unsigned char p );
	void bitscramble( char & q );
	void scramble( char * scram, const int m );
	void YIELD();
	// void draw_mask( BITMAP * dest, BITMAP * source, int _x, int _y );

	// char * data_file( const char * file_name );
	void getDataPath( char * buffer, const char * file );
	string getInstallDirectory();
}

#endif
