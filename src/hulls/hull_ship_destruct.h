#ifndef _hull_ship8_h
#define _hull_ship8_h

#include "hull.h"

class SpaceObject;
class ECollide;

class Destruct:public HullObject{
public:
	Destruct( int life, int level, ECollide * eb );
};

#endif
