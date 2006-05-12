/*
 * Wormhole effect
 * by Jon Rafkind
 * email: workmin@ccs.neu.edu
 *
 * last modifed December 2, 2002 
 * 
 * You are free to use this code for whatever purpose you like.
 * No gaurantee that the program will not destroy your monitor, computer,
 * dog, or marriage.
 * 
 */

#ifndef _wormhole_h
#define _wormhole_h

#include <stdlib.h>
#include <time.h>
#include "defs.h"
#include "bitmap.h"
#include <math.h>
#include "trigtable.h"
#include "rgbhandle.h"
#include <vector>

using namespace std;

#define WORM_MOVE 9.3
#define _si_ 1000
#define MAX_STAR 1500
#define Z_SPEED 9
#define MAX_Z 550

class StarClass{
public:
	StarClass( const int x, const int y, const int z, const int mx, const int my ):
		actualx( x ),
		actualy( y ),
		cx( mx ),
		cy( my ),
		Z( z ){
			ReCalc();
		}

	int GetZ(){
		return Z;
	}

	int GetX(){
		return virtualx;
	}

	int GetY(){
		return virtualy;
	}

	void CalcX(){
		if ( Z <= 0 )
			virtualx = _si_ * actualx / cx;
		else
			virtualx = _si_ * actualx / Z + cx;
	}

	void CalcY(){
		if ( Z <= 0 )
			virtualy = _si_ * actualy / cy;
		else
			virtualy = ( _si_ * actualy ) / Z + cy;
	}

	void ReCalc(){
		CalcX();
		CalcY();
	}

	bool Update(){

		Z-=Z_SPEED;
		return ( Z <= 0 || !inbox() );
	}

	bool inbox(){
		return ( virtualx > 0 && virtualx < GRAPHICS_X &&
			virtualy > 0 && virtualy < GRAPHICS_Y );
	}

protected:
	int actualx;
	int actualy;
	int virtualx;
	int virtualy;
	int cx;
	int cy;
	int Z;
};

class StarLine{
public:

	StarLine( int scale, int mx, int my ){
		int qz = MAX_Z;
		int ang = Util::rnd(360);
		for ( int q = 0; q < 2; q++ )
			star[q] = new StarClass( 
			(int)(Tcos(ang)*scale),
			(int)(Tsine(ang)*scale),
			qz-q*(Util::rnd(6)+4), mx, my ); 
	}

	StarLine( int scale, int mx, int my, int ang, int qz ){
		for ( int q = 0; q < 2; q++ )
			star[q] = new StarClass(
			(int)(Tcos(ang)*scale),
			(int)(Tsine(ang)*scale),
			qz-q*(Util::rnd(5)+3), mx, my );
	}

	bool Update( ){

		bool cy = false;
		for ( int q = 0; q < 2; q++ )
			cy = cy || star[q]->Update();
		return cy;
	
	}

	void Draw( const Bitmap & work , int * shade, int max_shade ){
		for ( int q = 0; q < 2; q++ ){
			star[q]->ReCalc();
		}
		int ncolor = (int)( (double)star[0]->GetZ() * (double)(max_shade-1) / (double)MAX_Z);
		work.line( star[0]->GetX(), star[0]->GetY(), star[1]->GetX(), star[1]->GetY(), shade[ncolor]);
	}

	~StarLine(){
		for ( int q = 0; q < 2; q++ )
			delete star[q];
	}

protected:

	StarClass * star[ 2 ];

};

class StarNode{
public:
	StarNode( StarLine * st ){
		next = NULL;
		star = st;
	}

	void add( StarNode * who ){
		next = who;
	}

	StarNode * Next(){
		return next;
	}

	StarLine * Get(){
		return star;
	}

	~StarNode(){
		delete star;
	}

protected:
	StarNode * next;
	StarLine * star;
};

class ColorChanger{
public:

	ColorChanger( int m ){
		max = m;
		shade = new int[ m ];

		c1 = new RGBHandle();
		c2 = new RGBHandle();

		Util::blend_palette( shade, max, c1->Get(), c2->Get() );

	}

	void update(){

		c1->update( 255, 180 );
		c2->update( 115, 30 );

		Util::blend_palette( shade, max, c1->Get(), c2->Get() );
	}

