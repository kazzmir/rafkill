#ifdef WINDOWS
#include <allegro.h>
#include <winalleg.h>
#endif

#include "bitmap.h"
#include "defs.h"
#include <pthread.h>

static pthread_t loadingThread;
static pthread_mutex_t loadingMutex;
static bool loading = false;

static const int MAX_COLORS = 32;
static int shades[ MAX_COLORS ];

#define LOCK pthread_mutex_lock( &loadingMutex );
#define UNLOCK pthread_mutex_unlock( &loadingMutex );

static void * loadScreen( void * arg );

void startLoadingScreen(){

	loading = true;
	int c1 = Bitmap::makeColor( 128, 32, 94 );
	int c2 = Bitmap::makeColor( 200, 10, 160 );
	Util::blend_palette( shades, MAX_COLORS >> 1, c1, c2 );
	Util::blend_palette( shades + (MAX_COLORS >> 1), MAX_COLORS >> 1, c2, c1 );
	pthread_mutex_init( &loadingMutex, NULL );
	pthread_create( &loadingThread, NULL, loadScreen, NULL );

}

static void * loadScreen( void * arg ){

	int i = 0;
	bool alive = true;
	unsigned int ticks;
	Font font = Util::getNormalFont();
	Util::getTicks( &ticks );
	Bitmap temp( font.textLength("Loading") + 1, font.getHeight() );
	temp.fill( Bitmap::MaskColor );
	while ( alive ){
		
		LOCK;{
			alive = loading;
		}
		UNLOCK;

		bool draw = false;

		int count = Util::getTicks( &ticks );
		if ( count == 0 ){
			Util::YIELD();
			continue;
		}
		while ( count > 0 ){
			i = (i + 1) % MAX_COLORS;
			count--;
			draw = true;
		}
		
		if ( draw ){
			int color = shades[ i ];
			// Util::raptor_font->rtext( *Bitmap::Screen, 300, 220, color, "Loading" );
			
			// Bitmap::Screen->printfNormal( 300, 220, color, "Loading" );
			// Bitmap::Screen->printf( 300, 220, color, &font, "Loading" );
			temp.printf( 0, 0, color, &font, "Loading" );
			temp.drawToScreen( GRAPHICS_X / 2, GRAPHICS_Y / 2 );
		}
	}

	return NULL;
}

void endLoadingScreen(){
	LOCK;{
		loading = false;
	}
	UNLOCK;
	pthread_join( loadingThread, NULL );
}
