#ifndef _hull_num_show_h
#define _hull_num_show_h

#include "hull.h"
#include "bitmap.h"

class HullShow: public HullObject{
public:

	HullShow( int stupid_crap );

	virtual void Draw( const Bitmap & who, int x, int y );
	virtual ~HullShow();

private:
	
	static const int MAX_SHADE = 20;

	int spc;
	int col;
	int shade[ MAX_SHADE ];
	Bitmap * mock;

};

#endif
