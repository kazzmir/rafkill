#include "menu.h"
#include "spaceobj.h"
// #include "game.h"
#include "drawer.h"
#include "logic.h"
#include "level.h"
#include "trigtable.h"
#include "bitmap.h"
#include "keyboard.h"
#include "mouse.h"
#include "strings.h"
#include <string.h>
#include <sstream>
#include <iostream>
#include "loadsave.h"
#include "defs.h"
#include "ebox.h"
#include "raptor.h"
#include "sound.h"
#include "rmenu.h"
#include "rfield.h"
#include "hull.h"
#include "wormhole.h"
#include "explode.h"
#include "music.h"
#include "loading_screen.h"

#include "hulls/hull_player.h"
#include "playerobj.h"
#include "guns/gun_machine.h"

#include "config.h"

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
static const int INIT_CHANGE_KEYS = 8;
static const int INIT_MOUSE = 9;
static const int INIT_LOAD = 5000;
static const int INC_RATE = 10;
static const int DEC_RATE = 11;
static const int INIT_HELP = 12;
static const int INIT_SCREEN = 13;
static const int SOUND_INC = 15;
static const int SOUND_DEC = 16;
static const int MUSIC_INC = 17;
static const int MUSIC_DEC = 18;
static const int MOUSE_INC = 100;
static const int MOUSE_DEC = 101;
static const int DIFFICULT_MENU = 1000;

static const int CHANGE_KEY_FORWARD = 20;
static const int CHANGE_KEY_BACKWARD = 21;
static const int CHANGE_KEY_LEFT = 22;
static const int CHANGE_KEY_RIGHT = 23;
static const int CHANGE_KEY_SHOOT = 24;

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
	const char ** creds = new const char*[6];
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

	Bitmap work( GRAPHICS_X, GRAPHICS_Y );
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
	player = new PlayerObject(Util::screen_x / 2, 450, difficulty, hwho );
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
	// Bitmap::Screen->Blit( sell_screen );
	sell_screen.CopyScreen();
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

static int userSelectKey(){

	Bitmap work( normalFont->textLength( "Press a key" ) + 20, 50 );
	work.fill( Bitmap::makeColor( 32, 32, 32 ) );

	work.printf( 10, 10, Bitmap::makeColor( 200, 64, 23 ), normalFont, "Press a key" );
	work.drawBorder( 2, Bitmap::makeColor( 200, 200, 200 ) );

	work.drawTransScreen( GRAPHICS_X / 2 - work.getWidth() / 2, GRAPHICS_Y / 2 - work.getHeight() / 2 - 100 );

	while ( Keyboard::readKey() != -1 ){
		Util::YIELD();
	}

	int key = Keyboard::readKey();
	while ( key == -1 ){
		Util::YIELD();
		key = Keyboard::readKey();
	}

	while ( Keyboard::keyPressed() ){
		Util::YIELD();
	}

	return key;
}

