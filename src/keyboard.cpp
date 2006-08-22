#include <allegro.h>
#include "keyboard.h"
#include <string>

using namespace std;

static const bool getKey( int k ){
	return ::key[ k ];
}

const bool Keyboard::getAnyKey( int k1, int k2, int k3, int k4 ){
	return getKey( k1 ) || getKey( k2 ) || getKey( k3 ) || getKey( k4 );
}

const bool Keyboard::getAnyKey( int k1, int k2, int k3 ){
	return getKey( k1 ) || getKey( k2 ) || getKey( k3 );
}

const bool Keyboard::getAnyKey( int k1, int k2 ){
	return getKey( k1 ) || getKey( k2 );
}

const bool Keyboard::getAnyKey( int k1 ){
	return getKey( k1 );
}
	
const bool Keyboard::keyPressed(){
	return ::keypressed();
}

void Keyboard::clear(){
	::clear_keybuf();
}
	
const int Keyboard::readKey(){
	if ( ! ::keypressed() ){
		return -1;
	}
	return ::readkey() >> 8;
}
	
string Keyboard::keyToString( int key ){
	if ( key == A ) return "A";
	if ( key == B ) return "B";
	if ( key == C ) return "C";
	if ( key == D ) return "D";
	if ( key == E ) return "E";
	if ( key == F ) return "F";
	if ( key == G ) return "G";
	if ( key == H ) return "H";
	if ( key == I ) return "I";
	if ( key == J ) return "J";
	if ( key == K ) return "K";
	if ( key == L ) return "L";
	if ( key == M ) return "M";
	if ( key == N ) return "N";
	if ( key == O ) return "O";
	if ( key == P ) return "P";
	if ( key == Q ) return "Q";
	if ( key == R ) return "R";
	if ( key == S ) return "S";
	if ( key == T ) return "T";
	if ( key == U ) return "U";
	if ( key == V ) return "V";
	if ( key == W ) return "W";
	if ( key == X ) return "X";
	if ( key == Y ) return "Y";
	if ( key == Z ) return "Z";
	if ( key == N0 ) return "N0";
	if ( key == N1 ) return "N1";
	if ( key == N2 ) return "N2";
	if ( key == N3 ) return "N3";
	if ( key == N4 ) return "N4";
	if ( key == N5 ) return "N5";
	if ( key == N6 ) return "N6";
	if ( key == N7 ) return "N7";
	if ( key == N8 ) return "N8";
	if ( key == N9 ) return "N9";
	if ( key == PAD_0 ) return "PAD_0";
	if ( key == PAD_1 ) return "PAD_1";
	if ( key == PAD_2 ) return "PAD_2";
	if ( key == PAD_3 ) return "PAD_3";
	if ( key == PAD_4 ) return "PAD_4";
	if ( key == PAD_5 ) return "PAD_5";
	if ( key == PAD_6 ) return "PAD_6";
	if ( key == PAD_7 ) return "PAD_7";
	if ( key == PAD_8 ) return "PAD_8";
	if ( key == PAD_9 ) return "PAD_9";
	if ( key == F1 ) return "F1";
	if ( key == F2 ) return "F2";
	if ( key == F3 ) return "F3";
	if ( key == F4 ) return "F4";
	if ( key == F5 ) return "F5";
	if ( key == F6 ) return "F6";
	if ( key == F7 ) return "F7";
	if ( key == F8 ) return "F8";
	if ( key == F9 ) return "F9";
	if ( key == F10 ) return "F10";
	if ( key == F11 ) return "F11";
	if ( key == F12 ) return "F12";
	if ( key == ESC ) return "ESC";
	if ( key == TILDE ) return "TILDE";
	if ( key == MINUS ) return "MINUS";
	if ( key == EQUALS ) return "EQUALS";
	if ( key == BACKSPACE ) return "BACKSPACE";
	if ( key == TAB ) return "TAB";
	if ( key == OPENBRACE ) return "OPENBRACE";
	if ( key == CLOSEBRACE ) return "CLOSEBRACE";
	if ( key == ENTER ) return "ENTER";
	if ( key == COLON ) return "COLON";
	if ( key == QUOTE ) return "QUOTE";
	if ( key == BACKSLASH ) return "BACKSLASH";
	if ( key == BACKSLASH2 ) return "BACKSLASH2";
	if ( key == COMMA ) return "COMMA";
	if ( key == STOP ) return "STOP";
	if ( key == SLASH ) return "SLASH";
	if ( key == SPACE ) return "SPACE";
	if ( key == INSERT ) return "INSERT";
	if ( key == DEL ) return "DEL";
	if ( key == HOME ) return "HOME";
	if ( key == END ) return "END";
	if ( key == PGUP ) return "PGUP";
	if ( key == PGDN ) return "PGDN";
	if ( key == LEFT ) return "LEFT";
	if ( key == RIGHT ) return "RIGHT";
	if ( key == UP ) return "UP";
	if ( key == DOWN ) return "DOWN";
	if ( key == SLASH_PAD ) return "SLASH_PAD";
	if ( key == ASTERISK ) return "ASTERISK";
	if ( key == MINUS_PAD ) return "MINUS_PAD";
	if ( key == PLUS_PAD ) return "PLUS_PAD";
	if ( key == DEL_PAD ) return "DEL_PAD";
	if ( key == ENTER_PAD ) return "ENTER_PAD";
	if ( key == PRTSCR ) return "PRTSCR";
	if ( key == PAUSE ) return "PAUSE";
	if ( key == C1 ) return "C1";
	if ( key == YEN ) return "YEN";
	if ( key == KANA ) return "KANA";
	if ( key == CONVERT ) return "CONVERT";
	if ( key == NOCONVERT ) return "NOCONVERT";
	if ( key == AT ) return "AT";
	if ( key == CIRCUMFLEX ) return "CIRCUMFLEX";
	if ( key == COLON2 ) return "COLON2";
	if ( key == KANJI ) return "KANJI";
	if ( key == EQUALS_PAD ) return "EQUALS_PAD";
	if ( key == BACKQUOTE ) return "BACKQUOTE";
	if ( key == SEMICOLON ) return "SEMICOLON";
	if ( key == COMMAND ) return "COMMAND";
	if ( key == UNKNOWN1 ) return "UNKNOWN1";
	if ( key == UNKNOWN2 ) return "UNKNOWN2";
	if ( key == UNKNOWN3 ) return "UNKNOWN3";
	if ( key == UNKNOWN4 ) return "UNKNOWN4";
	if ( key == UNKNOWN5 ) return "UNKNOWN5";
	if ( key == UNKNOWN6 ) return "UNKNOWN6";
	if ( key == UNKNOWN7 ) return "UNKNOWN7";
	if ( key == UNKNOWN8 ) return "UNKNOWN8";
	if ( key == MODIFIERS ) return "MODIFIERS";
	if ( key == LSHIFT ) return "LSHIFT";
	if ( key == RSHIFT ) return "RSHIFT";
	if ( key == LCONTROL ) return "LCONTROL";
	if ( key == RCONTROL ) return "RCONTROL";
	if ( key == ALT ) return "ALT";
	if ( key == ALTGR ) return "ALTGR";
	if ( key == LWIN ) return "LWIN";
	if ( key == RWIN ) return "RWIN";
	if ( key == MENU ) return "MENU";
	if ( key == SCRLOCK ) return "SCRLOCK";
	if ( key == NUMLOCK ) return "NUMLOCK";
	if ( key == CAPSLOCK ) return "CAPSLOCK";
	if ( key == MAX ) return "MAX";

	return "Unknown";
}

