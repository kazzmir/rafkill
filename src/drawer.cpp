#include "drawer.h"
#include "playerobj.h"
#include "bitmap.h"
#include "explode.h"
#include "timedifference.h"
#include "hulls/hull_player.h"
#include "spaceobj.h"
#include <vector>
#include <map>
#include "defs.h"
#include "trigtable.h"
#include "pck.h"
#include <iostream>
#include <string.h>

/* TODO:
 * Add weapon icons to HUD
 */

using namespace std;

#ifndef debug
#define debug cout<<"File: "<<__FILE__<< " Line:"<<__LINE__<<endl;
#endif

const int Y_BLIT_OFFSET = 500;
const int SCROLL_VIEW = 210;

const int RADAR_X = 100;
const int RADAR_Y = 80;
	
Drawer::Drawer():
land( 0 ),
warning_shade_color( 0 ),
view_port( 0 ),
level_speech( 0 ),
draw_land( true ),
drawTrans( false ){

	transBuffer = new Bitmap( Util::screen_x, Util::screen_y );

	// work = create_Bitmap( screen_x, screen_y+Y_BLIT_OFFSET );
	// Screen = new Bitmap( screen );
	work = new Bitmap( Util::screen_x, Util::screen_y+Y_BLIT_OFFSET );
	// radar = create_Bitmap( RADAR_X, RADAR_Y );
	radar = new Bitmap( RADAR_X, RADAR_Y );
	// clear_to_color( radar, makecol(10,40,10) );
	radar->fill( Bitmap::makeColor(10,40,10) );

	Util::blend_palette( warning_shade, MAX_WARNING_SHADE/2, Bitmap::makeColor(85,0,0), Bitmap::makeColor(255,0,0) );
	Util::blend_palette( warning_shade+MAX_WARNING_SHADE/2, MAX_WARNING_SHADE/2, Bitmap::makeColor(255,0,0), Bitmap::makeColor(85,0,0) );
	
	Util::blend_palette( shade_energy, MAX_ATTRIBUTE_COLOR, Bitmap::makeColor(255,0,0), Bitmap::makeColor(255,255,255) );
	Util::blend_palette( shade_shield, MAX_ATTRIBUTE_COLOR, Bitmap::makeColor(0,100,140), Bitmap::makeColor(255,255,255) );
	Util::blend_palette( shade_power, MAX_ATTRIBUTE_COLOR, Bitmap::makeColor(50,80,100), Bitmap::makeColor(90,160,200) );

	land = loadLand();
}

Bitmap * Drawer::loadLand(){

	pckLoader p;
	const char * ff = "1.pck";
	switch ( Util::rnd( 3 ) ) {
		case 0  :       ff = "1.pck";break;
		case 1  :       ff = "2.pck";break;
		case 2  :       ff = "3.pck";break;
	}

	/* TODO: fix */
	Bitmap * ld = p.load( ff );
	if ( !ld ) {
		printf("Supreme error with land Bitmap\n");
		return NULL;
	}

	land_counter = 0;
	// blit( ld, screen, 0, 0, 0, 0, GRAPHICS_X, GRAPHICS_Y );

	/*
	Bitmap * who = get_rle_sprite( ld );
	destroy_Bitmap( ld );
	*/
	// Bitmap * who = new Bitmap(10,10);

	return ld;

}

void Drawer::fadeToBlack( int num ){
	// cout << "Fade to black " << num << endl;
	if ( num < 255 ){
		setDrawTrans();
	}
	Bitmap::transBlender( 0, 0, 0, num );
}

