#include "menu.h"
#include "spaceobj.h"
// #include "game.h"
#include "drawer.h"
#include "logic.h"
#include "level.h"
#include "trigtable.h"
#include "bitmap.h"
#include "keyboard.h"
#include "strings.h"
#include <string.h>
#include <iostream>
#include "loadsave.h"
#include "defs.h"
#include "ebox.h"
#include "raptor.h"
#include "sound.h"
#include "rmenu.h"
#include "hull.h"
#include "wormhole.h"
#include "explode.h"
#include "music.h"
#include "loading_screen.h"

#include "hulls/hull_player.h"
#include "playerobj.h"
#include "guns/gun_machine.h"

#ifndef debug
#define debug cout << "File: " << __FILE__ << " Line: " << __LINE__ << endl;
#endif

/* easier as a #define because Allegro isnt initialized till later */
#define RAPTOR_TITLE_COLOR (Bitmap::makeColor(244,228,7))

static const int NO_SOUND = -1;
static const int INIT_CONTINUE = 0;
static const int INIT_PLAY = 1;
static const int INIT_OPT = 2;
static const int INIT_QUIT = 3;
static const int INIT_CREDITS = 4;
static const int INIT_BACK = 6;
static const int INIT_SAVE = 7;
static const int INIT_LOAD = 5000;
static const int INC_RATE = 10;
static const int DEC_RATE = 11;
static const int INIT_HELP = 12;
static const int INIT_SCREEN_FULL = 13;
static const int INIT_SCREEN_WINDOW = 14;
static const int SOUND_INC = 15;
static const int SOUND_DEC = 16;
static const int MUSIC_INC = 17;
static const int MUSIC_DEC = 18;
static const int DIFFICULT_MENU = 1000;

static Font * normalFont = NULL;

extern void init( int GFX, int GAME_SPEED );


void credits() {
	cout << "Exiting normally.. " << endl;
	cout << "-------" << endl;
	cout << "Credits" << endl;
	cout << "Programming: Jon Rafkind" << endl;
	cout << "Graphics: Jon Rafkind and Elton Fry" << endl;
	cout << "Sound: Jon Rafkind" << endl;
	cout << "Gameplay: Jon Rafkind" << endl;
	cout << "Concept and design: Jon Rafkind" << endl;
	cout << "Almost all ideas stolen from other games, including idea to steal in the first place" << endl;
	cout << "Made with the Allegro graphics library by Shawn Hargreaves" << endl;
	cout << "Email Jon at: workmin@ccs.neu.edu" << endl;
}


void do_credits(){

	Bitmap work( GRAPHICS_X, GRAPHICS_Y );
	work.clear();

	int y_begin = GRAPHICS_Y-20;
	char ** creds = new char*[6];
	creds[0] = "Rafkill";
	creds[1] = "Programming Jon Rafkind";
	creds[2] = "Design Jon Rafkind";
	creds[3] = "Art Jon Rafkind";
	creds[4] = "Art Elton Fry";
	creds[5] = "Sound Jon Rafkind";

	// int * shade = new int[60];
	int shade[ 60 ];
	#define RCOLOR (127+Util::rnd(127))
	shade[0] = Bitmap::makeColor( RCOLOR, RCOLOR, RCOLOR );
	for ( int q = 0; q < 4; q++ ){
		Util::blend_palette( shade+q*12+1, 12, shade[q*12], Bitmap::makeColor(RCOLOR,RCOLOR,RCOLOR) );
	}
	Util::blend_palette( shade+48, 12, shade[48], shade[0] );
	int color = 0;
	int shade_color = 0;

	WormHole wole;
	for ( int q = 0; q < 40; q++ )
		wole.Update();

	unsigned int ticks;
	Util::getTicks( &ticks );
	while ( ! Keyboard::getAnyKey( Keyboard::SPACE ) && ! Keyboard::getAnyKey( Keyboard::ESC ) ){

		bool draw = false;
		int counter = Util::getTicks( &ticks );
		if ( counter == 0 ){
			Util::YIELD();
			continue;
		}
		while ( counter ){
			draw = true;
			if ( y_begin > 100 ) y_begin-=2;
			if ( y_begin > 100 ) {
				y_begin-=2;
				color = Bitmap::makeColor(255,255,255);
			}
			else {
				color = shade[ shade_color ];
				shade_color++;
				if ( shade_color > 59 ) shade_color = 0;
			}

			wole.Update();

			counter--;
		}

		if ( draw ) {
			wole.Draw( work );

			for ( int q = 0; q < 6; q++ ){
				work.printf( 100, y_begin + q * 30, color, normalFont, creds[q] );
			}
			work.BlitToScreen();
			work.clear();
			/*
			blit( work, screen, 0, 0, 0, 0, GRAPHICS_X, GRAPHICS_Y );
			clear( work );
			*/
		}
	}
	while ( Keyboard::getAnyKey( Keyboard::SPACE ) ){
		Util::YIELD();
	}
	// destroy_bitmap( work );
	delete[] creds;
	// delete[] shade;

}

