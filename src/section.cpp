#include "section.h"
#include "spaceobj.h"
// #include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std;

Section::Section():
section_y( 0 ),
section_x( 0 ){
// internal_list( 0 ) {

	/*
	for ( int q = 0; q < MAX_SECTION_LIST; q++ )
		container_list[q] = new vector< SpaceObject * >();
	*/

	current_list = lists.begin();

}


void Section::add( SpaceObject * who, int x, int y ) {

	y += MIN_SECTION_Y;
	y /= MAX_SECTION_OBJ_Y;
	x += MIN_SECTION_X;
	x /= MAX_SECTION_OBJ_X;

	if ( y >= 0 && y < MAX_SECTION_LIST_Y && x >= 0 && x < MAX_SECTION_LIST_X ) {

		//for ( int q = 0; q < container_list[y]->size(); q++ )
		//	if ( (*container_list[y])[q] == who ) return;

		// container_list[y]->push_back( who );
		container_list[y][x].push_back( who );

		lists[y*10+x] = &container_list[y][x];
	}

}


void Section::dispose( SpaceObject * who ) {

	for ( int y = 0; y < MAX_SECTION_LIST_Y; y++ )
		for ( int x = 0; x < MAX_SECTION_LIST_X; x++ ){
			vector< SpaceObject * > & vec = container_list[y][x];
			for ( vector< SpaceObject * >::iterator it = vec.begin(); it != vec.end(); ){
				if ( *it == who )
					it = vec.erase( it );
				else ++it;
			}
		}
	/*
	for ( int q = 0; q < MAX_SECTION_LIST_Y; q++ ) {

		for ( vector< SpaceObject * >::iterator it = container_list[q]->begin();
		it != container_list[q]->end(); ) {
			if ( *it == who )
				it = container_list[q]->erase( it );
			else ++it;
		}

	}
	*/

}


void Section::print() {

	/*
	printf("Info for %p\n", this );
	for ( int q = 0; q < MAX_SECTION_LIST; q++ ){

		printf("Container %d\n", q );
		Iterator * i = container_list[q]->iterator();

		while ( !i->isEmpty() ){
			printf("[%p]", i->getObj() );
			i->Next();
		}

	delete i;
	printf("\n");

	}
	printf("End info for %p\n", this );
	*/

}


void Section::reset() {
	// internal_list = 0;
	section_y = 0;
	section_x = 0;
	current_list = lists.begin();
}


int Section::spacerY() {
	return MAX_SECTION_OBJ_Y;
}

int Section::spacerX() {
	return MAX_SECTION_OBJ_X;
}

void Section::clear() {

	/*
	for ( int q = 0; q < MAX_SECTION_LIST; q++ )
		container_list[q]->clear();
	internal_list = 0;
	*/
	cout<<"CLEARARARA"<<endl;

}


vector< SpaceObject * > * Section::getNext() {

	/*
	if ( section_x < MAX_SECTION_LIST_X && section_y < MAX_SECTION_LIST_Y ){
		vector< SpaceObject * > * ret = &container_list[section_y][section_x];
		section_x++;
		if ( section_x >= MAX_SECTION_LIST_X ){
			section_x = 0;
			section_y++;
		}

		return ret;
	}
	*/
	if ( current_list == lists.end() ) return NULL;
	vector< SpaceObject * > * ret = (*current_list).second;
	current_list++;
	return ret;
	return NULL;
	/*
	if ( internal_list < MAX_SECTION_LIST ) {
		internal_list++;
		return container_list[ internal_list-1 ];
	}
	return NULL;
	*/
}


Section::~Section() {
	// clear();
	/*
	for ( int q = 0; q < MAX_SECTION_LIST; q++ )
		delete container_list[q];
		*/
}
