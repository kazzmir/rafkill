#ifndef _hull_animation_h
#define _hull_animation_h

#include "hull.h"
#include "bitmap.h"
#include <vector>

using namespace std;

class HullAnimation: public HullObject{
public:
	
	HullAnimation( const vector< Bitmap > & animations, const vector< Bitmap > & shadows, int _life, int _strength, int num_guns, int level, int _drawing_plane, bool _trans, ECollide * ec );

	virtual void Draw( const Bitmap & who, int x, int y );
	virtual Bitmap * getShadow();
	//virtual void Shadow( Bitmap * who, int x, int y );
	~HullAnimation();

protected:
	vector< Bitmap > pics;
	vector< Bitmap > pics_shadow;
	unsigned int animation;
	bool own_shadow;
};

#endif
