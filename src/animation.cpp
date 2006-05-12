#include "animation.h"
#include <vector>

Animation::Animation( int x, int y ):
posx( x ),
posy( y ) {
	current = pics.begin();
}


void Animation::add( const Bitmap & who ){
	pics.push_back( who );
	current = pics.begin();
}


const Bitmap Animation::show() const{
	return (*current);
}


void Animation::clear() {

	pics.clear();
	current = pics.begin();

	/*
	if ( sent ) destroy_bitmap( sent );
	sent = NULL;
	return;

	if ( pics.empty() ) return;

	for ( current = pics.begin(); current != pics.end(); ) {

		BITMAP * temp = *current;
		current = pics.erase( current );
		destroy_bitmap( temp );

	}
	current = pics.begin();
	*/

}


void Animation::Next( const Bitmap & work ){

	if ( ! pics.empty() ){

		const Bitmap & frame = *current;
		frame.draw( posx, posy, work );

		current++;
		if ( current == pics.end() ) current = pics.begin();
	}

}


void Animation::changePos( const int x, const int y ) {
	posx = x;
	posy = y;
}


Animation::~Animation() {

	/*
	if ( sent )
		destroy_bitmap( sent );
	return;
	for ( current = pics.begin(); current != pics.end(); ) {

		BITMAP * temp = *current;
		current = pics.erase( current );
		destroy_bitmap( temp );

	}
	*/

}
