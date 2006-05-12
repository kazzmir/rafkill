#include "logic.h"
#include "spaceobj.h"
#include "level.h"
#include "explode.h"
#include "section.h"
#include "sound.h"
#include "defs.h"
#include "group.h"

#include <iostream>

/*
#include "hull.h"
#include "ebox.h"
*/

#ifndef debug
#define debug std::cout<<"File: "<<__FILE__<<" Line: "<<__LINE__<<std::endl;
#endif

Logic::Logic(){

	for ( int q = 0; q < MAX_EXPL; q++ ){
		expl[q] = NULL;
	}

	// objects.push_back( new SpaceObject( 320, 100, 0, 0, new HullObject( new Bitmap( Util::getDataSprite( 187 ) ), 50, 10, 1, 50, 10,false, new ECollide( Util::getDataSprite( 187 ) ) ), NULL, PLANE_AIR, TEAM_ENEMY ) );

}

int Logic::runCycle( SpaceObject * player, LevelCreator * level ){

	Section section;

	if ( player != NULL ){
		objects.push_back( player );
	}

	/* this has to go here */
	HandleExplosion();

	double x = 0;
	if ( level ){
		level->create( &objects, 1, x );
	}

	handleSpace( &objects, &section );
	if ( player != NULL ){
		enforceUniverse( player );
	}
	clearCollide( &objects );
	checkCollision( &section, player, SND_SUSTAIN, 12 );
	DeleteSpace( &objects, &section, player, level );

	for ( vector< SpaceObject * >::iterator it = objects.begin(); it != objects.end(); ){
		if ( *it == player ){
			it = objects.erase( it );
		} else {
			++it;
		}
	}

	return 0;
}

Logic::~Logic(){
	for ( int q = 0; q < MAX_EXPL; q++ ){
		if ( expl[q] ){
			delete expl[q];
			expl[q] = NULL;
		}
	}

	for ( vector< SpaceObject * >::iterator it = objects.begin(); it != objects.end(); ++it ){
		delete *it;
	}

	objects.clear();
}
	
vector< SpaceObject * > * Logic::getObjects(){
	return &objects;
}

ExplosionClass ** Logic::getExplode(){
	return expl;
}

int Logic::maxExplode(){
	return MAX_EXPL;
}

void Logic::HandleExplosion() {
	for ( int q = 0; q < MAX_EXPL; q++ ){
		if( expl[q] != NULL ){
			if ( expl[q]->update() ) {
				delete expl[q];
				expl[q] = NULL;
			}
		}
	}
}

void Logic::enforceUniverse( SpaceObject * player ){

	if ( player->getX() + player->getMaxX()/2 > Util::screen_x )
		player->setX( Util::screen_x - player->getMaxX()/2 );
	if ( player->getX() - player->getMaxX()/2 < 0 )
		player->setX( player->getMaxX()/2 );
	if ( player->getY() + player->getMaxY()/2 > Util::screen_y )
		player->setY( Util::screen_y - player->getMaxY()/2 );
	if ( player->getY() - player->getMaxY()/2 < 0 )
		player->setY( player->getMaxY()/2 );

}

bool Logic::outOfBounds( SpaceObject * who ){

	int x = who->getX();
	int y = who->getY();

	if ( x < -200 || x > Util::screen_x + 200 || y < -500 || y > Util::screen_y+200 )
		return true;
	return false;

}

void Logic::handleSpace( vector< SpaceObject * > * mv, Section * onscreen ) {

	vector< SpaceObject * > Ammo;
	for ( vector< SpaceObject * >::iterator it = mv->begin(); it != mv->end(); ) {
		if ( *it == NULL ){
			cerr << "Object = NULL. Skipping" << endl;
			it = mv->erase( it );
			continue;
		}

		(*it)->MoveMe( &Ammo, mv, onscreen );

		// if ( (*it)->MoveMe( &Ammo, mv, onscreen, global_snd ) ) {
		if ( outOfBounds( *it ) && (*it)->Destroyable() ){
			SpaceObject * del = *it;
			it = mv->erase( it );
			delete del;
		} else ++it;
	}
	vectorAdd( mv, &Ammo );

	for ( vector< SpaceObject * >::iterator it = mv->begin(); it != mv->end(); ++it ){
		(*it)->addSection( onscreen );
	}
}

