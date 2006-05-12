#ifndef _drawer_h
#define _drawer_h

#include <vector>
#include "bitmap.h"

using namespace std;

class SpaceObject;
class PlayerObject;
class ExplosionClass;

const int MAX_WARNING_SHADE = 40;
const int MAX_ATTRIBUTE_COLOR = 100;

/* Drawer:
 * Draws all the objects and everything you see on the screen
 */
class Drawer{
public:

	Drawer();

	void Draw( const vector< SpaceObject * > * objects, const SpaceObject * player, ExplosionClass ** expl, int MAX_EXPL );
	void fadeToBlack( int num );

	inline void setDrawTrans(){
		drawTrans = true;
	}

	inline void setDrawSolid(){
		drawTrans = false;
	}

	~Drawer();

protected:

	void drawHud( const PlayerObject * player );
	void showAttribute( int amount, int MAX, int start_x, int offset, int * shade );
	void drawLand( int view, int y1 );

	Bitmap * loadLand();

protected:
	int land_counter;
	Bitmap * work;
	Bitmap * radar;
	Bitmap * land;
	Bitmap * transBuffer;

	int warning_shade[ MAX_WARNING_SHADE ];
	int warning_shade_color;

	int view_port;

	int level_speech;

	int shade_energy[ MAX_ATTRIBUTE_COLOR ];
	int shade_shield[ MAX_ATTRIBUTE_COLOR ];

	bool draw_land;
	bool drawTrans;

	// Bitmap * Screen;
};

#endif
