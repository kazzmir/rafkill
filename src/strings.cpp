#include "strings.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int numDig( int q ) {

	int t = 1;
	q = abs( q );
	while( q >= 10 ) {
		t++;
		q /= 10;
	}
	return t;

}


char * int2str( int z ) {
	bool neg = z < 0;
	int nd = numDig( z );
	char * str = (char *)malloc( sizeof(char) * (neg + nd + 1) );

	z = abs( z );
	for ( int q = 0; q < nd; q++ ) {
		int h = z % 10;
		str[ neg + nd - q - 1 ] = '0' + h;
		z /= 10;
	}
	if ( neg ) str[0] = '-';
	str[ neg + nd ] = '\0';
	return str;

}


char * int2normal( int z ) {
	bool neg = z < 0;
	int nd = numDig( z );
	int total_char = neg + nd + abs(nd-1)/3+1;
	char * str = (char *)malloc( sizeof(char) * (total_char) );
	for ( int q = 0; q < total_char; q++ )
		str[q] = 'A';
	char * lem = str+(total_char-1);
	*lem = '\0';
	lem--;
	z = abs( z );
	for ( int q = 0; q < nd; q++ ) {
		int h = z % 10;
		*lem = '0'+h;
		lem--;
		if ( (q+1) % 3 == 0 && q != nd-1 ) {
			*lem = ',';
			lem--;
		}
		z /= 10;
	}
	if ( neg ) *str = '-';
	return str;
}


char * d2normal( double whole, int precise ) {
	int z = (int)whole;
	bool neg = z < 0;
	int nd = numDig( z );
	int total_char = neg + nd + abs(nd-1)/3+1+1;
	char * str = (char *)malloc( sizeof(char) * (total_char) );
	for ( int q = 0; q < total_char; q++ )
		str[q] = 'A';
	char * lem = str+(total_char-1);
	*lem = '\0';
	lem--;
	*lem = '.';
	lem--;
	z = abs( z );
	for ( int q = 0; q < nd; q++ ) {
		int h = z % 10;
		*lem = '0'+h;
		lem--;
		if ( (q+1) % 3 == 0 && q != nd-1 ) {
			*lem = ',';
			lem--;
		}
		z /= 10;
	}

	z = (int)whole;
	whole -= z;
	whole = fabs( whole );
	for ( int q = 0; q < precise; q++ ) {

		char * t = (char *)malloc( sizeof( char ) * 2 );
		whole *= 10;
		z = (int)whole;
		*t = '0' + z;
		whole -= z;
		*(t+1) = '\0';
		char * reveal = append( str, t );
		free( str );
		free( t );
		str = reveal;

	}

	if ( neg ) *str = '-';
	return str;
}


char upcase( char u ) {

	if ( u >= 'a' && u <= 'z' )
		return u-'a'+'A';
	else    return u;

}


void upstring( char * who ) {
	while ( *who != 0 )
		*who++ = upcase( *who );
}


int str2int( char * convert ) {

	int total = 0;
	bool neg = convert[0] == '-';
	for ( int q = neg; q < length( convert ); q++ ) {
		if ( !(convert[q] >= '0' && convert[q] <= '9' ) )
			return 0;
		total = total * 10 + convert[q]-'0';
	}
	if ( neg ) total *= -1;
	return total;

}


double str2d( char * convert ) {

	double front = 0;
	double back = 0;
	int place;
	bool neg = convert[0] == '-';
	for ( place = neg; place < length( convert ) && convert[place] != '.'; place++ ) {
		if ( !( convert[place] >= '0' && convert[place] <= '9' ) )
			return 0;
		front = (front * 10.0) + convert[place]-'0';
	}
	if ( neg ) front *= -1;
	if ( place >= length( convert ) )
		return front;
	if ( convert[place] == '.' ) place++;
	double total = 1.0;
	for ( ; place < length( convert ); place++ ) {
		if ( !(convert[place] >= '0' && convert[place] <= '9' ) )
			return 0;
		total *= 10.0;
		back = (back * 10.0) + convert[place]-'0';
	}
	back /= total;
	if ( neg ) back *= -1;
	front += back;
	return front;

}


int length( char * q ) {
	int z;
	for ( z = 0; *q != '\0'; z++, q++ );
	return z;
}


/*
char * mstr( char * copy ) {

	return strdup( copy );

	int m1 = length( copy );
	char * mv = (char *)malloc( sizeof(char) * ( m1 + 1 ) );
	memmove( (void *)mv, (void *)copy, m1 );
	mv[m1] = '\0';
	return mv;

}
*/

char * append( const char * first, const char * second ) {
	//printf("Appending [%s] with [%s]\n", first, second );
	int m1 = strlen( first );
	int m2 = strlen( second );
	if ( m1 + m2 == 0 )
		return strdup("");
	char * final = (char *)malloc( sizeof(char) * (m1 + m2 + 1) );
	if ( m1 ) memmove( (void *)final, (void *)first, m1 );
	if ( m2 ) memmove( (void *)(final + sizeof(char)*m1 ), (void *)second, m2 );
	final[ m1 + m2 ] = '\0';
	return final;
}
