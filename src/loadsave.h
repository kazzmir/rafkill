#ifndef _loadsave_h
#define _loadsave_h

class SpaceObject;
int savePlayer( SpaceObject * player, int game_slot );
SpaceObject * loadPlayer( int game_slot );

#endif
