#ifndef _player_object_h
#define _player_object_h

#include "shipobj.h"
#include "booster.h"
#include "bitmap.h"
#include <map>

class SpaceObject;
class HullObject;
class WeaponObject;
class Section;

struct input{
	double dx, dy;
	bool shoot;
	bool change_weapons;
};

class PlayerObject:public ShipObject{
public:
	PlayerObject(int qx, int qy, int _difficulty, HullObject * hnew);
	virtual void MoveMe( vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight,Section * onscreen );

	virtual void Draw( const Bitmap & less, ExplosionClass ** _explr, int MAX_EXPLR, int g, int offset ) const;

	virtual bool powerUp();
	virtual int getDifficulty();
	virtual void setDifficulty( int d );
	virtual int getLevel() const;
	virtual void setLevel( int s );
	
	virtual bool Destroyable() const;

	virtual bool acceptSpecial() const;
	virtual void Radar( const Bitmap & rad )const;

	void idleGuns( vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );
	void shootGuns( vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight );

	virtual ~PlayerObject();
	
	void Inertia( double & d );

	void setControl( bool a );

	/* returns a map from a weapon to the power of the weapon */
	std::map<WeaponObject*,int> gunStrengths();

	int hull_num;

private:
	//process: slows object down
	
	//process: forces x and y to be within screen limitations
	// void CheckXY();

	void userInput( const vector< SpaceObject * > * fight, vector< SpaceObject * > * Ammo );
	struct input keyboardInput();
	struct input mouseInput();
	struct input joyInput();
	
	//process: sets dx=fx, dy=fy
	void MoveD( double & d, double f_max );
	
	int difficulty;

	int last_dir;
	int change_frame;
	bool holding_accessory;
	int * shade;
	int shade_color;
	Booster engine;

	bool user_control;

	int level;

	// bool key_UP, key_DOWN, key_LEFT, key_RIGHT, key_SHOOT, key_ACCESSORY;
};

#endif
