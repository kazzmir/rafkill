#include "defs.h"
#include "spaceobj.h"
#include "trigtable.h"
#include "raptor.h"

#include "hull.h"
#include "hull_ship_destruct.h"
#include "guns/gun_destruct.h"
#include "ebox.h"

Destruct::Destruct( int life, int level, ECollide * eb ):
HullObject( NULL, life, SHIP_DAMAGE, 2, level, 10, false, eb ) {
	guns[1] = new GunDestruct(1,TEAM_ENEMY);
}