Bitmap get_help_screen() {

	Bitmap work( 640, 480 );
	work.fill( Bitmap::makeColor( 0, 12, 19 ) );

	//int cy = 10;
	/*
	textprintf(work,font,10,cy,makecol(255,255,255),"How to play Raptor" );cy+=10;
	textprintf(work,font,10,cy,makecol(255,255,255),"Main Menu Options" );cy+=10;
	textprintf(work,font,10,cy,makecol(255,255,255),"Continue: Continue playing an already started game" );cy+=10;
	textprintf(work,font,10,cy,makecol(255,255,255),"Play New: Play a new game" );cy+=10;
	textprintf(work,font,10,cy,makecol(255,255,255),"Options: More Options" );cy+=10;
	textprintf(work,font,10,cy,makecol(255,255,255),"Help: This screen" );cy+=10;
	textprintf(work,font,10,cy,makecol(255,255,255),"Credits: The credits! What else?" );cy+=10;
	textprintf(work,font,10,cy,makecol(255,255,255),"Quit: Quit the game" );cy+=10;
	cy += 10;
	textprintf(work,font,10,cy,makecol(255,255,255),"Options Menu" );cy+=10;
	textprintf(work,font,10,cy,makecol(255,255,255),"Frame Rate: Frame Rate Menu" );cy+=10;
	textprintf(work,font,10,cy,makecol(255,255,255),"Fullscreen: Fullscreen Mode" );cy+=10;
	textprintf(work,font,10,cy,makecol(255,255,255),"Background on/off: Turn the background on or off" );cy+=10;
	textprintf(work,font,10,cy,makecol(255,255,255),"" );cy+=10;
	textprintf(work,font,10,cy,makecol(255,255,255),"" );cy+=10;
	textprintf(work,font,10,cy,makecol(255,255,255),"" );cy+=10;
	textprintf(work,font,10,cy,makecol(255,255,255),"" );cy+=10;
	textprintf(work,font,10,cy,makecol(255,255,255),"" );cy+=10;
	textprintf(work,font,10,cy,makecol(255,255,255),"" );cy+=10;
	textprintf(work,font,10,cy,makecol(255,255,255),"" );cy+=10;
	*/

	return work;

}

SpaceObject * getNewPlayer( int difficulty ){

	SpaceObject * player = NULL;

	vector< Bitmap * > pics;
	for ( int q = 0; q < 9; q++ ){
		pics.push_back( new Bitmap( Util::getDataSprite( HULL_1_1 + q ) ) );
	}

	HullObject * hwho = new PlayerHull( pics, 100, 100, 3, 1, new ECollide( pics[4] ) );
	player = new PlayerObject(320,450, difficulty, hwho );
	WeaponObject * wwho = new WeaponMachineGun( 0, -1, -1, TEAM_PLAYER );
	player->giveWeapon( wwho, 0 );
	( ((PlayerObject *) player ) )->setLevel( 1 );

	return player;
}

void getLoadMenu( RMenu * menu, int load_num, int select_smp ){

	menu->clear();
	for ( int q = 0; q < 6; q++ ){
		char filename[ 64 ];
		snprintf( filename, 64, "player%d.rap", q+1 );
		if ( Util::exists( filename ) ){
			time_t tl = Util::fileTime( filename );
			struct tm * real_time = localtime( &tl );

			char xbuf[ 128 ];
			strftime( xbuf, 64, "%A %F", real_time );
			char * temp = (char *)malloc( sizeof(char) * 1024 );
			sprintf( temp, "Slot %d %s", q+1, xbuf );
			menu->addMenu( temp, normalFont, true, load_num+q+1, NULL, NO_SOUND );
		}
	}
	
	menu->addMenu( "Return", normalFont, true, 800, NULL, select_smp );
}

