#ifndef _hull_shield_h
#define _hull_shield_h

#include "hull.h"
#include "bitmap.h"

class ECollide;

class ShieldHull:public HullObject{
public:
	ShieldHull( Bitmap * me, double life, int level, ECollide * eb );
	virtual void Draw( const Bitmap & who, int x, int y );
	virtual double Damage( double much );
	#define shield_max 3

	HullObject * pr[ shield_max ];

	virtual ~ShieldHull();

};

#endif
