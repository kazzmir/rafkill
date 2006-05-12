#ifndef _booster_h
#define _booster_h

#include "bitmap.h"

class PixelList{
public:

	PixelList( int ax, int ay, int l, PixelList * nx );

	int Update();
	void Draw( const Bitmap & work, int * shade, int offset )const;

	int x, y;
	int life;
	PixelList * next;
};

class Booster{
public:

	Booster();

	void add( int x, int y );
	void Draw( const Bitmap & work, int offset )const;

	void Update();

	~Booster();

	PixelList * head;
	int * shade;

};

#endif
