#include "hull.h"
#include "hull_weapon_explode.h"
#include "bitmap.h"
#include "ebox.h"
#include "section.h"

Explode_WHull::Explode_WHull( int str, ECollide ** _collide_list, int _max_list ):
HullObject( NULL, 1, str, 0, 0, 20, false, NULL ),
size( 3 ),
use( 0 ) {

	collide_list = _collide_list;
	max_list = _max_list;
	collide = collide_list[use];

}

void Explode_WHull::Draw( const Bitmap & who, int x, int y ) {

	Bitmap::drawingMode( Bitmap::MODE_TRANS );

	int color = Bitmap::makeColor(150+size<255 ? 150+size : 255, size*((int)strength/2)<255?size*((int)strength/2):255, size*(int)strength/3<255?size*(int)strength/3:255 );

	who.circleFill( x, y, size, color );
	
	Bitmap::drawingMode( Bitmap::MODE_SOLID );
}


/*
void Explode_WHull::addSection( SpaceObject * who, Section * onscreen, int x, int y ){

	int y1 = y;
	int y2 = y;
	if ( collide ) {
		//y1 = collide->CY1( collide->ul_y + y );
		//y2 = collide->CY1( collide->lr_y + y );
		y1 = collide->upperY( y );
		y2 = collide->lowerY( y );
	}

onscreen->add( who, x, y1 );
for ( int q = y1+onscreen->spacer(); q <= y2; q += onscreen->spacer() )
onscreen->add( who, x, q );

}
*/

void Explode_WHull::Moved( double _dx, double _dy, double _ax, double _ay ) {

	if ( use < max_list ) {
		collide = collide_list[ use++ ];
		size += 6;
	}
	if ( use >= max_list ) life = -1;

}


Explode_WHull::~Explode_WHull() {

	collide = NULL;
	//for ( int q = 0; q < max_list; q++ )
	//	delete collide_list[q];
	//delete[] collide_list;

}
