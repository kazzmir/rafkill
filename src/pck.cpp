#include "pck.h"
#include "strings.h"
#include "defs.h"
#include "bitmap.h"

#include <stdio.h>
#include <stdlib.h>

/* PCK:
 * File format invented by me to store the background in a conveinent way.
 * Initially, the background file contains numbers ranging from 0-127. Each number
 * represents an index into an array of colors which are made by blend_palette.
 * These numbers can be packed together becuase many numbers occur repeatedly next
 * to each other. If this is the case then the number of repeated numbers is stored
 * followed by the raw index. If a sample row of numbers is:
 * 9 9 120 85 85 85 17 1
 * Then the final packed form would be:
 * 2 9 248 3 85 145 129
 * If a number is larger than 128, subtract 128 to get its index value. Otherwise
 * the first number is the count, and the second is the index. Simple enough and packs
 * the file about 1/3. 
 */

/* pckLoader:
 * Constructor. Does nothing
 */
pckLoader::pckLoader(){}

Bitmap * pckLoader::load( const char * sf ) {

	//clear( screen );
	int g1, g2;
	get_colors( g1, g2 );
	// int * shade = new int[ 128 ];
	int shade[ 128 ];
	Util::blend_palette( shade, 128, g1, g2 );

	char fileName[ 4096 ];
	// char * file_name = Util::data_file( sf );
	Util::getDataPath( fileName, sf );

	Bitmap * ret = load_pck( fileName, shade, 128 );

	// free( file_name );
	// delete[] shade;
	return ret;

}


void pckLoader::set( Bitmap * fat, int & x, int & y, int col) {
	if ( x >= 0 && x < 640 && y >= 0 && y < 480 )
	{
		// _putpixel16( fat, x, y, col );
		fat->putPixel( x, y, col );
		#ifdef PANDORA
		if (x<160)
			fat->putPixel( x+640, y, col );
		#endif
	}
	x++;
	if ( x >= 640 ) {
		y++;
		x = 0;
	}
}


Bitmap * pckLoader::load_pck( char * sf, int * shade, int max ) {

	// Bitmap * choice = create_bitmap( GRAPHICS_X, GRAPHICS_Y );
	Bitmap * choice = new Bitmap( GRAPHICS_X, GRAPHICS_Y );
	if ( !choice ) {
		printf("Supreme error with backgruond!\n");
		return NULL;
	}
	// clear( choice );
	choice->clear();

	// textprintf_ex(screen,font,100,100,makecol(255,255,255), -1, "Loading background..");

	int x = 0;
	int y = 0;
	FILE * fv = fopen( sf, "rb" );
	if ( !fv ) {
		printf("File %s doesnt exist!\n", sf );
		return NULL;
	}

	while ( y != GRAPHICS_Y ) {
		unsigned char rd;

		fread( &rd, sizeof( unsigned char ), 1, fv );
		if ( rd > 127 ) {
			set( choice, x, y, shade[rd-128] );
		}
		else {
			unsigned char num;
			fread( &num, sizeof( unsigned char ), 1, fv );
			for ( int q = 0; q < rd; q++ )
				set( choice, x, y, shade[num] );
		}

	}

	fclose( fv );
	return choice;
}


int pckLoader::getnum( char *& buf ) {
	int r = str2int( buf );
	while ( *buf != '\0' ) buf++;
	while ( *buf == '\0' ) buf++;
	int g = str2int( buf );
	while ( *buf != '\0' ) buf++;
	while ( *buf == '\0' ) buf++;
	int b = str2int( buf );
	while ( *buf != '\0' ) buf++;
	while ( *buf == '\0' ) buf++;
	return Bitmap::makeColor( r, g, b );
}


int pckLoader::filesize( FILE * fv ) {
	/*
	char dumb;
	while ( !feof( fv ) ) fread( &dumb, sizeof( char ), 1, fv );
	*/
	fseek( fv, 0, SEEK_END );
	int size = ftell( fv );
	rewind( fv );
	return size;
}


void pckLoader::get_colors( int & c1, int & c2 ) {

	// char * file_name_col = Util::data_file("table.col");
	char fileNameCol[ 4096 ];
	Util::getDataPath( fileNameCol, "table.col" );

	FILE * fv = fopen( fileNameCol, "rb" );

	if ( !fv ) {

		fv = fopen( fileNameCol, "wb" );
		char * buf;
		buf = "4\n";
		fwrite( buf, sizeof( char ), length( buf ), fv );
		buf = "90 15 70\n";
		fwrite( buf, sizeof( char ), length( buf ), fv );
		buf = "3 78 3\n";
		fwrite( buf, sizeof( char ), length( buf ), fv );
		buf = "53 24 40\n";
		fwrite( buf, sizeof( char ), length( buf ), fv );
		buf = "25 4 98";
		fwrite( buf, sizeof( char ), length( buf ), fv );
		fclose( fv );
		fv = fopen( "table.col", "rb" );
		if ( !fv ){
			return;
		}

	}
	// free( file_name_col );
	int size = filesize( fv );

	// char * buf = new char[ size+1 ];
	char storage[ size+1 ];
	char * buf = storage;
	fread( buf, sizeof( char ), size, fv );
	buf[size] = '\0';

	for ( int q = 0; q < size+1; q++ ) {
		if ( buf[q] == ' ' ) buf[q] = '\0';
		if ( buf[q] == '\n' ) buf[q] = '\0';
	}

	int str = str2int( buf );
	while ( *buf != '\0' ) buf++;
	while ( *buf == '\0' ) buf++;

	int colors[ str ];
	for ( int q = 0; q < str; q++ )
		colors[q] = getnum( buf );

	int choose[ str ];
	for ( int q = 0; q < str; q++ ) choose[q] = 0;

	int g = Util::rnd( str );
	while ( choose[g] ) g = Util::rnd( str );
	c1 = colors[g];
	choose[g] = 1;
	while ( choose[g] ) g = Util::rnd( str );
	c2 = colors[g];

	//delete[] buf;
	fclose( fv );

}
