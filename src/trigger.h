#ifndef _trigger_base_class_h
#define _trigger_base_class_h

class trigger{
public:
	trigger( char * info, int size_data, int type, int xv, int yv );

	virtual void * get( void * helper );
	virtual int size();
	virtual int kind();
	virtual int CX();
	virtual int CY();
	virtual void kill();

	virtual ~trigger();

protected:
	char * data;
	int size_d;
	int id;
	int loc_x, loc_y;

};

#endif
