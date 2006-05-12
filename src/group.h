#ifndef _group_h
#define _group_h

using namespace std;

#include <vector>

class SpaceObject;

class Group{
public:

	Group( const int _y );

	void add( SpaceObject * who );
	void drop( SpaceObject * who );
	int size() const;
	inline const int pos() const{
		return y;
	}
	const vector< SpaceObject * > * members() const;

	~Group();

protected:
	vector< SpaceObject * > list;
	int y;
	
};

#endif
