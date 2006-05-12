#ifndef _game_logic_h_
#define _game_logic_h_

#include <vector>

using namespace std;

class SpaceObject;
class LevelCreator;
class Section;
class ExplosionClass;

#define MAX_EXPL 100

class Logic{
public:

	Logic();
	~Logic();

	int runCycle( SpaceObject * player, LevelCreator * level );

	vector< SpaceObject * > * getObjects();
	ExplosionClass ** getExplode();
	int maxExplode();

protected:
	
	void handleSpace( vector< SpaceObject * > * mv, Section * onscreen );
	void checkCollision( Section * fight, SpaceObject * take, int sound, int vol );
	void enforceUniverse( SpaceObject * player );
	void HandleExplosion();
	void DeleteSpace( vector< SpaceObject *> * objs, Section * sec, const SpaceObject * _player, LevelCreator * level );
	void clearCollide( vector< SpaceObject * > * contain );
	bool outOfBounds( SpaceObject * who );
	void vectorAdd( vector< SpaceObject * > * stable, vector< SpaceObject * > * state );

protected:
	ExplosionClass * expl[ MAX_EXPL ];
	vector< SpaceObject * > objects;

};

#endif
