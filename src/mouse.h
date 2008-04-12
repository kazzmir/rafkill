#ifndef _rafkill_mouse_h
#define _rafkill_mouse_h

namespace mouse{

	void get_mickeys( int * x, int * y );

	bool leftClick();
	bool rightClick();

	double getSensitivity();
	void setSensitivity( int x );
}

#endif
