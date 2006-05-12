#ifndef _hull_rotate_h
#define _hull_rotate_h

#include "hull.h"
#include "bitmap.h"

class RotateHull:public HullObject{
public:
	RotateHull( int _color, int mX, int mY, int sf, int * _shade );

	virtual void Draw( const Bitmap & who, int x, int y );

protected:
	
	int angX;
	int angY;
	int dX;
	int dY;
	int dwX;
	int dwY;

	int sd;

	int ox, oy;
	int ox2, oy2;

	int maxX, maxY;
	int * shade;
};

#endif
