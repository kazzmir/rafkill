#include "weaponobj.h"
#include "weapon_angle.h"
#include "hull.h"
#include "trigtable.h"

Angle::Angle( int qx, int qy, double kx, double ky, double _speed, HullObject * hnew, int al, int _ang ):
WeaponNode(qx,qy,kx,ky,hnew,al),
ang_vel( (_ang+90)%360 ),
ang_accel( (_ang+180) % 360 ),
speed( _speed ){

	/*
	setDX( Tcos(ang_vel) * speed );
	setDY( Tsine(ang_vel) * speed );
	*/

	/*
	center_x = getX();
	center_y = getY();
	*/
}
	
void Angle::MoveMe( vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight, Section * onscreen ){

	/*
	center_x += getDX();
	center_y += getDY();

	setX( center_x );
	setY( center_y );

	MoveReal();

	double fx, fy;

	fx = center_x + Tcos(ang_vel) * speed;
	fy = center_y + Tsine(ang_vel) * speed;
	ang_vel = (ang_vel + 20 ) % 360;

	setX( fx );
	setY( fy );
	*/
	
	setOffsetX( (int)( Tcos(ang_vel) * speed ) );
	setOffsetY( (int)( Tsine(ang_vel) * speed ) );
	ang_vel = (ang_vel + 20 ) % 360;

	MoveReal();

	/*
	fx = getDX();
	fy = getDY();

	int ix = (int)fx;
	int iy = (int)fy;
	int sang = gang( 0, 0, ix, iy );
	ang_vel = (sang+5) % 360;

	fx = Tcos( ang_vel ) * speed;
	fy = Tsine( ang_vel ) * speed;
	setDX( fx );
	setDY( fy );
	// ang = (ang+5)%360;
	*/
	
	if ( hull ) hull->Moved( this->getDX(), this->getDY(), this->getAccelX(), this->getAccelY() );

}

/*
void Angle::MoveReal() {

	//virtualx += dx + tcos[ ang ];
	//virtualy += dy + tsine[ ang ];
	//actualx = (int)virtualx;
	//actualy = (int)virtualy;

	/ *
	virtualx += dx;
	virtualy += dy;
	actualx = (int)(virtualx + tcos[ang] * 25 );
	actualy = (int)(virtualy + tsine[ang] * 25 );
	* /

	ang = ( ang + 2 ) % 360;

}
*/
