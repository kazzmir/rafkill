#include "defs.h"
#include "bitmap.h"
#include "raptor.h"

#include "hull_weapon.h"
#include "hull_weapon_bomb.h"

/* This class isnt used as far as I know */
Bomb_WHull::Bomb_WHull():
HullWeapon( WEAPON_BOMB_1, 1, 20 ),
frame( 0 ){}

void Bomb_WHull::Draw( const Bitmap & who, int x, int y ) {

	if ( ++frame > 100 ) frame = 0;
	if ( frame % 1 == 0 )
		if ( ++drawNum > WEAPON_BOMB_7 ) drawNum = WEAPON_BOMB_1;

	//int mx = ((BITMAP *)dat[ drawNum ].dat)->w/2;
	//int my = ((BITMAP *)dat[ drawNum ].dat)->h/2;

	//draw_sprite( who, (BITMAP *)dat[ drawNum ].dat, x-mx, y-my );

	//HullObject::Draw( who, dat, x, y );

	/* TODO: fix, i think o_O
	if ( ++frame > WEAPON_BOMB_7 ) frame = WEAPON_BOMB_1;

	drawNum = frame;
	int mx = ((BITMAP *)dat[ drawNum ].dat)->w/2;
	int my = ((BITMAP *)dat[ drawNum ].dat)->h/2;
	draw_sprite( who, (BITMAP *)dat[ drawNum ].dat, x-mx, y-my );

	*/

}
