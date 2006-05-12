#ifndef _move_h
#define _move_h

#include "spaceobj.h"
#include <vector>

using namespace std;

//Most basic, just move whatever dx and dy are
class Move{
public:
	Move( double _dx, double _dy );

	/*
	virtual void setP( int & ax, int & ay, double & vx, double & vy );
	virtual void setD( double _dx, double _dy );
	*/
	virtual void action( const vector< SpaceObject * > * fight, int x, int y, double & sdx, double & sdy );
	/*
	virtual double DX();
	virtual double DY();
	virtual double Accel_X();
	virtual double Accel_Y();
	*/

protected:

	// virtual bool MoveReal();
	/*
	virtual int AX();
	virtual int AY();
	*/

protected:
	/*
	int * actualx;
	int * actualy;
	double * virtualx;
	double * virtualy;
	*/
	const double o_dx;
	const double o_dy;
	/*
	double dx, dy;
	*/
	double accel_x, accel_y;
	
};

//Move from side to side
class MoveHorizontal: public Move{
public:
	MoveHorizontal( double _dx, double _dy );
	virtual void action( const vector< SpaceObject * > * fight, int x, int y, double & sdx, double & sdy );
protected:
	int dir;
};

//Heads for the player
class MoveMine: public Move{
public:

	MoveMine( double _dx, double _dy );
	virtual void action( const vector< SpaceObject * > * fight, int x, int y, double & sdx, double & sdy );
protected:
	int fx, fy;
	double sx, sy;
};

//Moves in circles
class MoveAngular: public Move{
public:
	MoveAngular( double _dx, double _dy );
	virtual void action( const vector< SpaceObject * > * fight, int x, int y, double & sdx, double & sdy );
protected:
	int ang;
	int dir;
};

//Moves down and slowly increases its positive dx speed
class MoveSwingRight: public Move{
public:
	MoveSwingRight( double _dx, double _dy );
	virtual void action( const vector< SpaceObject * > * fight, int x, int y, double & sdx, double & sdy );
};

//Move down and slowly increases its negative dx speed
class MoveSwingLeft: public Move{
public:
	MoveSwingLeft( double _dx, double _dy );
	virtual void action( const vector< SpaceObject * > * fight, int x, int y, double & sdx, double & sdy );
};

//Slowly increases its dy speed
class MoveSwingDown: public Move{
public:
	MoveSwingDown( double _dx, double _dy );
	virtual void action( const vector< SpaceObject * > * fight, int x, int y, double & sdx, double & sdy );
};

//Moves from side to side in a sine wave motion.
class MoveSine: public Move{
public:
	MoveSine( double _dx, double _dy );
	virtual void action( const vector< SpaceObject * > * fight, int x, int y, double & sdx, double & sdy );

protected:
	int ang;
};

class MoveCircle_Player: public Move{
public:
	MoveCircle_Player( double _dx, double _dy );
	virtual void action( const vector< SpaceObject * > * fight, int x, int y, double & sdx, double & sdy );

protected:
	int ang;
	int find_circle;
};

#endif
