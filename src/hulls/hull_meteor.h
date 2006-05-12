#ifndef _hull_meteor_h
#define _hull_meteor_h

#include "hull.h"
#include "bitmap.h"

class SpaceObject;
class ECollide;

class MeteorHull:public HullObject{
public:
	MeteorHull( int level, int lf, ECollide * eb );
	virtual bool Inside( int mx, int my, int ax, int ay );
	virtual bool Collide( int ax, int ay, SpaceObject * check );
	virtual void Draw( const Bitmap & who, int x, int y );

	int frame;
};

#endif
