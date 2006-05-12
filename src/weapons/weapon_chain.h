#ifndef _weapon_chain_h
#define _weapon_chain_h

#include "weapon_damage.h"
class HullObject;

class Chain:public Damage_Weapon{
public:
	Chain(int qx, int qy, double kx, double ky, HullObject * hnew, int al );
	// virtual void MoveReal();
};

#endif

