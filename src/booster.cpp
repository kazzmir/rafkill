#include "booster.h"
#include "bitmap.h"
#include "defs.h"

#define MAX_BOOSTER_SHADE 13

PixelList::PixelList( int ax, int ay, int l, PixelList * nx ) {
	x = ax;
	y = ay;
	next = nx;
	life = l;
}

int PixelList::Update(){
	life++;
	return life;
}

void PixelList::Draw( const Bitmap & work, int * shade, int offset ) const{
	// circlefill( work, x, y+offset, 1, shade[ life ] );
	work.circleFill( x, y+offset, 1, shade[ life ] );
}


Booster::Booster() {

	shade = new int[ MAX_BOOSTER_SHADE ];
	Util::blend_palette( shade, MAX_BOOSTER_SHADE*2/3, Bitmap::makeColor(244,220,12), Bitmap::makeColor(237,53,42) );
	Util::blend_palette( shade+MAX_BOOSTER_SHADE*2/3, (MAX_BOOSTER_SHADE-MAX_BOOSTER_SHADE*2/3), Bitmap::makeColor(237,53,42), Bitmap::makeColor(83,6,0) );
	head = new PixelList(0,0,0,NULL);

}


void Booster::add( int x, int y) {

	PixelList * temp = new PixelList( x, y, 0, head->next );
	head->next = temp;

}


void Booster::Draw( const Bitmap & work, int offset ) const{

	PixelList * cur = head;
	while ( cur->next != NULL ) {
		cur->next->Draw( work, shade, offset );
		cur = cur->next;

		/*
		if ( cur->next->Draw(work,shade,offset) >= MAX_BOOSTER_SHADE ) {
			PixelList * dump = cur->next;
			cur->next = cur->next->next;
			delete dump;
		} else cur = cur->next;
		*/
	}

}

void Booster::Update(){
	PixelList * cur = head;
	while ( cur->next != NULL ) {
		if ( cur->next->Update() >= MAX_BOOSTER_SHADE ) {
			PixelList * dump = cur->next;
			cur->next = cur->next->next;
			delete dump;
		} else cur = cur->next;
	}
}

Booster::~Booster() {
	delete shade;
	PixelList * cur = head;
	while ( cur != NULL ) {
		PixelList * dump = cur;
		cur = cur->next;
		delete dump;
	}

}
