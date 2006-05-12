#include <allegro.h>
#include "defs.h"
#include <dumb.h>
#include <aldumb.h>

void inc_speed_counter() {
	Util::speed_counter++;
}

END_OF_FUNCTION( inc_speed_counter );

void init( int mode, int GAME_SPEED ) {

	allegro_init();
	srand( time( NULL ) );
	install_timer();
	install_keyboard();

	/*
	if ( get_desktop_resolution(&Util::screen_x,&Util::screen_y) == -1 ){
		Util::screen_x = 640;
		Util::screen_y = 480;
	}
	*/

	int gfx = GFX_AUTODETECT_WINDOWED;
	switch ( mode ){
		case 0 : {
			gfx = GFX_AUTODETECT_FULLSCREEN;
			break;
		}
		case 1 : {
			gfx = GFX_AUTODETECT_WINDOWED;
			break;
		}
	}

	set_color_depth( 16 );
	if ( set_gfx_mode( gfx, GRAPHICS_X, GRAPHICS_Y, 0, 0 ) != 0 ){
		if ( set_gfx_mode( GFX_AUTODETECT, GRAPHICS_X, GRAPHICS_Y, 0, 0 ) != 0 ) {
			allegro_message( "Could not initialize a graphics mode.. bailing" );
			exit( 1 );
		}
	}
	// text_mode( -1 );
	reserve_voices (8, -1);
	set_volume_per_voice( 0 );
	install_sound( DIGI_AUTODETECT, MIDI_NONE, "" );
	atexit( &dumb_exit );
	dumb_register_packfiles();

	LOCK_VARIABLE( speed_counter );
	LOCK_FUNCTION( (void *)inc_speed_counter );
	install_int_ex( inc_speed_counter, MSEC_TO_TIMER( GAME_SPEED ) );
	Util::explColor();
	set_trans_blender( 0, 0, 0, 128 );
	//set_config_int( "sound", "quality", 2 );
	get_config_int( "sound", "quality", 2 );
	Util::sound_vol = 1.0;			  //max volume to begin with
	// music_vol = 0.50;
	dumb_resampling_quality = get_config_int( "sound", "dumb_resampling_quality", 1 );

	/* set up global screen variable */
	Bitmap::Screen = new Bitmap( screen );
}

