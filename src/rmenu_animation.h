#ifndef _rmenu_animation_h_
#define _rmenu_animation_h_

#include "rmenu.h"

class Animation;
class Bitmap;

class RMenuAnimation:public RMenu{
public:

	RMenuAnimation( const Bitmap & intr, int x, int y, int height, int c1, int c2, int c3, Animation * ani );

	virtual ~RMenuAnimation();

protected:

	virtual void Draw( const Bitmap & work, int x, int * yval, int * yshade, int min, int max );

	Animation * show_case;

};

#endif
