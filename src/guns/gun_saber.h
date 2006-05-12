#ifndef _gun_saber_h
#define _gun_saber_h

#include "gunobj.h"
#include "bitmap.h"
#include <vector>

#define MAX_GLOW 8

using namespace std;

class ECollide;
class SpaceObject;

class saber_point{
public:
	saber_point();
	int ang;
	double distance;
};

class WeaponSaber: public WeaponObject{
public:

	WeaponSaber( int z, int d, int smp, int al );
	virtual void MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );
	virtual void Idle(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );
	virtual void Draw( const Bitmap & less, int x, int y);
	virtual WeaponObject * copy();
	~WeaponSaber();

protected:

	int rising;
	saber_point glow[ MAX_GLOW ];
	int * shade;
	int min_color_r;
	int min_color_g;
	bool shooting;
	int fat;

};


#endif