void Logic::vectorAdd( vector< SpaceObject * > * stable, vector< SpaceObject * > * state ) {

	for ( vector< SpaceObject * >::iterator it = state->begin(); it != state->end(); it++ ){
		stable->push_back( *it );
	}

}

void Logic::clearCollide( vector< SpaceObject * > * contain ) {

	for ( vector< SpaceObject * >::iterator it = contain->begin(); it != contain->end(); ++it ) {
		(*it)->clearCollide();
	}

}

void Logic::DeleteSpace( vector< SpaceObject *> * objs, Section * sec, const SpaceObject * _player, LevelCreator * level ) {

	// extra vector to store special objects
	vector< SpaceObject * > objs_special;
	
	for ( vector< SpaceObject * >::iterator it = objs->begin(); it != objs->end(); ) {

		if ( (*it)->getLife() <= 0 && (*it)->Destroyable() ){

			/* If object can become a powerup, it may in fact do so
			 * Can only become a powerup if it was the last in its group
			 * which is known when group->size() is 1.
			 */
			if ( (*it)->powerUp() ) {
				if ( (*it)->getGroup() != NULL ) {
					if ( (*it)->getGroup()->size() == 1 ){
						if ( Util::rnd(3)  ) {
							int x = (*it)->getX();
							int y = (*it)->getY();

							// The following line used to cuase a bug
							// objs->push_back( level->special(x,y,_player) );

							objs_special.push_back( level->special(x,y,_player) );
						}
					}
				}
			}

			SpaceObject * del = *it;
			it = objs->erase( it );
			delete del;

		} else ++it;

	}

	vectorAdd( objs, &objs_special );
}

void Logic::checkCollision( Section * fight, SpaceObject * take, int sound, int vol ) {

	/* Reset section lists. Look at section.cpp to see why this is important */
	fight->reset();

	vector< SpaceObject * > * fight_space = fight->getNext();

	int total = 0;
	while ( fight_space != NULL ) {

		// Loop through bad objects next
		for ( vector< SpaceObject * >::iterator fight_it = fight_space->begin(); fight_it != fight_space->end(); fight_it++ ) {

			for ( vector< SpaceObject * >::iterator good_it = fight_it+1; good_it != fight_space->end(); good_it++){

				SpaceObject * g_use = *good_it;
				SpaceObject * f_use = *fight_it;

				// First test to see if badobject life is less than 0
				// and if good object has already collided with bad object
				++total;

				/*
				cout << "F: " << f_use << " G: " << g_use << endl;
				cout << "F-hit: " << f_use->CanbeHit( g_use ) << " G-hit: " << g_use->CanbeHit( f_use ) << endl;
				*/
				if ( (f_use->CanbeHit(g_use) || g_use->CanbeHit(f_use)) && f_use->getLife() > 0 && !g_use->haveCollide( f_use ) ){
					if ( g_use->Collide( f_use ) || f_use->Collide( g_use ) ) { 
						// Util::play_sound( Util::global_snd, sound, vol );
						Util::playSound( sound, vol );

						float fhurt = f_use->Hurt();
						float ghurt = g_use->Hurt();

						if ( g_use->Damage( fhurt ) )
							g_use->Died( take, expl, MAX_EXPL );
						if ( f_use->Damage( ghurt ) ) 
							f_use->Died( take, expl, MAX_EXPL );

						// Let both objects know they collided with something
						g_use->Collided( f_use, expl, MAX_EXPL );
						f_use->Collided( g_use, expl, MAX_EXPL );

						g_use->addCollide( f_use );
						f_use->addCollide( g_use );

						//g_use->addCollide( f_use );
						//f_use->addCollide( g_use );
					}
				}//if

			}			  //for fight

		}				  //for good

		fight_space = fight->getNext();

	}					  //while
}
