#ifndef _player_hull_h
#define _player_hull_h

#include "hull.h"
#include "bitmap.h"
#include <vector>

using namespace std;
	
/*
#define MAX_ROTATE 7
#define MAX_ACCESSORY 3
*/
static const int MAX_ROTATE = 7;
static const int MAX_ACCESSORY = 3;

// #define MAX_INTERNAL_DAMAGE 30
static const int MAX_INTERNAL_DAMAGE = 30;

class WeaponObject;

class PlayerHull:public HullObject{
public:
//inherited function
	PlayerHull( const vector< Bitmap * > & pics, int _maxlife,int _maxshield,int _number_of_guns,int _hull_number,ECollide *eb);

	virtual void Draw( const Bitmap & who, int x, int y ); 
	//virtual void Shadow( Bitmap * who, int x, int y ); 
	virtual Bitmap * getShadow();
	virtual double Damage( double much );
	
	virtual int maxGuns();
	virtual WeaponObject ** Guns();
	virtual void giveWeapon( WeaponObject * weap, int num );

	virtual void Moved( double _dx, double _dy, double _ax, double _ay );
	virtual void addSection( SpaceObject * who, Section * onscreen, int x, int y );
	virtual HullObject * copy();

	virtual const int getShield() const;
	virtual void setShields( int s );
	virtual void incShield( int q );
	int getMaxLife();
	int getMaxShield();
	
	virtual ~PlayerHull();

public:
//new functions
	void frameRight();
	void frameLeft();
	void frameStable();

	// virtual void showAttribute( Bitmap * who, int amount, int MAX, int start_x, int offset );
	
	// int max( int q );
	int rank();
	virtual WeaponObject ** Accessories();
	virtual void NextAccessory();
	
protected:
	double shield;

public:
	int frame;
	int cloak;

public:
	virtual void drawGun( const Bitmap & who, int x, int y );
	
	HullObject * rotate[ MAX_ROTATE ];
	HullObject * rotate_damage[ MAX_ROTATE ];
	int MAX_SHIELD;
	int MAX_LIFE;
	int hull_num;	// records which player hull we are using
	int internal_damage; //set to MAX_INTERNAL_DAMAGE when struck to show rotate_damage
	// int * shade_damage; //blended palette for rotate_damage
	int shade_damage[ MAX_INTERNAL_DAMAGE ];

	int current_accessory;
	WeaponObject * accessory[ MAX_ACCESSORY ];
	WeaponObject ** true_guns;
	vector< Bitmap * > pics;
	vector< Bitmap * > pics_shadow;
	// Bitmap ** pics_shadow;
	int animation_pic;
	int max_pics;

};
#endif
