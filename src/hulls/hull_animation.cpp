#include "hull.h"
#include "hull_animation.h"
#include "defs.h"
#include "bitmap.h"
#include <vector>

HullAnimation::HullAnimation( const vector< Bitmap > & animations, const vector< Bitmap > & shadows, int _life, int _strength, int num_guns, int level, int _drawing_plane, bool _trans, ECollide * ec ):
HullObject( NULL, _life, _strength, num_guns, level, _drawing_plane, _trans, ec ) {

	pics = animations;
	pics_shadow = shadows;
	animation = 0;

	if ( pics_shadow.empty() ){
		for ( unsigned int q = 0; q < pics.size(); q++ ){
			pics_shadow.push_back( Bitmap( pics[ q ], true ) );
			int m = 22;
			pics_shadow[ q ].fill( Bitmap::makeColor( m, m, m ) );
			pics[ q ].drawMask( 0, 0, pics_shadow[ q ] );
		}
	}
}

Bitmap * HullAnimation::getShadow(){
	return &(pics_shadow[ animation ]);
}

void HullAnimation::Draw( const Bitmap & who, int x, int y ) {

	const Bitmap & bitmap = pics[ animation ];
	myBitmap = (Bitmap *)&bitmap;
	HullObject::Draw( who, x, y );
	
	if ( ++animation >= pics.size() ) animation = 0;
}


/*
void HullAnimation::Shadow( Bitmap * who, int x, int y ) {
	Bitmap = pics[ animation ];
	HullObject::Shadow( who, x, y );
}
*/


HullAnimation::~HullAnimation() {
	Shadow_Bitmap = NULL;
	myBitmap = NULL;
}