void popUp( const char * title ){

	int length = 550;
	int begin = 30;

	Bitmap sell_screen( GRAPHICS_X, GRAPHICS_Y );
	Bitmap::Screen->Blit( sell_screen );
	Bitmap::transBlender( 0, 0, 0, 120 );
	Bitmap::drawingMode( Bitmap::MODE_TRANS );
	sell_screen.rectangleFill( begin, 80, begin+length, 235, Bitmap::makeColor(0,0,0) );
	sell_screen.rectangle( begin, 80, begin+length, 235, Bitmap::makeColor(255,255,255) );
	Bitmap::drawingMode( Bitmap::MODE_SOLID );
	RMenu sell( sell_screen, begin+10, 100, 1000, Bitmap::makeColor(80,0,0), Bitmap::makeColor(255,136,0), RAPTOR_TITLE_COLOR );
	sell.addTitle( title, normalFont );
	sell.addMenu( "OK", normalFont, true, 1, &sell, NO_SOUND );
	sell.init();

	int call = -1;
	RMenu * current = &sell;
	while( call == -1 ) {
		call = current->procMenu( &current );
		if ( !sell.Selected() ) call = -1;
		Util::YIELD();
		// al_poll_duh( dumb_player );
		// dumb_player->play();

	}

	// delete sell;
	// destroy_bitmap( sell_screen );
}

