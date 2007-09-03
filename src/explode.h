#ifndef _explode_h_
#define _explode_h_

class Bitmap;

extern int last_explode;

class ExplosionClass{
public:
	ExplosionClass( int cx, int cy, double walkx, double walky, int rad );

	virtual ~ExplosionClass();

	//process: moves according to dx, dy and changes radius
	virtual bool update();

	//process: draws onto Bitmap
	virtual void Draw( Bitmap * who, int offset );

	int x, y;
	double vx, vy;
	double wx, wy;
	int radius;
	int max_rad;

};

void addExplode( ExplosionClass ** explode_array, int MAX_EXPL_ARRAY, ExplosionClass * who );

#endif