int intro_screen( int & frames, SpaceObject ** player, DATAFILE * sound ){

	char backgroundFile[ 4096 ];
	#ifdef PANDORA
	Util::getDataPath( backgroundFile, "logosmoot-pandora.pcx" );
	#else
	Util::getDataPath( backgroundFile, "logosmoot.pcx" );
	#endif
	Bitmap intr( backgroundFile );

	if ( intr.getError() ) {
		string message = "Could not load: ";
		message += backgroundFile;
		Util::alert( message.c_str() );
		return 3;
	}

	int select_smp = INTRO_MENU_SELECT;

	RMenu intro_menu( intr, 170, 200, 1000, Bitmap::makeColor(120,0,0), Bitmap::makeColor(255,0,0), RAPTOR_TITLE_COLOR);
	RMenu option_menu( intr, 1, 120, 1000, Bitmap::makeColor(120,0,0), Bitmap::makeColor(255,0,0), RAPTOR_TITLE_COLOR );
	RMenu frame_menu( intr, 1, 230, 1000, Bitmap::makeColor(120,0,0), Bitmap::makeColor(255,0,0), RAPTOR_TITLE_COLOR );
	RMenu difficulty_menu( intr, 1, 180, 1000, Bitmap::makeColor(120,0,0), Bitmap::makeColor(255,0,0), RAPTOR_TITLE_COLOR );
	RMenu changeKeyMenu( intr, 1, 180, 1000, Bitmap::makeColor(120,0,0), Bitmap::makeColor(255,0,0), RAPTOR_TITLE_COLOR );
	RMenu mouseMenu( intr, 1, 180, 1000, Bitmap::makeColor(120,0,0), Bitmap::makeColor(255,0,0), RAPTOR_TITLE_COLOR );
	RMenu sound_menu( intr, 1, 145, 1000, Bitmap::makeColor(120,0,0), Bitmap::makeColor(255,0,0), RAPTOR_TITLE_COLOR );
	RMenu load_menu( intr, 1, 200, 1000, Bitmap::makeColor(128,64,0), Bitmap::makeColor(255,128,0), RAPTOR_TITLE_COLOR );

	// load_menu.addMenu( "Return", Util::raptor_font, true, 800, NULL, select_smp );
	getLoadMenu( &load_menu, INIT_LOAD, select_smp );

	if ( *player != NULL ){
		intro_menu.addMenu( "Continue", normalFont, true, INIT_CONTINUE,NULL,select_smp);
	}

	// intro_menu.addMenu( "Play new", normalFont, true,INIT_PLAY,NULL,select_smp);
	intro_menu.addMenu( "Play new", normalFont, true, INIT_PLAY, &difficulty_menu, select_smp );
	intro_menu.addMenu( "Load Game", normalFont, true,INIT_LOAD,&load_menu,select_smp);
	intro_menu.addMenu( "Options", normalFont, true,INIT_OPT,&option_menu,select_smp);
	intro_menu.addMenu( "Credits", normalFont, true,INIT_CREDITS,&intro_menu,select_smp);
	intro_menu.addMenu( "Quit", normalFont, true,INIT_QUIT,NULL,select_smp);

	option_menu.addTitle( "Options", normalFont );
	string numnum = int2str( frames );

	RField * forwardKey = changeKeyMenu.addMenu( string("Forward: ") + Configuration::getForwardKeyName(), normalFont, true, CHANGE_KEY_FORWARD, &changeKeyMenu, select_smp );
	RField * backwardKey = changeKeyMenu.addMenu( string("Backwards: ") + Configuration::getBackwardKeyName(), normalFont, true, CHANGE_KEY_BACKWARD, &changeKeyMenu, select_smp );
	RField * leftKey = changeKeyMenu.addMenu( string("Left: ") + Configuration::getLeftKeyName(), normalFont, true, CHANGE_KEY_LEFT, &changeKeyMenu, select_smp );
	RField * rightKey = changeKeyMenu.addMenu( string("Right: ") + Configuration::getRightKeyName(), normalFont, true, CHANGE_KEY_RIGHT, &changeKeyMenu, select_smp );
	RField * shootKey = changeKeyMenu.addMenu( string("Shoot: ") + Configuration::getShootKeyName(), normalFont, true, CHANGE_KEY_SHOOT, &changeKeyMenu, select_smp );

	changeKeyMenu.addMenu( "Return", normalFont, true, INIT_OPT, NULL, select_smp );
	
	Font menuFont = Util::getMenuFont();

	int mouse_sensitivity = (int)(mouse::getSensitivity() * 3);
	char mouseNum[ 64 ];
	sprintf( mouseNum, "Sensitivity: %d", mouse_sensitivity );
	RField * mouseSensitivity = mouseMenu.addTitle( mouseNum, &menuFont );
	mouseMenu.addMenu( "Increase sensitivity", &menuFont, true, MOUSE_INC, &mouseMenu, select_smp );
	mouseMenu.addMenu( "Decrease sensitivity", &menuFont, true, MOUSE_DEC, &mouseMenu, select_smp );
	mouseMenu.addMenu( "Return", normalFont, true, INIT_OPT, NULL, select_smp );

	option_menu.addMenu( "Change Keys", normalFont, true, INIT_CHANGE_KEYS, &changeKeyMenu, select_smp );
	option_menu.addMenu( "Mouse", normalFont, true, INIT_MOUSE, &mouseMenu, select_smp );
	
	RField * fullscreenField;
	if ( Configuration::getWindowMode() ){
		fullscreenField = option_menu.addMenu( "Fullscreen Off", normalFont, true,INIT_SCREEN,&option_menu,select_smp);
	} else {
		fullscreenField = option_menu.addMenu( "Fullscreen On",  normalFont, true,INIT_SCREEN,&option_menu,select_smp);
	}

	RField * backgroundField;
	if ( Configuration::getBackground() ){
		backgroundField = option_menu.addMenu( "Background On", normalFont, true, INIT_BACK, &option_menu, select_smp );
	} else {
		backgroundField = option_menu.addMenu( "Background Off", normalFont, true, INIT_BACK, &option_menu, select_smp);
	}
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


	sprintf( soundNum, "Sound volume %d", (int)(Util::sound_vol * 100 ));

	/* make music_volume be the Music::volume */
	sprintf( musicNum, "Music volume %d", (int)(Music::getVolume() * 100) );

	RField * soundTitle = sound_menu.addTitle( soundNum, &menuFont );
	sound_menu.addMenu( "Increase sound volume", &menuFont, true, SOUND_INC, &sound_menu, select_smp );
	sound_menu.addMenu( "Decrease sound volume", &menuFont, true, SOUND_DEC, &sound_menu, select_smp );
	RField * musicTitle = sound_menu.addTitle( musicNum, &menuFont );
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

	int option = -1;
	bool done = false;
	while ( ! done ){

		Util::YIELD();

		temp = current;
		option = current->procMenu( &current );
		if ( !temp->Selected() ) option = -1;

		bool changed_frames = false;
		bool changed_sound = false;
		bool changed_music = false;

		if ( option > INIT_LOAD && option <= INIT_LOAD+6 ){
			int load = option - INIT_LOAD;

			// printf("Loading %d\n", load );
			*player = loadPlayer( load );

			if ( *player == NULL ){

				char tmp[ 64 ];
				snprintf( tmp, 64, "Error loading slot %d", load );
				popUp( tmp );

			} else option = INIT_CONTINUE;
		}

		switch ( option ) {
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
				Music::louden();
				changed_music = true;
				break;
			}
			case MUSIC_DEC  : {
				Music::soften();
				changed_music = true;
				break;
			}
			case MOUSE_INC : {
				mouse_sensitivity = mouse_sensitivity + 1;
				if ( mouse_sensitivity > 20 ){
					mouse_sensitivity = 20;
				}
				sprintf( mouseNum, "Sensitivity: %d", mouse_sensitivity );
				string str( mouseNum );
				mouse::setSensitivity( mouse_sensitivity );
				mouseSensitivity->set( &str );
				break;
			}
			case MOUSE_DEC : {
				mouse_sensitivity = mouse_sensitivity - 1;
				if ( mouse_sensitivity < 1 ){
					mouse_sensitivity = 1;
				}
				sprintf( mouseNum, "Sensitivity: %d", mouse_sensitivity );
				string str( mouseNum );
				mouse::setSensitivity( mouse_sensitivity );
				mouseSensitivity->set( &str );
				break;
			}
			case INIT_CREDITS       : {
				do_credits();
				break;
			}

			case CHANGE_KEY_FORWARD : {
				int key = userSelectKey();
				Configuration::setForwardKey( key );
				stringstream stream;
				stream << "Forward: " << Configuration::getForwardKeyName();
				string str( stream.str() );
				forwardKey->set( &str );
				break;
			}

			case CHANGE_KEY_LEFT : {
				int key = userSelectKey();
				Configuration::setLeftKey( key );
				stringstream stream;
				stream << "Left: " << Configuration::getLeftKeyName();
				string str( stream.str() );
				leftKey->set( &str );
				break;
			}

			case CHANGE_KEY_RIGHT : {
				int key = userSelectKey();
				Configuration::setRightKey( key );
				stringstream stream;
				stream << "Right: " << Configuration::getRightKeyName();
				string str( stream.str() );
				rightKey->set( &str );

				break;
			}

			case CHANGE_KEY_BACKWARD : {
				int key = userSelectKey();
				Configuration::setBackwardKey( key );
				stringstream stream;
				stream << "Backwards: " << Configuration::getBackwardKeyName();
				string str( stream.str() );
				backwardKey->set( &str );
				break;
			}

			case CHANGE_KEY_SHOOT : {
				int key = userSelectKey();
				Configuration::setShootKey( key );
				stringstream stream;
				stream << "Shoot: " << Configuration::getShootKeyName();
				string str( stream.str() );
				shootKey->set( &str );
				break;
			}
			case INIT_SCREEN : {
				Configuration::setWindowMode( ! Configuration::getWindowMode() );
				if ( Configuration::getWindowMode() ) {
					Bitmap::setGfxModeWindowed( GRAPHICS_X, GRAPHICS_Y );
					string str( "Fullscreen Off" );
					fullscreenField->set( &str );
				} else {
					Bitmap::setGfxModeFullscreen( GRAPHICS_X, GRAPHICS_Y );
					string str( "Fullscreen On" );
					fullscreenField->set( &str );
				}
  				break;
  			}
			
			case INIT_CONTINUE :
			case INIT_QUIT : {
				done = true;
				break;
			}

			case INIT_BACK : {
				Configuration::setBackground( ! Configuration::getBackground() );
				if ( Configuration::getBackground() ){
					// option_menu.replace( 5, "Background ON", &menuFont, true, INIT_BACK, &option_menu, select_smp );
					string str( "Background On" );
					backgroundField->set( &str );
				} else {
					// option_menu.replace( 5, "Background off", &menuFont, true, INIT_BACK, &option_menu, select_smp );
					string str( "Background Off" );
					backgroundField->set( &str );
				}
				break;
			}

			/* selected a new game */
			case DIFFICULT_MENU + 1 :
			case DIFFICULT_MENU + 2 :
			case DIFFICULT_MENU + 3 :
			case DIFFICULT_MENU + 4 :
			case DIFFICULT_MENU + 5 : {
				if ( *player != NULL ){
					delete *player;
				}

				int difficulty = option - DIFFICULT_MENU;
				*player = getNewPlayer( difficulty );
				done = true;
				break;
			}
		}

		/* wait for enter/space to be released
		 * so the user doesnt get into a loop of selecting
		 * enter or space for the key and then modifying
		 * that key again
		 */
		if ( option == CHANGE_KEY_SHOOT ||
                     option == CHANGE_KEY_FORWARD ||
                     option == CHANGE_KEY_BACKWARD ||
                     option == CHANGE_KEY_LEFT ||
                     option == CHANGE_KEY_RIGHT ){
			while ( Keyboard::getAnyKey( Keyboard::SPACE, Keyboard::ENTER ) ){
				Util::YIELD();
			}
		}

		if ( changed_sound ) {
			stringstream stream;
			stream << "Sound volume " << (int)(Util::sound_vol * 100);
			string str( stream.str() );
			soundTitle->set( &str );
		}

		if ( changed_music ) {
			stringstream stream;
			stream << "Music volume " << (int)(Music::getVolume() * 100);
			string str( stream.str() );
			musicTitle->set( &str );
		}

	}

	/*
	if ( 0 && option == INIT_PLAY ) {

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
	}
	*/

	if ( *player != NULL ){
		PlayerObject * px = (PlayerObject *)(*player);
		if ( px->getDifficulty() == 1 )
			Util::screen_x = GRAPHICS_X;
		else    Util::screen_x = GRAPHICS_X*3/2;
	}

	Configuration::saveConfiguration();

	return option;
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

        int halfX = Util::screen_x / 2;
        int halfY = Util::screen_y / 2;

	int width = 100;
	int height = 50;

	work.rectangleFill(halfX - width / 2, halfY - height / 2, halfX + width / 2, halfY + height / 2, Bitmap::makeColor( 0, 0, 0 ) );
	work.rectangle(halfX - width / 2, halfY - height / 2, halfX + width / 2, halfY + height / 2, Bitmap::makeColor( 200, 0, 0 ) );
	Font font = Util::getNormalFont();
	work.printf(halfX - font.textLength( "Paused" ) / 2, halfY - 10, Bitmap::makeColor(255,128,0), &font, "Paused" );

	// work.drawTrans( 0, 0, *Bitmap::Screen );
	work.drawTransScreen( 0, 0 );
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