int intro_screen( int & frames, int window_mode, bool & dl, SpaceObject ** player, DATAFILE * sound ){

	//RGB * crap = new RGB[256];
	// char * file_name_pcx = Util::data_file( "logosmoot.pcx" );
	char backgroundFile[ 4096 ];
	Util::getDataPath( backgroundFile, "logosmoot.pcx" );
	Bitmap intr( backgroundFile );
	// free( file_name_pcx );
	//delete[] crap;
	if ( intr.getError() ) {
		string message = "Could not load: ";
		message += backgroundFile;
		Util::alert( message.c_str() );
		return 3;
	}

	/*
	DUH * dumb_file = NULL;
	AL_DUH_PLAYER * dumb_player = NULL;
	char * d_file = data_file( "intro.mod" );
	dumb_file = dumb_load_mod( d_file );
	free( d_file );
	dumb_player = al_start_duh( dumb_file, 2, 0, music_vol, 4096, 22050 );
	*/

	int select_smp = INTRO_MENU_SELECT;

	/*
	RMenu * intro_menu = new RMenu( intr, 170, 220, makecol(120,0,0),makecol(255,0,0), RAPTOR_TITLE_COLOR);
	RMenu * option_menu = new RMenu( intr, 1, 120, makecol(120,0,0),makecol(255,0,0), RAPTOR_TITLE_COLOR );
	RMenu * frame_menu = new RMenu( intr, 1, 230, makecol(120,0,0),makecol(255,0,0), RAPTOR_TITLE_COLOR );
	RMenu * difficulty_menu = new RMenu( intr, 1, 210, makecol(120,0,0),makecol(255,0,0), RAPTOR_TITLE_COLOR );
	RMenu * sound_menu = new RMenu( intr, 1, 145, makecol(120,0,0), makecol(255,0,0), RAPTOR_TITLE_COLOR );
	*/
	RMenu intro_menu( intr, 170, 200, 1000, Bitmap::makeColor(120,0,0), Bitmap::makeColor(255,0,0), RAPTOR_TITLE_COLOR);
	RMenu option_menu( intr, 1, 120, 1000, Bitmap::makeColor(120,0,0), Bitmap::makeColor(255,0,0), RAPTOR_TITLE_COLOR );
	RMenu frame_menu( intr, 1, 230, 1000, Bitmap::makeColor(120,0,0), Bitmap::makeColor(255,0,0), RAPTOR_TITLE_COLOR );
	RMenu difficulty_menu( intr, 1, 180, 1000, Bitmap::makeColor(120,0,0), Bitmap::makeColor(255,0,0), RAPTOR_TITLE_COLOR );
	RMenu sound_menu( intr, 1, 145, 1000, Bitmap::makeColor(120,0,0), Bitmap::makeColor(255,0,0), RAPTOR_TITLE_COLOR );
	RMenu load_menu( intr, 1, 200, 1000, Bitmap::makeColor(128,64,0), Bitmap::makeColor(255,128,0), RAPTOR_TITLE_COLOR );

	// load_menu.addMenu( "Return", Util::raptor_font, true, 800, NULL, select_smp );
	getLoadMenu( &load_menu, INIT_LOAD, select_smp );

	if ( *player != NULL ){
		intro_menu.addMenu( "Continue", normalFont, true, INIT_CONTINUE,NULL,select_smp);
	}

	intro_menu.addMenu( "Play new", normalFont, true,INIT_PLAY,NULL,select_smp);
	intro_menu.addMenu( "Load Game", normalFont, true,INIT_LOAD,&load_menu,select_smp);
	intro_menu.addMenu( "Options", normalFont, true,INIT_OPT,&option_menu,select_smp);
	intro_menu.addMenu( "Credits", normalFont, true,INIT_CREDITS,&intro_menu,select_smp);
	intro_menu.addMenu( "Quit", normalFont, true,INIT_QUIT,NULL,select_smp);

	option_menu.addTitle( "Options", normalFont );
	string numnum = int2str( frames );
	// option_menu.addMenu( append("Frame rate ",numnum), normalFont, true,244,&frame_menu,select_smp);
	//if ( window_mode == GFX_AUTODETECT )
	//	option_menu->addMenu( "Windowed",Util::raptor_font,true,INIT_SCREEN,option_menu,select_smp);
	//else    option_menu->addMenu( "Fullscreen",Util::raptor_font,true,INIT_SCREEN,option_menu,select_smp);
	option_menu.addMenu( "Windowed", normalFont, true,INIT_SCREEN_WINDOW,&option_menu,select_smp);
	option_menu.addMenu( "Fullscreen", normalFont, true,INIT_SCREEN_FULL,&option_menu,select_smp);
	if ( dl )
		option_menu.addMenu( "Background on", normalFont, true,INIT_BACK,&option_menu,select_smp);
	else    option_menu.addMenu( "Background off", normalFont, true,INIT_BACK,&option_menu,select_smp);
	option_menu.addMenu( "Sound", normalFont, true, 800, &sound_menu, select_smp );
	option_menu.addMenu( "Return to Menu", normalFont, true,800,NULL,select_smp);

	/*
	frame_menu.addTitle( append("Frame Rate ",numnum), normalFont );
	//frame_menu->addTitle( "Frame Rate is Unstable",Util::raptor_font );
	frame_menu.addMenu( "Increase Rate", normalFont, true,INC_RATE,&frame_menu,select_smp);
	frame_menu.addMenu( "Decrease Rate", normalFont, true,DEC_RATE,&frame_menu,select_smp);
	frame_menu.addMenu( "Return to options", normalFont, true,800,NULL,select_smp);
	*/

	// char * sound_num = int2str( (int)(sound_vol * 100 ) );
	// char * music_num = int2str( (int)(music_vol * 100 ) );
	char soundNum[ 64 ];
	char musicNum[ 64 ];

	// int music_volume = 100;

	Font menuFont = Util::getMenuFont();

	sprintf( soundNum, "Sound volume %d", (int)(Util::sound_vol * 100 ));

	/* make music_volume be the Music::volume */
	sprintf( musicNum, "Music volume %d", (int)(Music::getVolume() * 100) );

	sound_menu.addTitle( soundNum, &menuFont );
	sound_menu.addMenu( "Increase sound volume", &menuFont, true, SOUND_INC, &sound_menu, select_smp );
	sound_menu.addMenu( "Decrease sound volume", &menuFont, true, SOUND_DEC, &sound_menu, select_smp );
	sound_menu.addTitle( musicNum, &menuFont );
	sound_menu.addMenu( "Increase music volume", &menuFont, true, MUSIC_INC, &sound_menu, select_smp );
	sound_menu.addMenu( "Decrease music volume", &menuFont, true, MUSIC_DEC, &sound_menu, select_smp );
	sound_menu.addMenu( "Return to options", &menuFont, true,800,NULL,select_smp);

	difficulty_menu.addTitle( "Difficulty", &menuFont );
	difficulty_menu.addMenu( "Very Easy", &menuFont, true, DIFFICULT_MENU+1, NULL, select_smp );
	difficulty_menu.addMenu( "Easy", &menuFont, true, DIFFICULT_MENU+2, NULL, select_smp );
	difficulty_menu.addMenu( "Medium", &menuFont, true, DIFFICULT_MENU+3, NULL, select_smp );
	difficulty_menu.addMenu( "Hard", &menuFont, true, DIFFICULT_MENU+4, NULL, select_smp );
	difficulty_menu.addMenu( "Impossible", &menuFont, true, DIFFICULT_MENU+5, NULL, select_smp );

	RMenu * current = &intro_menu;
	RMenu * temp = current;
	current->init();

	int g = -1;
	while ( g != INIT_QUIT && g != INIT_CONTINUE && g != INIT_PLAY ) {
		Util::YIELD();
		// al_poll_duh( dumb_player );
		/*
		dumb_player->play();
		*/

		temp = current;
		g = current->procMenu( &current );
		if ( !temp->Selected() ) g = -1;

		bool changed_frames = false;
		bool changed_sound = false;
		bool changed_music = false;

		if ( g > INIT_LOAD && g <= INIT_LOAD+6 ){
			int load = g - INIT_LOAD;

			// printf("Loading %d\n", load );
			*player = loadPlayer( load );

			if ( *player == NULL ){

				char tmp[ 64 ];
				snprintf( tmp, 64, "Error loading slot %d", load );
				popUp( tmp );

			} else g = INIT_CONTINUE;
		}

		switch ( g ) {
			case INC_RATE   : {
				frames++;
				changed_frames = true;
				break;
			}
			case DEC_RATE   : {
				if( frames > 1 ) {
					frames--;
					changed_frames = true;
				}
				break;
			}
			case SOUND_INC  : {
				Util::sound_vol += 0.02;
				if ( Util::sound_vol > 1.0 ) Util::sound_vol = 1.0;
				changed_sound = true;
				break;
			}
			case SOUND_DEC  : {
				Util::sound_vol -= 0.02;
				if ( Util::sound_vol < 0 ) Util::sound_vol = 0;
				changed_sound = true;
				break;
			}
			case MUSIC_INC  : {
				/*
				music_vol += 0.02;
				if ( music_vol > 1.0 ) music_vol = 1.0;
				*/
				Music::louden();
				// dumb_player->louden();
				changed_music = true;
				break;
			}
			case MUSIC_DEC  : {
				/*
				music_vol -= 0.02;
				if ( music_vol < 0 ) music_vol = 0;
				*/
				// dumb_player->soften();
				Music::soften();
				changed_music = true;

				break;
			}
			case INIT_CREDITS       : {
				do_credits();
				break;
			}
						  /*
			case INIT_SCREEN        : {
			if ( window_mode == GFX_AUTODETECT_FULLSCREEN )
			window_mode = GFX_AUTODETECT_WINDOWED;
			else    window_mode = GFX_AUTODETECT_FULLSCREEN;
			if ( window_mode == GFX_AUTODETECT_WINDOWED )
			option_menu->replace( 3, "Windowed", Util::raptor_font,true, INIT_SCREEN, option_menu, select_smp  );
			else    option_menu->replace( 3, "Fullscreen", Util::raptor_font,true, INIT_SCREEN, option_menu, select_smp );
			printf("Setting gfx mode to %d - Status ",window_mode);
			int cap = set_gfx_mode( window_mode, GRAPHICS_X, GRAPHICS_Y, 0, 0 );
			printf("%d\n",cap );
			if ( cap == -1 ) {
			printf("Allegro error: %s\n", allegro_error );
			set_gfx_mode(GFX_AUTODETECT,GRAPHICS_X,GRAPHICS_Y,0,0);
			option_menu->replace(3,"Error with gfx set", Util::raptor_font,false, INIT_SCREEN, option_menu, select_smp );
			}

			break;
			}
			*/
			case INIT_SCREEN_FULL   : {
				Bitmap::setGfxModeFullscreen( GRAPHICS_X, GRAPHICS_Y );
				break;
			}
			case INIT_SCREEN_WINDOW : {
				Bitmap::setGfxModeWindowed( GRAPHICS_X, GRAPHICS_Y );
				break;
			}
			case INIT_BACK          : {
				if ( dl ) dl = false;else dl=true;
				if ( dl ) option_menu.replace( 5, "Background ON", &menuFont, true, INIT_BACK, &option_menu, select_smp ); else
					option_menu.replace( 5, "Background off", &menuFont, true, INIT_BACK, &option_menu, select_smp );
				break;
			}

		}

		/*
		if ( changed_frames ) {
			free( numnum );
			numnum = int2str( frames );
			option_menu.replaceTitle( 2, append("Frame Rate ",numnum), &menuFont );
			frame_menu.replaceTitle( 1, append("Frame Rate ",numnum), &menuFont );
			install_int_ex( inc_speed_counter, MSEC_TO_TIMER( frames ) );
		}
		*/

		if ( changed_sound ) {
			// free( sound_num );
			// sound_num = int2str( (int)(sound_vol * 100 ) );
			sprintf( soundNum, "Sound volume %d", (int)(Util::sound_vol * 100) );
			sound_menu.replaceTitle( 1, soundNum, &menuFont );
		}

		if ( changed_music ) {
			// free( music_num );
			// music_num = int2str( (int)(music_vol * 100 ) );
			sprintf( musicNum, "Music volume %d", (int)(Music::getVolume() * 100) );
			sound_menu.replaceTitle( 4, musicNum, &menuFont );
			// al_duh_set_volume( dumb_player, music_vol );
		}

	}

	if ( g == INIT_PLAY ) {

		if ( *player != NULL )
			delete *player;
		current = &difficulty_menu;
		current->init();
		int v = 0;
		while ( !current->Selected() ) {
			v = current->procMenu( &current );
			// al_poll_duh( dumb_player );
			// dumb_player->play();
			Util::YIELD();
		}
		int difficulty = v - DIFFICULT_MENU;

		*player = getNewPlayer( difficulty );

		/*
		BITMAP ** pics = new BITMAP*[ 9 ];
		for ( int q = 0; q < 9; q++ )
			pics[q] = (BITMAP *)Util::global_data[HULL_1_1+q].dat;
		HullObject * hwho = new PlayerHull( pics, 9, 100, 100, 3, 1, new ECollide( pics[4], 6, makecol(255,0,255), 52 ) );
		*player = new PlayerObject(320,450, difficulty, hwho );
		WeaponObject * wwho = new WeaponMachineGun( 0, -1, NULL, TEAM_PLAYER );
		(*player)->giveWeapon( wwho, 0 );
		( ((PlayerObject *) (*player) ) )->level = 1;
		*/


	}

	if ( *player != NULL ){
		PlayerObject * px = (PlayerObject *)(*player);
		if ( px->getDifficulty() == 1 )
			Util::screen_x = 640;
		else    Util::screen_x = 640*3/2;
	}

	//al_stop_duh( dumb_player );
	//unload_duh( dumb_file );

	/*
	delete intro_menu;
	delete option_menu;
	delete frame_menu;
	delete difficulty_menu;
	delete sound_menu;
	*/
	// free( sound_num );
	// free( music_num );

	// destroy_bitmap( intr );

	return g;
}

