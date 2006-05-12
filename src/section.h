#ifndef _section_h
#define _section_h

class SpaceObject;

using namespace std;

#include <vector>
#include <map>

#define MAX_SECTION_LIST_Y 20
#define MAX_SECTION_OBJ_Y 30
#define MIN_SECTION_Y 100

#define MAX_SECTION_LIST_X 40
#define MAX_SECTION_OBJ_X 40
#define MIN_SECTION_X 100

class Section{
public:

	Section();

	void add( SpaceObject * who, int x, int y );
	void reset();
	int spacerY();
	int spacerX();
	void clear();
	
	vector< SpaceObject * > * getNext();

	void dispose( SpaceObject * who );
	
	//debug
	void print();

	~Section();

protected:
	//vector< SpaceObject * > container_list[ MAX_SECTION_LIST ];
	// vector< SpaceObject * > * container_list[ MAX_SECTION_LIST ];
	vector< SpaceObject * > container_list[ MAX_SECTION_LIST_Y ][ MAX_SECTION_LIST_X ];
	map< int, vector< SpaceObject * > * > lists;
	map< int, vector< SpaceObject * > * >::iterator current_list;
	int section_y, section_x;
	// int internal_list;

};

#endif
