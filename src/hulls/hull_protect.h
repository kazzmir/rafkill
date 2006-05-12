#ifndef _hull_protect_h
#define _hull_protect_h

#include "hull.h"
#include "bitmap.h"

class ProtectHull:public HullObject{
public:
	ProtectHull( int c, int level );
	virtual void Draw( const Bitmap & who, int x, int y );
	virtual bool Inside( int mx, int my, int ax, int ay );

private:

	void angular( int & a, int d );

	int angX;
	int angY;
	int dirX;
	int dirY;
	
};

#endif
