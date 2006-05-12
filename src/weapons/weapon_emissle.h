#ifndef _weapon_enemy_missle_h
#define _weapon_enemy_missle_h

#include "weaponobj.h"

class normalMissle: public WeaponNode{
public:

	normalMissle(int qx, int qy, double kx, double ky, int al );
	virtual void MoveReal();

};

#endif
