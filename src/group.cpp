#include "group.h"
#include "spaceobj.h"
#include <vector>
#include <iostream>

using namespace std;

/* Group:
 * Creates a new group with a y coordinate to be used for knowing when to
 * put the group into the game.
 */
Group::Group( const int _y ):
y( _y ) {

	// list = new vector< SpaceObject * >;

}

/* pos:
 * Returns the y coordinate of the group
 */
/*
int Group::pos() const{
	return y;
}
*/

/* add:
 * Adds another spaceobject to this group
 */
void Group::add( SpaceObject * who ) {
	list.push_back( who );
}


/* drop:
 * Removes a spaceobject from this group if it exists
 */
void Group::drop( SpaceObject * who ) {
	for ( vector< SpaceObject *>::iterator it = list.begin(); it != list.end(); ){
		if ( *it == who ) {
			it = list.erase( it );
			return;
		} else it++;
	}
}

/* size:
 * Returns number of spaceobjects currently stored in this group
 */
int Group::size() const{
	return list.size();
}


/* members:
 * Returns a list of the objects that this group stores
 */
const vector< SpaceObject * > * Group::members() const{
	return &list;
}

/* ~Group:
 * Destructor. Deletes all objects stored in this group.
 */
Group::~Group() {
	for ( vector< SpaceObject * >::iterator it = list.begin(); it != list.end(); it++ ){
		SpaceObject * del = *it;
		/* remove the object from this group */
		del->Independent();
		// it = list.erase( it );
		/* then delete the object */
		delete del;
	}
	// delete list;
	
	list.clear();
}

