#include "strings.h"
#include "defs.h"
#include "bitmap.h"
#include "hull.h"
#include "hull_num_show.h"

HullShow::HullShow( int sp ):
HullObject( NULL, 19, 0, 0, 0, MAX_PLANE, true, NULL ),
spc( sp ),
col( 0 ) {

	// shade = new int[ 20 ];
	if ( spc > 800 ) {

		Util::blend_palette( shade, 5, Bitmap::makeColor( 242,2,2 ), Bitmap::makeColor(49,244,19) );
		Util::blend_palette( shade+4, 5, Bitmap::makeColor(49,244,19), Bitmap::makeColor(234,242,4) );
		Util::blend_palette( shade+4+4,5, Bitmap::makeColor(234,242,4), Bitmap::makeColor(255,139,7) );
		Util::blend_palette( shade+4+4+4, 8, Bitmap::makeColor(255,139,7),Bitmap::makeColor(242,2,2) );

	} else {
		Util::blend_palette( shade, 20, Bitmap::makeColor(255,255,255), Bitmap::makeColor(30,30,30) );
	}

	char fx[ 128 ];
	sprintf( fx, "%d", spc );
	Font font = Util::getNormalFont();
	mock = new Bitmap( font.textLength( fx ), font.getHeight() + 1 );
	mock->fill( Bitmap::makeColor(255,0,255) );
}

void HullShow::Draw( const Bitmap & who, int x, int y ) {

	char fx[ 128 ];
	sprintf( fx, "%d", spc );

	Font font = Util::getNormalFont();

	int len = font.textLength( fx );

	mock->printf( 0, 0, shade[col], &font, "%d", spc );
	mock->drawStretched( x, y - col, len + col, font.getHeight() + col + 1, who );

	takeDamage( 1 );

	col++;
	if ( col >= MAX_SHADE ) col = MAX_SHADE - 1;
}

HullShow::~HullShow() {
	delete mock;
}
