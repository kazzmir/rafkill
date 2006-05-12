#ifndef _move_find_h
#define _move_find_h

#include "move.h"
#include <deque>

using namespace std;

struct XYPoint{
	XYPoint( int _x, int _y ): x( _x ), y( _y ){}
	int x, y;
};

class MoveFind: public Move{
public:

	MoveFind( double _dx, double _dy );
	virtual void action( const vector< SpaceObject * > * fight, int x, int y, double & sdx, double & sdy );
	virtual ~MoveFind();

protected:

	deque< XYPoint * > points;	
	
};

#endif
