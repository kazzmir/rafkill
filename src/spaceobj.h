#ifndef _SpaceObject_h_
#define _SpaceObject_h_

#include <vector>
#include "bitmap.h"

using namespace std;

class WeaponObject;
class ExplosionClass;
class Section;
class ECollide;
class Engine;
class Group;
class Vector;
class HullObject;

class SpaceObject{
public:

	SpaceObject( int startX, int startY, double velocityX, double velocityY, HullObject * mhull, Group * _group, int plane, int alignment );

	// copy constructor, but should never be run.
	SpaceObject( const SpaceObject & s );

	//Hitme: calls hull->Inside( x, y, ax, ay )
	virtual bool HitMe( int ax, int ay );

	//Collide: determines if have collided with another object
	virtual bool Collide( SpaceObject * check);

	//Damage: decreases life returns true if 0 or less
	virtual bool Damage( double much );

	//Hurt: returns amount of damage object does when colliding with 
	//another object
	virtual double Hurt();

	//Draw: if plane == g then draw self
	virtual void Draw( const Bitmap & less, ExplosionClass ** _expl, int MAX_EXPLR, int g, int offset )const;

	//Shadow: draw a shadow the same way as the Draw() method
	virtual void Shadow( const Bitmap & less, int g, int offset ) const;

	// returns true if this object can be destroyed in the universe
	// basically only playerobj cannot be destroyed
	virtual bool Destroyable() const;

	//PowerUp: determines whether or not ship should turn into a powerup or money
	virtual bool powerUp();

	//GiveHull: replace old hull with hnew
	virtual void giveHull( HullObject * hnew );

	// push the coordinates onto mini-stack
	virtual void savePosition();

	// pop the coordinates from the mini-stack
	virtual void restorePosition();

	// true for powerups
	virtual bool isSpecial() const;

	// true for ships that can get powerups
	virtual bool acceptSpecial() const;

	virtual Group * getGroup();
	
	// ammo - array of pointers to bullets
	// fight - array of pointers to ships
	virtual void MoveMe( vector< SpaceObject * > * Ammo, const vector< SpaceObject * > * fight, Section * onscreen );

	/* the absolute last method called on this object.
	 * gives this object a chance to spawn new objects
	 */
	virtual void destroy( vector< SpaceObject * > * objects );

	//process: changes check according to death of object
	virtual void Died(SpaceObject * check,ExplosionClass ** explr, int ME );

	//process: increments objects score
	virtual void IncScore( int j );
        virtual void addPowerBonus(double value);

	//returns hull->drawlevel
	virtual int lookPlane() const;

	//process: returns whether or not object can be hit
	virtual bool CanbeHit( const SpaceObject * ht ) const;

	//forces object to have no group
	virtual void Independent();
	
	//gives the hull a weapon at slot num
	virtual void giveWeapon( WeaponObject * weap, int num );

	virtual void eraseWeapon( int num );

	virtual bool hullCollide( ECollide * col, int x, int y );
	virtual void Collided( SpaceObject * who, ExplosionClass ** explr, int M_EX );

	//adds an object to the collide list
	virtual void addCollide( SpaceObject * who );

	//check to see if the object is in the collide list
	virtual bool haveCollide( const SpaceObject * who );

	//clears the collide list
	virtual void clearCollide();

	//destructor
	virtual ~SpaceObject();

	//returns an exact copy of this object
	virtual SpaceObject * copy();

	//draws self on the radar
	virtual void Radar( const Bitmap & rad ) const;

	virtual inline void setX( int x ){
		actualx = x;
		virtualx = x;
	}

	virtual inline void setY( int y ){
		actualy = y;
		virtualy = y;
	}

	virtual inline void setX( double x ){
		actualx = (int)x;
		virtualx = x;
	}

	virtual inline void setY( double y ){
		actualy = (int)y;
		virtualy = y;
	}

	inline void setOffsetX( int x ){
		offset_x = x;
	}

	inline void setOffsetY( int y ){
		offset_y = y;
	}

	inline int getOffsetX(){
		return offset_x;
	}

	inline int getOffsetY(){
		return offset_y;
	}
		
	
	virtual void setDX( double x );
	virtual void setDY( double y );
	virtual void setAccelX( double x );
	virtual void setAccelY( double y );
	virtual void setScore( int s );
	virtual void setStrength( int s );
	virtual void setPlane( int p );
	virtual void setAlignment( int a );
	
	virtual HullObject * getHull() const; 
	
	//return dx and dy respectively
	virtual double getDX();
	virtual double getDY();
	
	//return accelx and accely respectively
	virtual double getAccelX();
	virtual double getAccelY();
	
	//returns alignment
	virtual inline const int getTeam() const{
		return alignment;
	}
	
	//process: returns hull->life

	virtual int getMaxX();
	virtual int getMaxY();
	
	inline int getX() const{
		return actualx + offset_x;
	}

	inline int getY() const{
		return actualy + offset_y;
	}

	inline double getVX() const{
		return virtualx;
	}

	inline double getVY() const{
		return virtualy;
	}

	virtual inline int getScore() const{
		return score;
	}

	virtual inline int getStrength(){
		return str;
	}

	virtual inline int getPlane(){
		return plane;
	}

	virtual inline int getAlignment(){
		return alignment;
	}

public:

	// non-overridable methods
	void addSection( Section * onscreen );
	
	// applies dx, dy to coordinates
	void MoveReal();

	// returns life
	double getLife() const;

	// set virtualx, virtualy, actualx, actualy
	void SetCoordXY( int ax, int ay );

private:

	int actualx, actualy;	// position in integer format
	int old_x, old_y;
	double virtualx, virtualy; // position in double format
	double dx, dy; // velocity 
	double accel_x, accel_y; //acceleration

	int save_ax, save_ay;
	double save_vx, save_vy;

protected:
	int score;
	int str;

	// offset_x and offset_y alter getX() and getY()
	// a hack? maybe
	int offset_x, offset_y;

	int plane;
	int alignment;

	HullObject * hull;
	Group * my_group;

protected:
	vector< SpaceObject * > collide_list;

};

#endif
