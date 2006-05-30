#include <string.h>
#include "rmenu.h"
#include "trigtable.h"
#include "strings.h"
#include "rfield.h"
#include "keyboard.h"
#include "font.h"
#include <stdio.h>
#include "bitmap.h"

static const int MAX_SHADE_OPT_COLOR = 14;
static const int NO_SOUND = -1;

RMenu::RMenu( const Bitmap & intr, int x1, int y1, int _height, int c1, int c2, int title_color ):
last_opt( 0 ),
first_x( x1 ),
first_y( y1 ),
col1( c1 ),
col2( c2 ),
t_color( title_color ),
height( _height ){

	prev = this;
	background = intr;
	head = new RField( false, false, -1, this, -1, NO_SOUND );
	location = head;


	// #define MAX_SHADE_OPT_COLOR 14
	
	shade = new int[ 20 ];
	shade_border = new int[ 20 ];
	shade_opt_color = new int[ MAX_SHADE_OPT_COLOR ];
	Util::blend_palette( shade_opt_color, MAX_SHADE_OPT_COLOR, col1, col2 );
	Util::blend_palette( shade_border, 20, Bitmap::makeColor( 130, 130, 0 ), Bitmap::makeColor( 255, 255, 0 ) );
	Util::blend_palette( shade, 20, Bitmap::makeColor( 240, 240, 0 ), Bitmap::makeColor( 130, 130, 0 ) );
	select = false;
	initialized = false;
	opts = NULL;
	opts_shade = NULL;
}


RMenu::~RMenu() {

	while ( head != NULL ) {
		RField * junk = head;
		head = head->Next();
		delete junk;
	}

	delete[] shade;
	delete[] shade_border;
	delete[] shade_opt_color;

	if ( initialized ){
		endMenu();
	}

}


RField * RMenu::addTitle( string title, Font * rf ) {
	int ta = countNodes();
	RField * junk = new RField_Name( rf, title, false, true, 0, NULL, ta, NO_SOUND );
	RField * current = head;
	while ( current->Next() != NULL ) current = current->Next();
	current->Add( junk );
	return junk;
}


RField * RMenu::addMenu( string title, Font * rf, bool s, int r, RMenu * who, int sound ) {
	int ta = countNodes();
	RField * junk = new RField_Name( rf, title, s, false, r, who, ta, sound );
	RField * current = head;
	while ( current->Next() != NULL ) current = current->Next();
	current->Add( junk );
	return junk;
}

RField * RMenu::addMenu( const Bitmap & look, bool s, int r, RMenu * who, int sound ) {
	int ta = countNodes();
	RField * junk = new RField_Bitmap( look, s, false, r, who, ta, sound );
	RField * current = head;
	while ( current->Next() != NULL ) current = current->Next();
	current->Add( junk );

	return junk;
}


void RMenu::replace( int q, string title, Font * rf, bool s, int r, RMenu * who, int sound ) {
	RField * current = head;
	for ( int z = 0; z < q; z++ ){
		current = current->Next();
	}
	RField * junk = new RField_Name( rf, title, s, false, r, who, current->Place(), sound );
	current->Prev()->Add( junk );
	junk->Add( current->Next() );
	if ( location == current ) location = junk;
	delete current;
	current = head;
}


void RMenu::replaceTitle( int q, string title, Font * rf ) {
	RField * current = head;
	for ( int z = 0; z < q; z++ )
		current = current->Next();
	RField * junk = new RField_Name( rf, title, false, true, 0, NULL, current->Place(), NO_SOUND );
	current->Prev()->Add( junk );
	junk->Add( current->Next() );
	if ( location == current ) location = junk;
	delete current;
	current = head;
}


void RMenu::replace( int q, const Bitmap & look, bool s, int r, RMenu * who, int sound ) {
	RField * current = head;
	for ( int z = 0; z < q; z++ )
		current = current->Next();
	RField * junk = new RField_Bitmap( look, s, false, r, who, current->Place(), sound );
	current->Prev()->Add( junk );
	junk->Add( current->Next() );
	if ( location == current ) location = junk;
	delete current;
	current = head;
}