void Drawer::drawHud( const PlayerObject * player ){

	if ( player->getLife() < 30 ) {
		// rectfill( work, view_port, 0+Y_BLIT_OFFSET, view_port+GRAPHICS_X-1, 10+Y_BLIT_OFFSET, warning_shade[warning_shade_color] );
		work->rectangleFill( view_port, Y_BLIT_OFFSET, view_port+GRAPHICS_X-1,10+Y_BLIT_OFFSET,warning_shade[warning_shade_color] );
		// rectfill( work, view_port, GRAPHICS_Y-10+Y_BLIT_OFFSET, view_port+GRAPHICS_X-1, GRAPHICS_Y-1+Y_BLIT_OFFSET, warning_shade[warning_shade_color] );
		work->rectangleFill( view_port, GRAPHICS_Y-10+Y_BLIT_OFFSET, view_port+GRAPHICS_X-1, GRAPHICS_Y-1+Y_BLIT_OFFSET, warning_shade[warning_shade_color] );
		if ( ++warning_shade_color > MAX_WARNING_SHADE ) warning_shade_color = 0;
	}

	// Show the player's score at the bottom left of the screen
	int score = player->getScore();
	char temp[ 64 ];
	sprintf( temp, "Score %d", score );
	/* TODO: fix */
	Font font = Util::getNormalFont();
	work->printf( view_port + 11, GRAPHICS_Y - font.getHeight() - 2 + Y_BLIT_OFFSET, Bitmap::makeColor(255,128,0), &font, temp );

	int level_use = ( (PlayerObject *)player )->getLevel();
	if ( level_speech < 120 ) {

		int speech[ 30 ];
		Util::blend_palette( speech, 10, Bitmap::makeColor( 255, 0, 120 ), Bitmap::makeColor(150,220,20) );
		Util::blend_palette( speech+10, 10, Bitmap::makeColor(150, 220, 20), Bitmap::makeColor(20,160,255) );
		Util::blend_palette( speech+10+10, 10, Bitmap::makeColor(20,160,255), Bitmap::makeColor(255,0,120) );

		level_speech++;
		char temp[ 64 ];
		snprintf( temp, 64, "level %d", level_use );
		int vx = 300;
		int vy = 200;
		for ( unsigned int q = 0; q < strlen( temp ); q++ ) {
			int sy = (int)(vy + Tsine( (int) (((level_speech+q*2)*12)%360) )*8);
			int sx = vx + q * 10;
			int col = 32 + ((level_speech+q*2)%20);
			col = speech[ (level_speech+q) % 30 ];
			// textprintf_ex( work, font, sx+view_port, sy+Y_BLIT_OFFSET, col, -1, "%c", temp[q] );
			work->printf( sx+view_port, sy+Y_BLIT_OFFSET, col, &font, "%c", temp[q] );
		}
	}

	// Show the player's health and shield on the sides of the screen
	PlayerHull * ph = (PlayerHull *)(player->getHull());

	showAttribute( (int)ph->getLife(), (int)ph->getMaxLife(), view_port+GRAPHICS_X-10, Y_BLIT_OFFSET, shade_energy );
	showAttribute( (int)ph->getShield(), (int)ph->getMaxShield(), view_port+1, Y_BLIT_OFFSET, shade_shield );
        showAttribute((int) player->getPowerBonus(), (int) player->getMaxPowerBonus(), view_port + GRAPHICS_X - 20, Y_BLIT_OFFSET, shade_power);

}

void Drawer::showAttribute( int amount, int MAX, int start_x, int offset, int * shade ) {
	const int start_attr = 470;
	for ( int z = 0; z < amount; z++ ) {

		int x1 = start_x;
		int x2 = start_x + 9;
		int start = start_attr * z / MAX;
		int y1 = start_attr - start + offset;
		int y2 = y1 + 1;

		int num = z * MAX_ATTRIBUTE_COLOR / MAX;
		if ( num >= MAX_ATTRIBUTE_COLOR ){
			num = MAX_ATTRIBUTE_COLOR - 1;
		}
		int color = shade[num];
		// rectfill( work, x1, y1, x2, y2, color );
		work->rectangleFill( x1, y1, x2, y2, color );

	}
}

void Drawer::drawLand( int view, int y1 ) {

	// clear( work );
	/* TODO: fix */
	/*
	draw_rle_sprite( work, land, view, y1-GRAPHICS_Y+Y_BLIT_OFFSET );
	draw_rle_sprite( work, land, view, y1+Y_BLIT_OFFSET );
	*/

	land->Blit( view, y1+Y_BLIT_OFFSET, *work );
	land->Blit( view, y1-GRAPHICS_Y+Y_BLIT_OFFSET, *work );
}
	
