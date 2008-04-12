#include <allegro.h>
#include "mouse.h"

void mouse::get_mickeys( int * x, int * y ){
	::get_mouse_mickeys( x, y );
}
	
bool mouse::leftClick(){
	return mouse_b & 1;
}

bool mouse::rightClick(){
	return mouse_b & 2;
}
