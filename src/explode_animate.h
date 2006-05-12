#ifndef _explode_animate_h_
#define _explode_animate_h_

#include "explode.h"
class Bitmap;

class ExplosionAnimate: public ExplosionClass{
public:
	ExplosionAnimate( int cx, int cy, double dx, double dy, int _first_pic, int _last_pic );

	virtual bool update();
	virtual void Draw( Bitmap * who, int offset );

protected:
	int first_pic;
	int last_pic;

};

#endif
