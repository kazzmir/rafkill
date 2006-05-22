#ifndef _rfield_h
#define _rfield_h

#include "bitmap.h"
#include <string>

using namespace std;

class Font;
class RMenu;

class RField{
public:
	RField( bool selectable, bool perm, int return_val, RMenu * who, int number, int sound );
	
	//selectable
	virtual bool Ok();

	virtual bool Title();

	//return value
	virtual int Val();

	//returns place in list
	virtual int Place();

	//add RField to list
	virtual void Add( RField * rf );

	//sets the next menu when chosen
	virtual void setMenu( RMenu * nx );

	virtual int Size();

	//called when field is selected from menu
	virtual void Selected();

	virtual void Draw( const Bitmap & work, int x, int y, int col );

	//returns true if container = obj
	virtual bool equiv( void * obj );
	
	virtual RField * Next();
	virtual RField * Prev();
	virtual RMenu * NextMenu();

	virtual ~RField();

protected:
	bool select;
	int ret;
	int num;

	bool title;

	RField * next, * prev;
	RMenu * menu_next;
	int sound;
};

class RField_Name: public RField {
public:
	RField_Name( Font * f_font, string name, bool selectable, bool perm, int return_val, RMenu * who, int number, int sound );
	virtual bool equiv( void * obj );
	virtual void Draw( const Bitmap & work, int x, int y, int col );
	virtual int Size();
	virtual ~RField_Name();
protected:
	string handle;
	Font * field_font;
};

class RField_Bitmap: public RField {
public:
	RField_Bitmap( const Bitmap & look, bool selectable, bool perm, int return_val, RMenu * who, int number, int sound );
	virtual bool equiv( void * obj );
	virtual void Draw( const Bitmap & work, int x, int y, int col );
	virtual int Size();
	virtual ~RField_Bitmap();
protected:
	Bitmap scene;
};

#endif