void Drawer::Draw( const vector< SpaceObject * > * objects, const SpaceObject * player, ExplosionClass ** expl, int MAX_EXPL ){

	TimeDifference time;

	time.startTime();

	if ( player != NULL ){
		if ( player->getX() < view_port + SCROLL_VIEW )
			view_port = player->getX() - SCROLL_VIEW;
		if ( player->getX() > view_port + GRAPHICS_X - SCROLL_VIEW )
			view_port += player->getX() - ( view_port + GRAPHICS_X - SCROLL_VIEW );
	}
		
	if ( view_port < 0 ) view_port = 0;
	if ( view_port > Util::screen_x - GRAPHICS_X ) view_port = Util::screen_x - GRAPHICS_X;

	/*
	 * Some crazy people from allegro said you should do this
	 * cuase windows directX blows and might mess up if you dont.
	 */
	// acquire_Bitmap( work );
	// work->acquire();

	/*
	time.endTime();
	time.printTime( "Drawer 1: " );
	time.startTime();
	*/

	/* Either draw the background or clear it */
	if ( draw_land ){
		drawLand( view_port, land_counter );
	} else {
		work->rectangleFill( view_port, Y_BLIT_OFFSET, view_port+GRAPHICS_X, GRAPHICS_Y+Y_BLIT_OFFSET, Bitmap::makeColor(0,0,0) );
	}
	
	/*
	time.endTime();
	time.printTime( "Drawer 2: " );
	time.startTime();
	*/

	land_counter = (land_counter+1) % GRAPHICS_Y;

	map< int, vector< const SpaceObject * > > map_draw;
	for ( vector< SpaceObject *>::const_iterator it = objects->begin(); it != objects->end(); ++it ){
		SpaceObject * m = *it;
		if ( m == 0 ) continue;
		vector< const SpaceObject * > & vec = map_draw[ (*it)->lookPlane() ];
		vec.push_back( *it );
	}

	/* add player to the vector of the plane he is in */
	if ( player != NULL ){
		vector< const SpaceObject * > & player_vec = map_draw[ player->lookPlane() ];
		player_vec.push_back( player );
	}

	for ( map< int, vector< const SpaceObject * > >::iterator it = map_draw.begin(); it != map_draw.end(); ++it ){
		vector< const SpaceObject * > & vec = (*it).second;
		int plane = (*it).first;

		for ( vector< const SpaceObject * >::const_iterator ship = vec.begin(); ship != vec.end(); ++ship ){
			const SpaceObject * s = *ship;

			s->Shadow( *work, plane, Y_BLIT_OFFSET );
			s->Draw( *work, expl, MAX_EXPL, plane, Y_BLIT_OFFSET );
			s->Radar( *radar );
		}
	}
	
	/*
	time.endTime();
	time.printTime( "Drawer 3: " );
	time.startTime();
	*/

	/* Draw all the explosions. */
	for ( int q = 0; q < MAX_EXPL; q++ ) {
		if ( expl[q] != NULL )
			expl[q]->Draw( work, Y_BLIT_OFFSET );
	}

	/*
	if ( time(NULL) != timex ) {
		fsec_keep = fsec;
		fsec = 0;
		timex = time(NULL);
	}
	*/

	if ( player != NULL ){
		drawHud( (const PlayerObject *)player );
	}

	/*
	if ( finished ) {

	}
	*/

	/* Draw all the important things */

	radar->drawTrans( view_port, Y_BLIT_OFFSET, *work );
	radar->fill( Bitmap::makeColor(10,60,30) );
	radar->rectangle( 0, 0, RADAR_X-1, RADAR_Y-1, Bitmap::makeColor(200,200,200) ); 

	if ( drawTrans ){
		/* Get the current viewport */
		Bitmap trans( *work, view_port, Y_BLIT_OFFSET, Util::screen_x, Util::screen_y );
		// trans.drawTrans( 0, 0, *Bitmap::Screen );
		/* Draw it translucently onto a buffer */
		trans.drawTrans( 0, 0, *transBuffer );

		/* Blit the buffer to the screen */
		// transBuffer->Blit( 0, 0, 0, 0, *Bitmap::Screen );
		transBuffer->BlitToScreen();
	} else {
		work->BlitToScreen( view_port, Y_BLIT_OFFSET, 0, 0 );
	}

	/*
	time.endTime();
	time.printTime( "Drawer 4: " );
	cout << endl;
	*/
}

Drawer::~Drawer(){

	delete work;
	delete radar;
	delete transBuffer;
	// destroy_Bitmap( work );

}
