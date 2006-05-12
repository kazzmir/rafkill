#ifndef _raptor_menu_h_
#define _raptor_menu_h_

#include <string>
#include "bitmap.h"

/* TODO: Replace all char* with std::string
 */

class Font;
class RField;

class RMenu{
public:

	RMenu( const Bitmap & intr, int x, int y, int height, int c1, int c2, int title_color );

	//addMenu: Adds a RField class to the list
	virtual void addTitle( char * n, Font * rf );
	virtual void addMenu( char * n, Font * rf, bool s, int r, RMenu * who, int sound );
	virtual void addMenu( const Bitmap & look, bool s, int r, RMenu * who, int sound );

	//replace: Replaces a given RField with a new RField at position q in the list
	virtual void replace( int q, char * n, Font * rf, bool s, int r, RMenu * who, int sound );
	virtual void replaceTitle( int q, char * n, Font * rf );
	virtual void replace( int q, const Bitmap & look, bool s, int r, RMenu * who, int sound );

	//returns the place where field str lives, or -1 if cant find
	virtual int askPos( char * str );

	//procMenu: Runs the current menu, returning the value of the menu
	//and changing the current menu to the selected one
	virtual int procMenu( RMenu ** current );

	virtual void init();

	virtual bool changed();
	
	virtual void nextMenu( int q, RMenu * nx );
	
	virtual void prevMenu( RMenu * rm );

	virtual RMenu * Previous();

	virtual void clear();

	virtual bool Selected();

	virtual ~RMenu();

protected:

	int countNodes();
	void spiffy_triangle( const Bitmap & work, int x1, int y1, int color, int * shade, int MAX_SHADE, int dir );
	virtual void Draw( const Bitmap & work, int x, int * yval, int * yshade, int min, int max );
	virtual void endMenu();

	Bitmap background;

	int last_opt;
	int first_x, first_y;

	int col1, col2;
	int t_color;
	RField * head, * location;
	RMenu * prev;

	int * shade;
	int * shade_border;
	int * shade_opt_color;

	bool select;

protected:

	Bitmap work;

	double x1;
	int ang;

	int height;

	int col_up;
	int col_down;
	int opt_max;
	int max_seen;				  //maximum number of fields on the screen at any one time
	int * opts;
	RField * field_seen;
	int keep_y;
	int * opts_shade;
	RField * temp;
	int ac_y;
	bool k_hold;
	int min_x;
	int shade_counter;

	bool initialized;
	bool change;

};

#endif
