#include <stdio.h>

#include "rfont.h"
#include "strings.h"
#include "bitmap.h"
#include "defs.h"

RGlyph::RGlyph( int w, int h, unsigned char * dat, char mc ):
_width( w ),
_height( h ) {

	letter = upcase( mc );

	data = new unsigned char[ w * h ];
	int count = 0;
	for ( int y = 0; y < h; y++ )
	for ( int x = 0; x < w; x++ ) {
		data[count] = (unsigned char)((double)dat[count]*100.0/255.0);
		count++;
	}

}


bool RGlyph::rightLetter( char x ) {
	return x==letter;
}


int RGlyph::height() {
	return _height;
}


int RGlyph::width() {
	return _width;
}


RGlyph::~RGlyph() {
	delete[] data;
}


void RGlyph::Draw( const Bitmap & work, int x, int y, int c ) {

	int o_r = Bitmap::getRed( c );
	int o_g = Bitmap::getGreen( c );
	int o_b = Bitmap::getBlue( c );

	int count = 0;
	for ( int cy = 0; cy < _height; cy++ )
	for ( int cx = 0; cx < _width; cx++ ) {

		int bash = count;
		int lx = cx;
		while ( data[bash] == data[count] && lx < _width ) {
			bash++;
			lx++;
		}

		if ( data[count] > 0 ) {
			double rd = (double)data[count] / 100.0;
			int a_r = (int)( (double)o_r*rd );
			int a_g = (int)( (double)o_g*rd );
			int a_b = (int)( (double)o_b*rd );

			int fc = Bitmap::makeColor( a_r, a_g, a_b );

			work.horizontalLine( x+cx, y+cy, x+lx-1, fc );

		}
		count = bash;
		cx = lx-1;

	}

}


RFont::RFont( char * fname ) {

	FILE * fv = fopen( fname, "rb" );

	glyphs = NULL;
	if ( fv == NULL ) {
		printf("Error reading font file %s\n", fname );
		return;
	}

	printf("Loading font %s\n", fname );

	max_glyphs = Util::readnum( fv, sizeof( int ) );

	glyphs = new RGlyph*[max_glyphs];
	for ( int q = 0; q < max_glyphs; q++ )
		glyphs[q] = NULL;
	for ( int q = 0; q < max_glyphs; q++ ) {
		int w;
		int h;
		char letter;
		w = Util::readnum( fv, sizeof( int ) );
		h = Util::readnum( fv, sizeof( int ) );
		letter = Util::readnum( fv, sizeof( char ) );
		unsigned char * d = new unsigned char[ w*h ];
		fread( d, sizeof( unsigned char ), w*h, fv );
		glyphs[q] = new RGlyph( w, h, d, letter );
		delete[] d;
	}

	fclose( fv );

}


int RFont::height() {

	if ( glyphs == NULL ) return 0;
	int average = 0;
	int count = 0;
	for ( char q = 'A'; q < 'Z'; q++ )
		for ( int z = 0; z < max_glyphs; z++ )
		if ( glyphs[z]->rightLetter(upcase(q)) ) {
			average += glyphs[z]->height();
		count++;
	}
	return average /= count;

}


void RFont::rtext( const Bitmap & work, int x, int y, int c, const char * wr ) {

	if ( glyphs == NULL ) return;

	int sx = x;
	int sy = y;

	for ( int q = 0; wr[q] != '\0'; q++ ) {
		int z = 0;
		for ( z = 0; z < max_glyphs && !glyphs[z]->rightLetter(upcase(wr[q])); z++ );
		if ( z == max_glyphs )sx += 20;
		else {
			glyphs[z]->Draw( work, sx, sy, c );
			sx += glyphs[z]->width();
		}
	}
}


RFont::~RFont() {

	if ( glyphs ) {
		for ( int q = 0; q < max_glyphs; q++ )
			if ( glyphs[q] )
				delete glyphs[q];
		delete[] glyphs;
	}

}
