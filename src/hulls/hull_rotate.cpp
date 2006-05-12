#include "trigtable.h"
#include "defs.h"
#include "hull_rotate.h"

RotateHull::RotateHull( int _color, int mY, int mX, int sf, int * _shade ):
HullObject( NULL, 100, 0, 1, 1, 10, false, NULL ) {

	color = _color;

	maxX = mX;
	maxY = mY;

	sd = sf;

	angX = Util::rnd(360);
	angY = Util::rnd(360);

	dX = (Util::rnd( 8 ) + sd) * (Util::rnd( 2 ) * 2 - 1 );
	dY = (Util::rnd( 8 ) + sd) * (Util::rnd( 2 ) * 2 - 1 );

	//dX = rnd(20) - 10;
	//dY = rnd(20) - 10;
	dwX = dX;
	dwY = dY;
	ox = angX;
	oy = angY;

	ox2 = angX;
	oy2 = angY;
	shade = _shade;
}


void RotateHull::Draw( const Bitmap & who, int x, int y ) {

	/*
	x += maxX / 2;
	y += maxY / 2;
	*/

	ox2 = ox;
	oy2 = oy;
	ox = angX;
	oy = angY;
	angX += dX;
	angY += dY;
	while ( angX >= 360 ) angX -= 360;
	while ( angX < 0 ) angX += 360;
	while ( angY >= 360 ) angY -= 360;
	while ( angY < 0 ) angY += 360;
	int zz = (Util::rnd( 2 ) * 2) - 1;
	if ( Util::rnd(15) == Util::rnd(15) )
		dwX = (Util::rnd(8)+sd )*zz;
	zz = (Util::rnd(2)*2)-1;
	if ( Util::rnd(15) == Util::rnd(15) )
		dwY = (Util::rnd(8)+sd )*zz;
	if ( dX < dwX ) dX++;
	if ( dX > dwX ) dX--;
	if ( dY < dwY ) dY++;
	if ( dY > dwY ) dY--;
	int nx = (int)(x+Tcos(angX)*maxX/2);
	int ny = (int)(y+Tsine(angY)*maxY/2);
	int lx = (int)(x+Tcos(ox)*maxX/2);
	int ly = (int)(y+Tsine(oy)*maxY/2);
	// line( who, lx, ly, nx, ny, shade[color] );
	who.line( lx, ly, nx, ny, shade[color] );
	nx = (int)(x+Tcos(ox2)*maxX/2);
	ny = (int)(y+Tsine(oy2)*maxY/2);
	who.line( lx, ly, nx, ny, shade[color] );

}
