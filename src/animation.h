#ifndef _animation_h_
#define _animation_h_

#include <vector>
#include "bitmap.h"

using namespace std;

class Animation{
public:

	Animation( int x, int y );

	virtual void add( const Bitmap & add );
	virtual void Next( const Bitmap & work );
	virtual void changePos( const int x, const int y );
	virtual void clear();
	virtual const Bitmap show() const;

	virtual ~Animation();
	

protected:

	vector< Bitmap > pics;
	vector< Bitmap >::const_iterator current;

	// Bitmap sent;

	int posx, posy;
};

#endif
