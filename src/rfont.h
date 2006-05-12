#ifndef _raptor_font_h
#define _raptor_font_h

#include "bitmap.h"

class RGlyph{
public:
	RGlyph( int w, int h, unsigned char * dat, char mc );

	void Draw( const Bitmap & work, int x, int y, int c );
	bool rightLetter( char x );
	int height();
	int width();

	~RGlyph();

protected:
	unsigned char * data;
	int _width;
	int _height;
	char letter;

};

class RFont{
public:
	RFont( char * fname );

	void rtext( const Bitmap & work, int x, int y, int c, const char * wr );
	int height();

	~RFont();

private:
	RGlyph ** glyphs;
	int max_glyphs;
	
};

#endif
