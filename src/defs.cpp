#include <allegro.h>

#include "defs.h"
#include <stdlib.h>
#include <stdio.h>
#include "explode.h"
#include "rfont.h"
#include "fonts.h"
#include "font.h"
#include "explode.h"
#include "bitmap.h"
#include "sound.h"

#include "strings.h"
#include <string.h>

#include <vector>

#ifndef INSTALL_DIR
#define INSTALL_DIR "."
#endif

using namespace std;

DATAFILE * Util::global_data;
DATAFILE * Util::global_snd;
DATAFILE * Util::global_fonts;

// RFont * Util::raptor_font;

int Util::screen_x = 640*3/2;
int Util::screen_y = 480;

int * Util::e_color;
float Util::sound_vol;
// float music_vol;

volatile unsigned int Util::speed_counter = 0;

Font Util::getNormalFont(){
	return Font( (FONT *)Util::global_fonts[ LCD_PCX ].dat );
}

Font Util::getMenuFont(){
	return Font( (FONT *)Util::global_fonts[ SQUARE_PCX ].dat );
}
	
Font Util::getDefaultFont(){
	return Font( ::font );
}

unsigned int Util::getTicks( unsigned int * tick ){
	unsigned int diff = Util::speed_counter - *tick;
	*tick = speed_counter;
	return diff;
}

unsigned char Util::getByte( unsigned char q, int byte ) {
	return ( q & ( 1 << byte ) ) >> byte;
}

void Util::YIELD() {
	rest( 1 );

	/*
	#ifdef UNIX
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 1;
	select( 0, NULL, NULL, NULL, &tv );
	#else
	//sleep(1);
	yield_timeslice();
	#endif
	*/
}


unsigned char Util::setByte( unsigned char n, int byte, unsigned char p ) {
	unsigned char final = 0;
	for ( int q = 15; q >= 0; q-- ) {
		unsigned char z = getByte( n, q );
		if ( q == byte )
			z = p;
		final = final << 1 | z;
	}
	return final;
}


void Util::bitscramble( char & q ) {

	q = setByte( q, 5, getByte(q,5)^1 );
	q = setByte( q, 9, getByte(q,9)^1 );

}

Bitmap Util::getDataSprite( int num ){
	return Bitmap( (BITMAP *) Util::global_data[ num ].dat );
}

void Util::alert( const char * message ){
	allegro_message( message );
}

void Util::scramble( char * scram, const int m ) {

	for ( int q = 0; q < m && q+2 < m; q += 3 ) {
		char t = scram[q];
		scram[q] = scram[q+2];
		scram[q+2] = t;
	}
	for ( int q = 0; q < m; q++ )
		bitscramble( scram[q] );

}


int Util::rnd( int q ) {

	/*
	#ifdef UNIX

	return random() % q;

	#else

	return (int)( q * ( (double)rand() / ( (double)RAND_MAX + 1.0 ) ) );
	#endif
	*/
	return (int)( q * ( (double)rand() / ( (double)RAND_MAX + 1.0 ) ) );

}
	
bool Util::exists( const char * filename ){
	return ::exists( filename );
}

const char * Util::getOS() {
	switch( ::os_type ) {
		case OSTYPE_UNKNOWN     :       return "unknown, or regular MSDOS";
		case OSTYPE_WIN3        :       return "Windows 3.1 or earlier";
		case OSTYPE_WIN95       :       return "Windows 95";
		case OSTYPE_WIN98       :       return "Windows 98";
		case OSTYPE_WINME       :       return "Windows ME";
		case OSTYPE_WINNT       :       return "Windows NT";
		case OSTYPE_WIN2000     :       return "Windows 2000";
		case OSTYPE_WINXP       :       return "Windows XP";
		case OSTYPE_OS2         :       return "OS/2";
		case OSTYPE_WARP        :       return "OS/2 Warp 3";
		case OSTYPE_DOSEMU      :       return "Linux DOSEMU";
		case OSTYPE_OPENDOS     :       return "Caldera OpenDOS";
		case OSTYPE_LINUX       :       return "Linux";
		case OSTYPE_FREEBSD     :       return "FreeBSD";
		case OSTYPE_UNIX        :       return "Unknown Unix variant";
		case OSTYPE_BEOS        :       return "BeOS";
		case OSTYPE_QNX         :       return "QNX";
		case OSTYPE_MACOS       :       return "MacOS";
	}
	return "Unknown OS";
}

string Util::getInstallDirectory(){
	return string( INSTALL_DIR ) + "/rafkill/";
}

vector< string > Util::getFiles( string dataPath, string find ){
	struct al_ffblk info;
	vector< string > files;

	dataPath = getInstallDirectory() + dataPath;

	if ( al_findfirst( (dataPath + find).c_str(), &info, FA_ALL ) != 0 ){
		return files;
	}
	files.push_back( string( info.name ) );
	while ( al_findnext( &info ) == 0 ){
		files.push_back( dataPath + string( info.name ) );
	}
	al_findclose( &info );

	return files;
}

void Util::loadGlobals(){

	char path[ 4096 ];
	Util::getDataPath( path, "raptor.dat" );
	Util::global_data = load_datafile( path );
	
	Util::getDataPath( path, "sound.dat" );
	Util::global_snd = load_datafile( path );

	Util::getDataPath( path, "beast.fnt" );
	// Util::raptor_font = new RFont( path );

	Util::getDataPath( path, "fonts.dat" );
	Util::global_fonts = load_datafile( path );

	cout << "Loaded data" << endl;

	if ( !Util::global_data || !Util::global_snd || !Util::global_fonts ) {
		cerr << "Could not load data. Install directory is " << INSTALL_DIR << endl;
		// Util::alert( "Error with data!" );
		Bitmap::setGfxModeText();
		exit( 1 );
	}
}
	
