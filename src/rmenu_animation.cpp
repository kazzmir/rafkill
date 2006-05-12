#include "rmenu.h"
#include "rmenu_animation.h"
#include "animation.h"
#include "rfield.h"
#include "bitmap.h"

RMenuAnimation::RMenuAnimation( const Bitmap & intr, int x, int y, int height, int c1, int c2, int c3, Animation * ani ):
RMenu( intr, x, y, height, c1, c2, c3 ) {
	show_case = ani;
}


void RMenuAnimation::Draw( const Bitmap & work, int x, int * yval, int * yshade, int min, int max ) {

	show_case->Next( work );

	RMenu::Draw( work, x, yval, yshade, min, max );

	/*
	RField * junk = head->Next();
	for ( int q = min; q <= max; q++ ) {
		while( junk->Place() != q ) junk=junk->Next();
		if ( junk->Title() )
			junk->Draw( work, x, yval[q-min], t_color );
		else
			junk->Draw( work, x, yval[q-min], shade_opt_color[yshade[junk->Place()]] );
	}
	*/

}


RMenuAnimation::~RMenuAnimation() {
}
