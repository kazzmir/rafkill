#ifndef _hull_weapon_explode_h
#define _hull_weapon_explode_h

#include "hull.h"
#include "bitmap.h"

class ECollide;
class Section;

class Explode_WHull:public HullObject{
public:

	Explode_WHull( int str, ECollide ** _collide_list, int _max_list );
	virtual void Draw( const Bitmap & who, int x, int y );
	virtual void Moved( double _dx, double _dy, double _ax, double _ay );
	//virtual void addSection( SpaceObject * who, Section * onscreen, int x, int y );

	virtual ~Explode_WHull();

protected:

	int size;
	int use;
	ECollide ** collide_list;
	int max_list;
	
};

#endif