void usage(){

	printf("OPTIONS\n");
	printf("------\n");
	printf("-w\t\t\tWindowed Mode\n");
	printf("-l\t\t\tNo background\n");
	printf("-g#\t\t\tRun game at # msec per tick\n");
	printf("-h -help --help\t\tThis Help Screen\n");
}

void deathScreen(){

	Font font = Util::getDefaultFont();

	int tx = font.textLength( "YOU DIED" );
	int ty = 10;
	// BITMAP * text = create_bitmap( tx, ty );
	Bitmap text( tx, ty );
	// clear( text );
	text.clear();
	// textprintf_ex( text, font, 0, 0, makecol(255,255,255), -1, "YOU DIED");
	text.printf( 0, 0, Bitmap::makeColor(255,255,255), &font, "YOU DIED" );
	// BITMAP * work = create_bitmap( GRAPHICS_X, GRAPHICS_Y );
	Bitmap work( GRAPHICS_X, GRAPHICS_Y );

	int _max_ex = 500;
	last_explode = 0;
	ExplosionClass ** expl = new ExplosionClass*[ _max_ex ];
	for ( int q = 0; q < _max_ex; q++ )
		expl[q] = NULL;

	while ( Keyboard::getAnyKey( Keyboard::SPACE, Keyboard::ENTER ) ){
		Util::YIELD();
	}

	unsigned int ticks;
	Util::getTicks( &ticks );
	while ( ! Keyboard::getAnyKey( Keyboard::SPACE ) && ! Keyboard::getAnyKey( Keyboard::ENTER ) ){

		bool dirty = false;
		unsigned int counter = Util::getTicks( &ticks );
		if ( counter == 0 ){
			Util::YIELD();
			continue;
		}
		while ( counter > 0 ){

			dirty = true;

			for ( int q = 0; q < 300; q++ ) {
				int x = Util::rnd( tx );
				int y = Util::rnd( ty );
				double ymove = ((double)y - (double)(ty-1) / 2.0) * 1.54;
				if ( text.getPixel( x, y ) == Bitmap::makeColor(255,255,255) )
					addExplode( expl, _max_ex, new ExplosionClass( x*9 + 50, y*9 + 200, 0, ymove, Util::rnd( 3 ) + 7 ) );
			}

			for ( int q = 0; q < _max_ex; q++ ){
				if( expl[q] != NULL ){
					if ( expl[q]->update() ) {
						delete expl[q];
						expl[q] = NULL;
					}
				}
			}
			counter--;
		}

		if ( dirty ) {
			for ( int q = 0; q < _max_ex; q++ )
				if ( expl[q] != NULL )
					expl[q]->Draw( &work, 0 );

			work.BlitToScreen();
			work.clear();
		}
	}

	for ( int q = 0; q < _max_ex; q++ ){
		if ( expl[q] ){
			delete expl[q];
		}
	}
	delete[] expl;

	/*
	destroy_bitmap( text );
	destroy_bitmap( work );
	*/

	while ( Keyboard::getAnyKey( Keyboard::SPACE, Keyboard::ENTER ) ){
		Util::YIELD();
	}

}