const int Keyboard::A = KEY_A;
const int Keyboard::B = KEY_B;
const int Keyboard::C = KEY_C;
const int Keyboard::D = KEY_D;
const int Keyboard::E = KEY_E;
const int Keyboard::F = KEY_F;
const int Keyboard::G = KEY_G;
const int Keyboard::H = KEY_H;
const int Keyboard::I = KEY_I;
const int Keyboard::J = KEY_J;
const int Keyboard::K = KEY_K;
const int Keyboard::L = KEY_L;
const int Keyboard::M = KEY_M;
const int Keyboard::N = KEY_N;
const int Keyboard::O = KEY_O;
const int Keyboard::P = KEY_P;
const int Keyboard::Q = KEY_Q;
const int Keyboard::R = KEY_R;
const int Keyboard::S = KEY_S;
const int Keyboard::T = KEY_T;
const int Keyboard::U = KEY_U;
const int Keyboard::V = KEY_V;
const int Keyboard::W = KEY_W;
const int Keyboard::X = KEY_X;
const int Keyboard::Y = KEY_Y;
const int Keyboard::Z = KEY_Z;
const int Keyboard::N0 = KEY_0;
const int Keyboard::N1 = KEY_1;
const int Keyboard::N2 = KEY_2;
const int Keyboard::N3 = KEY_3;
const int Keyboard::N4 = KEY_4;
const int Keyboard::N5 = KEY_5;
const int Keyboard::N6 = KEY_6;
const int Keyboard::N7 = KEY_7;
const int Keyboard::N8 = KEY_8;
const int Keyboard::N9 = KEY_9;
const int Keyboard::PAD_0 = KEY_0_PAD;
const int Keyboard::PAD_1 = KEY_1_PAD;
const int Keyboard::PAD_2 = KEY_2_PAD;
const int Keyboard::PAD_3 = KEY_3_PAD;
const int Keyboard::PAD_4 = KEY_4_PAD;
const int Keyboard::PAD_5 = KEY_5_PAD;
const int Keyboard::PAD_6 = KEY_6_PAD;
const int Keyboard::PAD_7 = KEY_7_PAD;
const int Keyboard::PAD_8 = KEY_8_PAD;
const int Keyboard::PAD_9 = KEY_9_PAD;
const int Keyboard::F1 = KEY_F1;
const int Keyboard::F2 = KEY_F2;
const int Keyboard::F3 = KEY_F3;
const int Keyboard::F4 = KEY_F4;
const int Keyboard::F5 = KEY_F5;
const int Keyboard::F6 = KEY_F6;
const int Keyboard::F7 = KEY_F7;
const int Keyboard::F8 = KEY_F8;
const int Keyboard::F9 = KEY_F9;
const int Keyboard::F10 = KEY_F10;
const int Keyboard::F11 = KEY_F11;
const int Keyboard::F12 = KEY_F12;
const int Keyboard::ESC = KEY_ESC;
const int Keyboard::TILDE = KEY_TILDE;
const int Keyboard::MINUS = KEY_MINUS;
const int Keyboard::EQUALS = KEY_EQUALS;
const int Keyboard::BACKSPACE = KEY_BACKSPACE;
const int Keyboard::TAB = KEY_TAB;
const int Keyboard::OPENBRACE = KEY_OPENBRACE;
const int Keyboard::CLOSEBRACE = KEY_CLOSEBRACE;
const int Keyboard::ENTER = KEY_ENTER;
const int Keyboard::COLON = KEY_COLON;
const int Keyboard::QUOTE = KEY_QUOTE;
const int Keyboard::BACKSLASH = KEY_BACKSLASH;
const int Keyboard::BACKSLASH2 = KEY_BACKSLASH2;
const int Keyboard::COMMA = KEY_COMMA;
const int Keyboard::STOP = KEY_STOP;
const int Keyboard::SLASH = KEY_SLASH;
const int Keyboard::SPACE = KEY_SPACE;
const int Keyboard::INSERT = KEY_INSERT;
const int Keyboard::DEL = KEY_DEL;
const int Keyboard::HOME = KEY_HOME;
const int Keyboard::END = KEY_END;
const int Keyboard::PGUP = KEY_PGUP;
const int Keyboard::PGDN = KEY_PGDN;
const int Keyboard::LEFT = KEY_LEFT;
const int Keyboard::RIGHT = KEY_RIGHT;
const int Keyboard::UP = KEY_UP;
const int Keyboard::DOWN = KEY_DOWN;
const int Keyboard::SLASH_PAD = KEY_SLASH_PAD;
const int Keyboard::ASTERISK = KEY_ASTERISK;
const int Keyboard::MINUS_PAD = KEY_MINUS_PAD;
const int Keyboard::PLUS_PAD = KEY_PLUS_PAD;
const int Keyboard::DEL_PAD = KEY_DEL_PAD;
const int Keyboard::ENTER_PAD = KEY_ENTER_PAD;
const int Keyboard::PRTSCR = KEY_PRTSCR;
const int Keyboard::PAUSE = KEY_PAUSE;
const int Keyboard::C1 = KEY_ABNT_C1;
const int Keyboard::YEN = KEY_YEN;
const int Keyboard::KANA = KEY_KANA;
const int Keyboard::CONVERT = KEY_CONVERT;
const int Keyboard::NOCONVERT = KEY_NOCONVERT;
const int Keyboard::AT = KEY_AT;
const int Keyboard::CIRCUMFLEX = KEY_CIRCUMFLEX;
const int Keyboard::COLON2 = KEY_COLON2;
const int Keyboard::KANJI = KEY_KANJI;
const int Keyboard::EQUALS_PAD = KEY_EQUALS_PAD;
const int Keyboard::BACKQUOTE = KEY_BACKQUOTE;
const int Keyboard::SEMICOLON = KEY_SEMICOLON;
const int Keyboard::COMMAND = KEY_COMMAND;
const int Keyboard::UNKNOWN1 = KEY_UNKNOWN1;
const int Keyboard::UNKNOWN2 = KEY_UNKNOWN2;
const int Keyboard::UNKNOWN3 = KEY_UNKNOWN3;
const int Keyboard::UNKNOWN4 = KEY_UNKNOWN4;
const int Keyboard::UNKNOWN5 = KEY_UNKNOWN5;
const int Keyboard::UNKNOWN6 = KEY_UNKNOWN6;
const int Keyboard::UNKNOWN7 = KEY_UNKNOWN7;
const int Keyboard::UNKNOWN8 = KEY_UNKNOWN8;
const int Keyboard::MODIFIERS = KEY_MODIFIERS;
const int Keyboard::LSHIFT = KEY_LSHIFT;
const int Keyboard::RSHIFT = KEY_RSHIFT;
const int Keyboard::LCONTROL = KEY_LCONTROL;
const int Keyboard::RCONTROL = KEY_RCONTROL;
const int Keyboard::ALT = KEY_ALT;
const int Keyboard::ALTGR = KEY_ALTGR;
const int Keyboard::LWIN = KEY_LWIN;
const int Keyboard::RWIN = KEY_RWIN;
const int Keyboard::MENU = KEY_MENU;
const int Keyboard::SCRLOCK = KEY_SCRLOCK;
const int Keyboard::NUMLOCK = KEY_NUMLOCK;
const int Keyboard::CAPSLOCK = KEY_CAPSLOCK;
const int Keyboard::MAX = KEY_MAX;

