#ifndef _hull_weapon_cork_h
#define _hull_weapon_cork_h

#include "hull_weapon.h"
#include "spaceobj.h"
#include <deque>
#include "bitmap.h"

using namespace std;

class RGBHandle;

class Cork_WHull:public HullWeapon{
public:

	Cork_WHull( int str );
	virtual void Draw( const Bitmap & who, int x, int y );
	virtual bool Collide( int mx, int my, SpaceObject * check );
	virtual ~Cork_WHull();

protected:
	int * shade[ 2 ];
	int ang;
	deque< int > list;

};

#endif