void pauseGame(){

	Bitmap work( Util::screen_x, Util::screen_y );
	work.fill( Bitmap::makeColor( 32, 32, 32 ) );

	int width = 100;
	int height = 50;

	work.rectangleFill( 320 - width / 2, 240 - height / 2, 320 + width / 2, 240 + height / 2, Bitmap::makeColor( 0, 0, 0 ) );
	work.rectangle( 320 - width / 2, 240 - height / 2, 320 + width / 2, 240 + height / 2, Bitmap::makeColor( 200, 0, 0 ) );
	Font font = Util::getNormalFont();
	work.printf( 320 - font.textLength( "Paused" ) / 2, 240 - 10, Bitmap::makeColor(255,128,0), &font, "Paused" );

	work.drawTrans( 0, 0, *Bitmap::Screen );
	while ( Keyboard::getAnyKey( Keyboard::P ) ){
		Util::YIELD();
	}
	while ( ! Keyboard::getAnyKey( Keyboard::P ) ){
		Util::YIELD();
	}
	while ( Keyboard::getAnyKey( Keyboard::P ) ){
		Util::YIELD();
	}
}

void playLevel( PlayerObject * const player ){
	char file_level[ 64 ];
	sprintf( file_level, "level%d.lev", player->getLevel() );

	player->SetCoordXY( Util::screen_x/2, Util::screen_y - 40 );

	int game_error = 0;
	int score = player->getScore();

	// dumb_player.pause();
	Drawer draw;
	Logic logic;
	LevelCreator level( file_level, player ); 
				
	/* stop loading screen */
	endLoadingScreen();

	const int QUIT = 6;

	int doneCounter = 0;
	int deathCounter = 0;
	unsigned int ticks;
	Util::getTicks( &ticks );

	PlayerObject * gamePlayer = player;

	while ( game_error == 0 ){

		bool doDraw = false;
		int counter = Util::getTicks( &ticks );
		if ( counter == 0 ){
			Util::YIELD();
			continue;
		}

		while ( counter > 0 ){
			logic.runCycle( gamePlayer, &level );
			counter--;
			doDraw = true;
		}

		if ( doDraw ){
			draw.Draw( logic.getObjects(), gamePlayer, logic.getExplode(), logic.maxExplode() );
		}

		if ( Keyboard::getAnyKey( Keyboard::P ) ){
			pauseGame();
			Util::getTicks( &ticks );
		}

		while ( Keyboard::getAnyKey( Keyboard::L ) && counter < 7 ){
			counter += Util::getTicks( &ticks );
			Util::YIELD();
		}

		if ( deathCounter == 0 ){
			if ( player->getLife() <= 0 ){
				gamePlayer = NULL;
				deathCounter = 1;
			}
		} else {
			if ( ++deathCounter > 80 ){
				game_error = 1;
			}
		}

		if ( doneCounter == 0 ){
			if ( level.done() ){
				doneCounter = 1;
			}
		} else {
			if ( ++doneCounter > 400 ){
				game_error = 5;
			}
			
			int min = 350;
			if ( doneCounter > min ){
				draw.fadeToBlack( 255 - (doneCounter - min) * 4 );
			}
		}

		if ( Keyboard::getAnyKey( Keyboard::V ) ){
			game_error = 5;
		}

		if ( Keyboard::getAnyKey( Keyboard::ESC ) ){
			game_error = QUIT;
		}
	}

	/*
	if ( player->getLevel() == 1 ){
		real_level++;
	}
	*/

	// cout << "Game error = " << game_error << endl;

	switch( game_error ) {
		case 5  : {
			player->setLevel( player->getLevel()+1 );
			break;

		}
		case 1  : {
			deathScreen();
			player->setScore( score );
			break;
		}
		case 2  : {
			player->setLevel( 1 );
			break;
		}
		case 3  : {
			// quit = true;
			break;
			  }
		case 4  : {
			break;
		}
		case QUIT : {
			player->setScore( score );
			break;
		}
		default : {
		}
	}
}