void RMenu::nextMenu( int q, RMenu * nx ) {
	RField * current = head;
	for ( int z = 0; z < q; z++ ){
		current = current->Next();
	}
	current->setMenu( nx );
}

void RMenu::prevMenu( RMenu * rm ) {
	prev = rm;
}

RMenu * RMenu::Previous() {
	return prev;
}

int RMenu::countNodes() {
	RField * current = head->Next();
	int total = 0;
	while ( current != NULL ) {
		total++;
		current = current->Next();
	}
	return total;
}

void RMenu::spiffy_triangle( const Bitmap & work, int x1, int y1, int color, int * shade, int MAX_SHADE, int dir ) {

	int x2 = x1 + 40;
	int y2 = y1;
	int x3 = ( x1 + x2) / 2;

	for ( int q = 10; q >= 0; q-- ) {
		int y3 = y2 + dir * q;
		int col = (color - q * 2 + MAX_SHADE) % MAX_SHADE;
		work.triangle( x1, y1, x2, y2, x3, y3, shade[ col ] );
	}

}

int RMenu::askPos( string title ) {

	RField * junk = head->Next();
	while ( junk != NULL ) {
		if ( junk->equiv( &title ) ){
			return junk->Place()+1;
		}
		junk = junk->Next();
	}
	return -1;

}

void RMenu::clear() {

	while ( head != NULL ) {
		RField * junk = head;
		head = head->Next();
		delete junk;
	}
	head = new RField( false, false, -1, this, -1, NO_SOUND );
	location = head;

}


bool RMenu::Selected() {

	bool cy = select;
	select = false;
	return cy;

}


void RMenu::Draw( const Bitmap & work, int x, int * yval, int * yshade, int min, int max ) {

	RField * junk = head->Next();
	for ( int q = min; q <= max; q++ ) {
		while( junk->Place() != q ) junk = junk->Next();
		if ( junk->Title() )
			junk->Draw( work, x, yval[q-min], t_color );
		else
			junk->Draw( work, x, yval[q-min], shade_opt_color[yshade[junk->Place()]] );
	}
}


bool RMenu::changed() {
	bool cy = change;
	change = false;
	return cy;
}


void RMenu::init() {

	initialized = true;

	while ( !location->Ok() ) {
		location = location->Next();
		if ( location == NULL ) location = head;
	}

	work.resize( GRAPHICS_X, GRAPHICS_Y );

	/*
	work = create_bitmap( GRAPHICS_X, GRAPHICS_Y );
	if ( !work )
		printf("Could not create proc work\n");
	*/

	background.Blit( work );

	x1 = 0;
	ang = 90;

	col_up = 5;
	col_down = 15;

	opt_max = countNodes();

	change = false;

	opts = new int[ opt_max ];
	opts_shade = new int[ opt_max ];

	field_seen = head->Next();
	keep_y = first_y;
	for ( int q = 0; q < opt_max; q++ ) {
		opts[q] = keep_y;
		if ( keep_y + field_seen->Size() < Util::screen_y ) max_seen = q;
		// keep_y += field_seen->Size()*5/2;
		keep_y += field_seen->Size() * 3 / 2;
		field_seen = field_seen->Next();
	}

	RField * temp = head->Next();
	while ( temp != NULL ) {
		if( temp->Ok() ) opts_shade[temp->Place()] = 0;
		else opts_shade[temp->Place()]=MAX_SHADE_OPT_COLOR-1;
		temp = temp->Next();
	}

	Util::speed_counter = 0;
	k_hold = false;

	min_x = first_x;

	shade_counter = 0;

}


void RMenu::endMenu() {

	initialized = false;
	// destroy_bitmap( work );
	delete[] opts;
	opts = NULL;
	delete[] opts_shade;
	opts_shade = NULL;

}


