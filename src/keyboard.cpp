#include <allegro.h>
#include "keyboard.h"

static const bool getKey( int k ){
	return key[ k ];
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