static vector< string > getSongs(){
	return Util::getFiles( "music/", "*" );
}

/*
static string getSong(){
	struct al_ffblk info;
	vector< string > files;

	string dataPath = "music/";

	if ( al_findfirst( (dataPath + "*").c_str(), &info, 0 ) != 0 ){
		return "";
	}
	files.push_back( string( info.name ) );
	while ( al_findnext( &info ) == 0 ){
		files.push_back( string( info.name ) );
	}
	al_findclose( &info );

	return dataPath + files[ Util::rnd( files.size() ) ];
}
*/

//******************************MAIN**************************
int rafkill( int argc, char ** argv ) {

	int window = 0;
	bool dl = true;
	int gameSpeed = 40;

	printf("raptor -h for help screen\n");
	for ( int q = 1; q < argc; q++ ) {
		if ( strcmp( argv[q], "-h" ) == 0 || strcmp( argv[q], "-help" ) == 0 || strcmp( argv[q], "--help" ) == 0 ) {
			usage();
			return 0;
		}
		if ( strcmp( argv[q], "-w" ) == 0 ){
			window = 1;
		} else if ( strcmp( argv[q], "-l" ) == 0 ){
			dl = false;
		} else if ( strlen( argv[q] ) > 2 ){
			if ( argv[q][1] == 'g' ){
				gameSpeed = atoi( &argv[q][2] );
			}
		}
	}
	
	if ( gameSpeed <= 0 ){
		gameSpeed = 40;
	}

	cout << "Running game at " << gameSpeed << endl;
	cout << "Using mode " << window << endl;
	init( window, gameSpeed );
	cout << "OS " << Util::getOS() << endl;

	Util::loadGlobals();
	
	Font useFont = Util::getMenuFont();
	normalFont = &useFont;
	
	char musicPath[ 1024 ];
	Util::getDataPath( musicPath, "intro.mod" );
	
	/* musicBox will be destructed at the end of main() and thus free up all music resources */
	Music musicBox;
	
	Music::loadSong( musicPath );

	SpaceObject * player;
	menuClass menu;

	player = NULL; 

	/*
	{
		player = getNewPlayer( 3 );
		playLevel( (PlayerObject * )player );
		delete player;
		return 0;
	}
	*/

	Bitmap::transBlender( 0, 0, 0, 192 );

	cout << "** Running game" << endl;
	bool quit;
	// int real_level = 1;
	int geti;
	while ( (geti = intro_screen( gameSpeed, window, dl, &player, Util::global_snd ) ) != INIT_QUIT ) {
		quit = geti == INIT_QUIT;
		while ( ! quit ) {

			if ( ! quit && geti != INIT_CONTINUE ) {
				/* show some loading text in a seperate thread */
				startLoadingScreen();

				/* load new song */
				Music::loadSong( getSongs() );

				/* play level */
				playLevel( (PlayerObject *) player );
				Bitmap::transBlender( 0, 0, 0, 192 );

				/* load intro music and go to menu */
				Music::loadSong( musicPath );
			}

			/* TODO: dont leave this */
			// player->setScore( player->getScore() + 1000000 );

			geti = INIT_PLAY;
			quit = menu.activate( player );
		}
		/* go back to main menu */
	}

	/* deal with globally allocated memory */
	if ( player ){
		delete player;
	}

	cout << "Unloading data" << endl;

	Util::unloadGlobals();

	credits();

	return 0;
}
