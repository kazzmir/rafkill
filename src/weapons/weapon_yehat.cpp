#include "weaponobj.h"
#include "weapon_yehat.h"
#include "hull.h"
#include "trigtable.h"

Yehat_Weapon::Yehat_Weapon( int qx, int qy, double kx, double ky, HullObject * hnew, int al ):
WeaponNode(qx,qy,kx,ky,hnew,al) {
}


void Yehat_Weapon::Collided( SpaceObject * who, ExplosionClass ** explr, int M_EX ) {

	double d = dist( getX(), getY(), who->getX(), who->getY() );
	int ang = gang( getX(), getY(), who->getX(), who->getY() );
	who->SetCoordXY( (int)(who->getX() + Tcos(ang)*d/1.3), (int)(who->getY() + Tsine(ang)*d/1.3) );
	//who->SetCoordXY( who->actualx, who->actualy + 10 );

	if ( hull ) hull->Collided();
	this->addCollide( who );
}