int RMenu::procMenu( RMenu ** current ) {

	if ( !initialized ) init();

	//while ( !key[KEY_SPACE] && !key[KEY_ENTER] ){

	bool dirty = false;
	while ( Util::speed_counter ) {
		dirty = true;
		Util::speed_counter--;

		ang += 6;
		if ( ang < 0 ) ang += 180;
		if ( ang >= 180 ) ang -= 180;

		if ( ! Keyboard::getAnyKey( Keyboard::DOWN ) && ! Keyboard::getAnyKey( Keyboard::UP ) ){
			k_hold = false;
		}

		if ( Keyboard::getAnyKey( Keyboard::DOWN ) && ! k_hold ) {
			do {
				location = location->Next();
				if ( location == NULL ) location = head->Next();
			} while ( ! location->Ok() );

			location->Selected();
			k_hold = true;
			change = true;
		}
		if ( Keyboard::getAnyKey( Keyboard::UP ) && ! k_hold ) {
			do {
				if ( location != head )
					location = location->Prev();
				if ( location == head ) {
					while ( location->Next() != NULL )
						location = location->Next();
				}
			} while ( ! location->Ok() );
			location->Selected();
			k_hold = true;
			change = true;

		}

		RField * junk = head->Next();
		while ( junk != NULL ) {
			if ( junk->Place() == location->Place() || !junk->Ok() ) {
				if ( opts_shade[junk->Place()] < MAX_SHADE_OPT_COLOR-1 )opts_shade[junk->Place()]++;
			} else  if ( opts_shade[junk->Place()] > 0 )opts_shade[junk->Place()]--;
			junk = junk->Next();

		}

	}

	if ( dirty ) {

		background.Blit( work );

		col_up = ang / 9;
		col_down = 19 - ang / 9;
		x1 = Tsine(ang)*20;

		int real_seen = max_seen/2;
		if ( location->Place() < max_seen/2 ){
			real_seen = location->Place();
		}
		if ( location->Place() >= opt_max - (max_seen / 2 + 1) ){
			real_seen = max_seen - (opt_max - 1 - location->Place());
		}

		ac_y = opts[ real_seen ] + location->Size()/2;
		work.triangle( min_x + 4, ac_y - (int) x1, min_x + 1, ac_y, min_x + 30, ac_y, shade[ col_down ] );
		work.triangle( min_x + 4, ac_y + (int) x1, min_x + 1, ac_y, min_x + 30, ac_y, shade[ col_up ] );

		work.line( min_x+4, ac_y-(int)x1, min_x+30, ac_y, shade_border[ col_up ] );
		work.line( min_x+4, ac_y+(int)x1, min_x+30, ac_y, shade_border[ col_down ] );

		int div2 = max_seen/2;

		int min = location->Place() - div2;
		int max = location->Place() + (max_seen - div2);

		if ( min < 0 ) {
			min = 0;
			max = max_seen;
		}
		if ( max >= opt_max ) {
			max = opt_max-1;
			min = max-max_seen;
		}

		Draw( work, min_x + 50, opts, opts_shade, min, max );

		shade_counter = (shade_counter + 1) % 20;

		if ( max + 1 < opt_max ){
			spiffy_triangle( work, min_x, opts[ max_seen ], shade_counter, shade, 20, 1 );
		}

		if ( min > 0 ){
			spiffy_triangle( work, min_x, opts[ 0 ]+10, shade_counter, shade, 20, -1 );
		}

		work.BlitToScreen();
	}

	//}

	if ( Keyboard::getAnyKey( Keyboard::ENTER, Keyboard::SPACE ) ){
		select = true;

		while ( Keyboard::getAnyKey( Keyboard::SPACE, Keyboard::ENTER ) ){
			Util::YIELD();
		}

		// while ( key[KEY_ENTER] );

		endMenu();

		if ( location->NextMenu() != this ) {
			if ( location->NextMenu() != NULL ) {
				*current = location->NextMenu();
				(*current)->prevMenu( this );
			}  else *current = prev;
		}
	}
	return location->Val();

}
