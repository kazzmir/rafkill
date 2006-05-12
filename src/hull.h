#ifndef _hull_h_
#define _hull_h_

#include "bitmap.h"
#include "ebox.h"

class WeaponObject;
class SpaceObject;
class Section;

class HullObject{
public:

	//c = color
	//l = life
	//s = strength
	//num_guns = number of guns
	//dl = drawing plane
	HullObject( Bitmap * _drawBitmap, double _life, double _strength, int num_guns, int level, int _drawing_plane, bool _trans, ECollide * ec );

	//process: determines if point is within hull
	virtual bool Inside( int mx, int my, int ax, int ay );

	//tells the hull it has been moved
	virtual void Moved( double _dx, double _dy, double _ax, double _ay );

	//process: draws hull onto Bitmap
	virtual void Draw( const Bitmap & who, int x, int y );

	virtual Bitmap * getShadow();
	
	//Shadow: draws a shadow
	virtual void Shadow( const Bitmap & who, int x, int y );

	virtual bool hullCollide( ECollide * col, int mx, int my, int ax, int ay );
	//process: determines if hull is within check->hull
	virtual bool Collide( int mx, int my, SpaceObject * check );

	//process: returns amount of hull structural integrity
	double GetLife();

	//does something when collided with something else
	virtual void Collided();

	//process: returns whether or not hull can be hit by bullets
	bool Translucent();

	virtual inline int getHeight(){
		if ( myBitmap ) return myBitmap->getHeight();
		if ( collide ) return collide->getHeight();
		return 0;
	}

	virtual inline int getWidth(){
		if ( myBitmap ) return myBitmap->getWidth();
		if ( collide ) return collide->getWidth();
		return 0;
	}

	inline ECollide * getCollide() const{
		return collide;
	}

	//returns how much damage hull should do
	virtual double Hurt();

	//allows hull to change how much damage it is going to take
	virtual double Damage( double much );

	//forces the hull to take so much damage
	virtual void takeDamage( double r );

	//adds current object to the section
	virtual void addSection( SpaceObject * who, Section * onscreen, int x, int y );

	//returns the guns the hull contains
	virtual WeaponObject ** Guns();

	//gives us a new weapon
	virtual void giveWeapon( WeaponObject * weap, int num );

	virtual void eraseWeapon( int num );

	//returns the maximum number of guns the hull can contain
	//usually a constant as guns is set to a specific number
	//in the constructor
	virtual int maxGuns();

	//returns crash. sets crash to false
	bool haveBeenHit();

	//sets the current life according to the level
	void setLife( double zx );

	inline int getLife(){
		return (int)life;
	}

	//debug stuff
	// void debug( Bitmap * work, int x, int y );

	//returns a copy of this hull
	virtual HullObject * copy();

	//virtual destructor
	virtual ~HullObject();

	bool crash;
	int color;
	double life;
	double original_life;
	bool trans;

	double strength;

	int drawNum;
	int drawLevel;

protected:
	Bitmap * myBitmap; 
	Bitmap * Shadow_Bitmap;
	WeaponObject ** guns;
	ECollide * collide;

public:

	int max_guns;

	double dx, dy;

};

#endif
