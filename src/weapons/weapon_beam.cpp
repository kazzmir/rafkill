#include "hull.h"
#include "weapon_damage.h"
#include "weapon_beam.h"
#include "explode.h"
#include "ebox.h"
#include "defs.h"

Beam::Beam(int qx, int qy, double kx, double ky, int dam, HullObject * hnew, int al ):
Damage_Weapon(qx,qy,kx,ky,dam,hnew,al) {
}


bool Beam::Damage( double much ) {
	return false;
}

void Beam::Collided( SpaceObject * who, ExplosionClass ** explr, int M_EX ) {

	int mw = getMaxX() / 2;
	int mh = getMaxY() / 2;
	
	int mx1 = getX() - mw;
	int mx2 = getX() + mw;
	int my1 = getY() - mh;
	int my2 = getY() + mh;

	int aw = who->getMaxX() / 2;
	int ah = who->getMaxY() / 2;

	int ax1 = who->getX() - aw;;
	int ay1 = who->getY() - ah;
	int ax2 = who->getX() + aw;
	int ay2 = who->getY() + ah;

	int x1 = ax1 > mx1 ? ax1 : mx1;
	int x2 = mx2 < ax2 ? mx2 : ax2;
	int y1 = ay1 > my1 ? ay1 : my1;
	int y2 = ay2 < ay2 ? my2 : ay2;

	for ( int x = x1; x < x2; x += Util::rnd(5)+7 )
		for ( int y = y1; y < y2; y += Util::rnd(5)+7 )
			addExplode( explr, M_EX, new ExplosionClass(x,y,0,-20,Util::rnd(6) + 3 ) );


	// this->addCollide( who );
}