void Util::unloadGlobals(){
	unload_datafile( Util::global_data );
	unload_datafile( Util::global_snd );
	unload_datafile( Util::global_fonts );
	// delete Util::raptor_font;
	// delete Bitmap::Screen;
}

int Util::addcol( int c1, int c2 ) {

	int r1, g1, b1;
	int r2, g2, b2;
	r1 = getr( c1 );
	g1 = getg( c1 );
	b1 = getb( c1 );

	r2 = getr( c2 );
	g2 = getg( c2 );
	b2 = getb( c2 );

	r1 += r2;
	g1 += g2;
	b1 += b2;
	if ( r1 > 255 ) r1 = 255;
	if ( g1 > 255 ) g1 = 255;
	if ( b1 > 255 ) b1 = 255;

	/* printf("C1 = %d. C2 = %d. New color = %d\n", c1, c2, makecol(r1,g1,b1) ); */

	return makecol(r1,g1,b1);

}


void Util::blend_palette( int * pal, int mp, int sc, int ec ) {

	int sc_r = getr( sc );
	int sc_g = getg( sc );
	int sc_b = getb( sc );

	int ec_r = getr( ec );
	int ec_g = getg( ec );
	int ec_b = getb( ec );

	for ( int q = 0; q < mp; q++ ) {
		float j = (float)( q ) / (float)( mp );
		int f_r = (int)( 0.5 + (float)( sc_r ) + (float)( ec_r-sc_r ) * j );
		int f_g = (int)( 0.5 + (float)( sc_g ) + (float)( ec_g-sc_g ) * j );
		int f_b = (int)( 0.5 + (float)( sc_b ) + (float)( ec_b-sc_b ) * j );
		pal[q] = makecol( f_r, f_g, f_b );
	}

}						  // end blend_palette

time_t Util::fileTime( const char * filename ){
	return ::file_time( filename );
}

int Util::pcount( char ** p, const int m ) {

	int total = 0;
	for ( int q = 0; q < m; q++ )
		if ( p[q] != NULL )
			total++;
	return total;
}


int Util::readnum( FILE * fv, int num ) {

	int final = 0;
	//char temp;
	char * buf = new char[ num ];

	fread( buf, sizeof( char ), num, fv );
	for ( int q = num-1; q >= 0; q-- )
		final = final | buf[q];
	delete[] buf;
	return final;

}


void Util::explColor() {

	e_color = new int[ MAX_E_COLOR ];
	blend_palette( e_color, 60, makecol(0,0,0), makecol(240,100,0) );
	blend_palette( e_color+60, 20, makecol(240,100,0), makecol(240,220,0) );
	blend_palette( e_color+60+20, 20, makecol(240,220,0), makecol(254,254,254) );

}

void Util::getDataPath( char * buffer, const char * file ){
	sprintf( buffer, (getInstallDirectory() + "data").c_str() );
	put_backslash( buffer );
	strcat( buffer, file );
}

/*
char * Util::data_file( const char * file_name ) {

	//char * file_place = new char[ 6 ];
	char file_place[ 30 ];
	//file_place = strdup( "data" );
	sprintf( file_place, "data" );
	put_backslash( file_place );
	char * final = append( file_place, file_name );
	//delete[] file_place;
	return final;

}
*/


void Util::MakeExplosion( ExplosionClass ** expl, int M_EX, int x, int y ) {
	/*
	int q = 0;
	while ( q < M_EX && expl[q] != NULL )
		q++;
	if ( q >= M_EX )
		return;
	*/
	double a = (double)( rnd( 45 ) + 15 ) / -10.0;
	ExplosionClass * w_expl = new ExplosionClass(x,y,0,a,rnd(6)+3);
	addExplode( expl, M_EX, w_expl );
	//expl[q] = new ExplosionClass( x, y, 0, a, rnd( 6 ) + 3 );
}


/*
void MakeSlimExplosion( ExplosionClass ** expl, int M_EX, int x, int y ){

	int q = 0;
	while ( q < M_EX && expl[q] != NULL )
		q++;
	if ( q >= M_EX )
		return;
	//double a = (double)( rnd( 45 ) + 15 ) / -10.0;
	expl[q] = new ExplosionSlim( x, y );

}
*/

/*
void draw_mask( BITMAP * dest, BITMAP * source, int _x, int _y ){
	int mask = makecol(255,0,255);
	for ( int x = 0; x < source->w; x++ )
		for ( int y = 0; y < source->h; y++ )
			if ( _getpixel16( source,x,y ) == mask )
				_putpixel16( dest, x+_x, y+_y, mask );
}
*/

void Util::play_sound( DATAFILE * snd, int m, int vol ) {
	play_sample( (SAMPLE *)snd[m].dat, (int)(vol*sound_vol), 128, 1000, false );
}

void Util::playSound( int m, int vol ){
	int max = SND_SUSTAIN + 1;
	if ( m >= 0 && m < max ){
		play_sample( (SAMPLE *)Util::global_snd[m].dat, (int)(vol*sound_vol), 128, 1000, false );
	} else {
		cerr << "Sample out of range: " << m << endl;
	}
}

void Util::play_sound( SAMPLE * snd, int vol ) {
	play_sample( snd, (int)(vol*sound_vol), 128, 1000, false );
}