	int * Colors(){
		return shade;
	}

	int MAXCOLORS(){
		return max;
	}

	~ColorChanger(){
		delete[] shade;
		delete c1;
		delete c2;
	}

protected:
	int * shade;
	int max;

	RGBHandle * c1, * c2;
	
};

class WormHole{
public:
	WormHole(){
		spiral = 0;
		actualx = Util::rnd(640);
		actualy = Util::rnd(480);
		virtualx = actualx;
		virtualy = actualy;
		zsize = Util::rnd( 20 ) + 25;
		msize = zsize;
		ang = Util::rnd( 360 );
		//head = new StarNode( NULL );
		//very_last = head;
		x_col = new ColorChanger( 30 );

	}

	void Update(){
		if ( !spiral ){
			ang = ( ang + Util::rnd( 30 ) - 15 + 360 ) % 360;
			if ( Util::rnd( 20 ) == Util::rnd( 20 ) )
				ang = Util::rnd( 360 );
		} else {
			ang = ( ang + 15 ) % 360;
			spiral--;
		}
		if( Util::rnd( 120 ) == Util::rnd( 120 ) )
			spiral = Util::rnd( 30 ) + 35;

		if ( actualx < 20 || actualy < 20 || actualx > GRAPHICS_X-20 ||
			actualy > Util::screen_y - 20 )
				ang = gang( actualx, actualy, GRAPHICS_X/2, GRAPHICS_Y/2 );
		virtualx += Tcos( ang ) * WORM_MOVE;
		virtualy += Tsine(ang ) * WORM_MOVE;
		actualx = (int)virtualx;
		actualy = (int)virtualy;

		if ( Util::rnd( 20 ) == Util::rnd( 20 ) )
			msize = Util::rnd( 40 ) + 5;
		if ( zsize < msize )
			zsize++;
		if ( zsize > msize )
			zsize--;

		for ( int q = 0; q < 60; q++ ){
			StarLine * p = new StarLine(zsize,actualx,actualy);
			//star_list.push_back( new StarLine(zsize,actualx,actualy) );
			star_list.push_back( p );
		}

		/*
		StarNode * junk = head->Next();
		StarNode * hold = head;
		while ( junk != NULL ){
			if ( junk->Get()->Update() ){
				hold->add( junk->Next() );
				if ( junk == very_last ) very_last = hold;
				delete junk;
				junk = NULL;
			}
			hold = hold->Next();
			if ( hold != NULL ) junk = hold->Next();
		}
		*/
		for ( vector< StarLine * >::iterator it = star_list.begin(); it != star_list.end(); )
			if ( (*it)->Update() ){
				StarLine * who = *it;
				it = star_list.erase( it );
				delete who;
			} else ++it;
		
		x_col->update();
		
	}

	void add( StarNode * temp ){
		StarNode * junk = very_last;
		//while ( junk->Next() != NULL ) junk = junk->Next();
		junk->add( temp );
		very_last = junk->Next();
	}

	void Draw( const Bitmap & work ){
		
		for ( vector< StarLine * >::iterator it = star_list.begin(); it != star_list.end(); it++ ){
			(*it)->Draw( work, x_col->Colors(), x_col->MAXCOLORS() );
		}

		/*
		StarNode * junk = head->Next();
		while ( junk != NULL ){
			junk->Get()->Draw( work, x_col->Colors(), x_col->MAXCOLORS() );
			junk = junk->Next();
		}
		*/

	}

	~WormHole(){
	
		delete x_col;
		for ( vector< StarLine * >::iterator it = star_list.begin(); it != star_list.end(); ){
			StarLine * who = *it;
			it = star_list.erase( it );
			delete who;
		}

		/*
		StarNode * junk = head;
		while( junk != NULL ){
			StarNode * last = junk;
			junk = junk->Next();
			delete last;
		}
		*/
	}


protected:
	int zsize;
	int msize;
	int actualx, actualy;
	int ang;
	int spiral;
	double virtualx, virtualy;
	StarNode * head;
	StarNode * very_last;
	ColorChanger * x_col;
	vector< StarLine * > star_list;

	bool printing;
	int print_x;
	int sang;
	int scount;
};
#endif
