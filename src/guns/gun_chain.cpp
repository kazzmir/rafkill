#include "gunobj.h"
#include "defs.h"
#include "gun_chain.h"
#include "weapons/weapon_damage.h"
#include "hulls/hull_weapon_chain.h"
#include "trigtable.h"
#include "raptor.h"
#include "ebox.h"
#include "bitmap.h"

#define chain_length 145

WeaponChainGun::WeaponChainGun( int z, int d, const char * name, int wor, int smp, int al, ECollide * eb ):
WeaponObject( d, name, wor, al, z, 0 ) {

	lx = -1;
	ly = -1;
	fx = -1;
	fy = -1;
	dx = 0;
	dy = 0;
	d_length = 0;

	chain_collide = eb;

	draw_number = 0;

}


WeaponChainGun::~WeaponChainGun() {
	if ( chain_collide != NULL )
		delete chain_collide;
}


void WeaponChainGun::Idle(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight) {
	lx = -1;
	dx = 0;
	dy = 0;
	draw_number = 0;
}


void WeaponChainGun::MakeShot(int x, int y, vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight ) {

	if ( lx == -1 ) {
		lx = x+3;
		ly = y+3;
		fx = x+3;
		fy = y+3;
	}
	
	draw_number = (draw_number + 1 ) % ( IRON_012 - IRON_000 + 1 );
	Bitmap * pic = new Bitmap( Util::getDataSprite( IRON_000 + draw_number ) );

	int mx = pic->getWidth() / 2;
	int my = pic->getHeight() / 2;

	shot_counter = 0;

	ox = lx;
	oy = ly;

	fx += dx;
	fy += dy;
	lx = (int)fx;
	ly = (int)fy;
	int d = (int) dist( x, y, lx, ly );
	if ( d < 2 ) return;
	int ang = getAngle( lx, ly, x, y );
	if ( d > chain_length ) {

		if ( d-chain_length > d_length ) d_length = d-chain_length;

		dx += Tcos(ang)*d_length/2;
		dy += Tsine(ang)*d_length/2;
		fx = x+Tcos((ang+180)%360)*chain_length;
		fy = y+Tsine((ang+180)%360)*chain_length;
		lx = (int)fx;
		ly = (int)fy;
	} else d_length = 0;

	dx += Tcos(ang)*2;
	dy += Tsine(ang)*2;

	/*
	#define sma 0.1
	if ( dx > sma ) dx -= sma;
	else if ( dx < -sma ) dx += sma;
	else dx = 0;

	if ( dy > sma ) dy -= sma;
	else if ( dy < -sma ) dy += sma;
	else dy = 0;
	*/

	int fin = (int) tsqrt( dx*dx + dy*dy );

	double zd = zdist( lx, ly, ox, oy );
	double gx, gy;
	int zang = getAngle(ox,oy,lx,ly);
	

	#define CHAIN_MAX 6
	for ( int q = 0; q < zd/CHAIN_MAX; q++ ) {

		gx = ox+Tcos(zang)*zd*(double)q/(zd/CHAIN_MAX);
		gy = oy+Tsine(zang)*zd*(double)q/(zd/CHAIN_MAX);

		switch( strength ) {

			case 0  :       Ammo->push_back(new Damage_Weapon((int)gx-mx,(int)gy-my,0,0,1,new Chain_WHull(NULL,strength,fin,ang,d,chain_collide->copy()), alignment ));break;

			//case 1  :       Ammo->push_back(new FireChain(lx,ly,0,0,new Chain_WHull(NULL,strength,fin,ang,d,chain_collide->copy()), alignment ));break;

		}				  //switch

	}

	/*
	BITMAP ** pics = new BITMAP*[ IRON_012 - IRON_000 + 1 ];
	for ( int q = 0; q < IRON_012 - IRON_000 +1; q++ )
		pics[q] = (BITMAP *)global_data[ IRON_000 + q ].dat;
	*/

	switch( strength ) {
		case 0  :       Ammo->push_back(new Damage_Weapon(lx,ly,0,0,1,new Chain_WHull(pic,strength,fin,ang,d,chain_collide->copy()), alignment ));break;

		//case 1  :       Ammo->push_back(new FireChain(lx,ly,0,0,new Chain_WHull(pic,strength,fin,ang,d,chain_collide->copy()), alignment ));break;
	}					  //switch

}


WeaponObject * WeaponChainGun::copy() {
	return new WeaponChainGun( strength, dir, this->GetName(), worth, smp, alignment, chain_collide->copy() );
}
