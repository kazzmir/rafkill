#ifndef _hull_weapon_follow_h_
#define _hull_weapon_follow_h_

#include "hull_weapon.h"
#include "bitmap.h"

/*
 * Follow
 *
 * a ball of lightning
 *
 */

class Follow_WHull:public HullWeapon{
public:

	Follow_WHull( int _life );
	virtual void Draw( const Bitmap & who, int x, int y );

};

#endif
