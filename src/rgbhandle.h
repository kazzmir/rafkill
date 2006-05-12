#ifndef _rgbhandle_h
#define _rgbhandle_h

#define RGB_GO_BLACK 12
#define RGB_SWITCH 15

struct RGB{
	unsigned char r, g, b;	
};

class RGBHandle{
public:

	RGBHandle();
	void update( int max, int min );
	int Get();

protected:
	
	bool changecol( unsigned char & c, unsigned char & dir );

	RGB mine;
	unsigned char rwant, gwant, bwant;
};

#endif
