#ifndef _pck_loader_h
#define _pck_loader_h

#include "defs.h"
#include <stdio.h>

class Bitmap;

class pckLoader{
public:
	pckLoader();
	Bitmap * load( const char * sf );

private:
	void set( Bitmap * fat, int & x, int & y, int col);
	Bitmap * load_pck( char * sf, int * shade, int max );
	int getnum( char *& buf );
	int filesize( FILE * fv );
	void get_colors( int & c1, int & c2 );

};

#endif
