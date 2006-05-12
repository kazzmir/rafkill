#ifndef _strings_h
#define _strings_h

int numDig( int q );
char * int2str( int z );
char * int2normal( int z );
char * d2normal( double whole, int precise );
int str2int( char * convert );
double str2d( char * convert );
int length( char * q );
char * append( const char * first, const char * second );
char upcase( char u );
void upstring( char * who );

#endif