/* reset gun strengths if the player died */
static void resetStrengths( const map<WeaponObject*,int> & guns ){
	for ( map<WeaponObject*,int>::const_iterator it = guns.begin(); it != guns.end(); it++ ){
		WeaponObject * weapon = (*it).first;
		int strength = (*it).second;
		weapon->setPower( strength );
	}
}

void playLevel( PlayerObject * const player ){
	char file_level[ 64 ];
	sprintf( file_level, "level%d.lev", player->getLevel() );

	player->SetCoordXY( Util::screen_x/2, Util::screen_y - 40 );

	int game_error = 0;
	int score = player->getScore();
	map<WeaponObject*,int> oldPower = player->gunStrengths();

	// dumb_player.pause();
	Drawer draw;
	Logic logic;
	LevelCreator level( file_level, player ); 
	draw.setDrawLand( Configuration::getBackground() );
				
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

		/*
		while ( Keyboard::getAnyKey( Keyboard::L ) && counter < 7 ){
			counter += Util::getTicks( &ticks );
			Util::YIELD();
		}
		*/

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
			resetStrengths( oldPower );
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
			resetStrengths( oldPower );
			break;
		}
		default : {
		}
	}
}

static vector< string > getSongs(){
	return Util::getFiles( "music/", "*" );
}

int rafkill( int argc, char ** argv ) {

	int gameSpeed = 40;

	printf("rafkill -h for help screen\n");
	for ( int q = 1; q < argc; q++ ) {
		if ( strcmp( argv[q], "-h" ) == 0 || strcmp( argv[q], "-help" ) == 0 || strcmp( argv[q], "--help" ) == 0 ) {
			usage();
			return 0;
		}
		if ( strcmp( argv[q], "-w" ) == 0 ){
			Configuration::setWindowMode( true );
		} else if ( strcmp( argv[q], "-W" ) == 0 ){
			Configuration::setWindowMode( false );
		} else if ( strcmp( argv[q], "-l" ) == 0 ){
			Configuration::setBackground( false );
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
	cout << "Using window mode " << Configuration::getWindowMode() << endl;
	init( Configuration::getWindowMode(), gameSpeed );
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
	while ( (geti = intro_screen( gameSpeed, &player, Util::global_snd ) ) != INIT_QUIT ) {
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

	// Configuration::saveConfiguration();

	cout << "Unloading data" << endl;

	Util::unloadGlobals();

	credits();

	return 0;
}
