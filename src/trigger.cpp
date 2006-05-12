#include "trigger.h"

/* Trigger:
 * Constructor. Sets things and whatnot. Not very exciting.
 */
trigger::trigger( char * info, int size_data, int type, int xv, int yv ) {
	data = info;
	size_d = size_data;
	id = type;
	loc_x = xv;
	loc_y = yv;
}

/* kind:
 * Returns a number that determines what kind of trigger this is.
 * Those numbers are defined elsewhere.
 */
int trigger::kind() {
	return id;
}

/* kill:
 * Forces trigger to die.
 */
void trigger::kill() {
	id = -1;
}


/* size:
 * Returns the size of the data the trigger is storing
 */
int trigger::size() {
	return size_d;
}


/* CX:
 * Returns the X coordinate of the trigger
 */
int trigger::CX() {
	return loc_x;
}


/* CY:
 * Returns the Y coordinate of the trigger
 */
int trigger::CY() {
	return loc_y;
}


/* get:
 * Returns the data stored by the trigger.
 */
void * trigger::get( void * helper ) {
	return data;
}

/* ~Trigger:
 * Deletes data
 */
trigger::~trigger() {
	if ( data )
		delete[] data;
}
