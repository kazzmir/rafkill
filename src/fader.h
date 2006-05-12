#ifndef _background_fader_h
#define _background_fader_h

#include "allegro.h"

class Fader{
public:

	Fader( RLE_SPRITE * back );

	bool complete();

	RLE_SPRITE * blend();
	
	~Fader();

private:

	BITMAP * own;
	RLE_SPRITE * first;
	int x, y;

};

#endif
