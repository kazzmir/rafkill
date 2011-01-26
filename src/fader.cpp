#include "fader.h"
#include "defs.h"
#include "allegro.h"

Fader::Fader( RLE_SPRITE * back ) {
	x = 0;
	y = 0;
	own = create_bitmap( back->w, back->h );
	first = back;
	draw_rle_sprite( own, back, 0, 0 );
}


RLE_SPRITE * Fader::blend() {

	for ( int x = 0; x < GRAPHICS_X; x++ )
		((short *)own->line[y])[x] += makecol(9,9,9);
	y++;
	if ( y >= first->h ) {
		destroy_rle_sprite( first );
		RLE_SPRITE * use = get_rle_sprite( own );
		destroy_bitmap( own );
		return use;
	}

	return first;

}


bool Fader::complete() {
	return y >= first->h;
}


Fader::~Fader() {
}
