#include "rfield.h"
#include "rmenu.h"
#include "defs.h"
#include "font.h"
#include <string.h>
#include "bitmap.h"

RField::RField( bool selectable, bool perm, int return_val, RMenu * who, int number, int sound_ ):
select( selectable ),
ret( return_val ),
num( number ),
title( perm ),
next( NULL ),
prev( NULL ),
menu_next( who ),
sound( sound_ ){
}


void RField::Add( RField * rf ) {
	next = rf;
	if ( rf != NULL )
		rf->prev = this;
}


void RField::setMenu( RMenu * nx ) {
	menu_next = nx;
}


bool RField::Ok() {
	return select;
}

bool RField::Title() {
	return title;
}

void RField::Selected() {

	if ( sound != -1 ){
		Util::playSound( sound, 255 );
	}

}

int RField::Size() {
	return 0;
}


void RField::Draw( const Bitmap & work, int x, int y, int col ) {
}

bool RField::equiv( void * obj ) {
	return false;
}

int RField::Val() {
	return ret;
}


RField * RField::Next() {
	return next;
}


RField * RField::Prev() {
	return prev;
}


int RField::Place() {
	return num;
}


RMenu * RField::NextMenu() {
	return menu_next;
}


RField::~RField() {
}

//**//
RField_Name::RField_Name( Font * f_font, string name, bool selectable, bool perm, int return_val, RMenu * who, int number, int sound ):
RField( selectable, perm, return_val, who, number, sound ) {
	handle = name;
	field_font = f_font;
}

bool RField_Name::equiv( void * obj ) {
	return handle == *(string *)obj;
}

int RField_Name::Size() {
	return field_font->getHeight();
}

void RField_Name::Draw( const Bitmap & work, int x, int y, int col ) {
	work.printf( x, y, col, this->field_font, this->handle );
}

RField_Name::~RField_Name() {
	//delete[] handle;
	// free( handle );
}

RField_Bitmap::RField_Bitmap( const Bitmap & look, bool selectable, bool perm, int return_val, RMenu * who, int number, int sound ):
RField( selectable, perm, return_val, who, number, sound ) {
	scene =  look;
}

bool RField_Bitmap::equiv( void * obj ) {
	return false;
}

int RField_Bitmap::Size() {
	return scene.getHeight();
}

void RField_Bitmap::Draw( const Bitmap & work, int x, int y, int col ) {
	scene.draw( x, y, work );
}

RField_Bitmap::~RField_Bitmap() {
}
