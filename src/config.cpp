#include "config.h"
#include "keyboard.h"
#include "system.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

static const char * filename = "rafkill.config";

string getConfigFile(){
	if ( System::onWindows() ){
		return System::getHomeDirectory() + "/" + filename;
	} else if ( System::onUnix() ){
		return System::getHomeDirectory() + "/.rafkill";
	}
	return filename;
}

Configuration * Configuration::instance = NULL;

Configuration * Configuration::getInstance(){
	if ( instance == NULL ){
		instance = new Configuration();
	}
	return instance;
}

Configuration::Configuration(){
	internalSetForwardKey( Keyboard::UP );
	internalSetBackwardKey( Keyboard::DOWN );
	internalSetLeftKey( Keyboard::LEFT );
	internalSetRightKey( Keyboard::RIGHT );
	internalSetShootKey( Keyboard::SPACE );

	loadConfiguration();
}

void Configuration::loadConfiguration(){
	FILE * config = fopen( getConfigFile().c_str(), "rb" );
	if ( ! config ){
		return;
	}
	char buf[ 1024 ];
	while ( ! feof( config ) ){
		fgets( buf, sizeof( buf ), config );
		if ( feof( config ) ){
			continue;
		}
		if ( buf[ 0 ] != '#' ){
			char bname[ 1024 ];
			int key = 0;
			sscanf( buf, "%s = %d", bname, &key );
			string name( bname );
			if ( name == "forward" ){
				internalSetForwardKey( key );
			} else if ( name == "backward" ){
				internalSetBackwardKey( key );
			} else if ( name == "left" ){
				internalSetLeftKey( key );
			} else if ( name == "right" ){
				internalSetRightKey( key );
			} else if ( name == "shoot" ){
				internalSetShootKey( key );
			} else {
				cout << "Ignoring line " << buf << endl;
			}
		}
	}
	fclose( config );
}
	
std::string Configuration::getForwardKeyName(){
	return Keyboard::keyToString( getForwardKey() );
}

std::string Configuration::getBackwardKeyName(){
	return Keyboard::keyToString( getBackwardKey() );
}

std::string Configuration::getLeftKeyName(){
	return Keyboard::keyToString( getLeftKey() );
}

std::string Configuration::getRightKeyName(){
	return Keyboard::keyToString( getRightKey() );
}

std::string Configuration::getShootKeyName(){
	return Keyboard::keyToString( getShootKey() );
}

int Configuration::getForwardKey(){
	return getInstance()->internalGetForwardKey();
}

int Configuration::getBackwardKey(){
	return getInstance()->internalGetBackwardKey();
}

int Configuration::getLeftKey(){
	return getInstance()->internalGetLeftKey();
}

int Configuration::getRightKey(){
	return getInstance()->internalGetRightKey();
}

int Configuration::getShootKey(){
	return getInstance()->internalGetShootKey();
}

int Configuration::internalGetForwardKey() const {
	return keyForward;
}

int Configuration::internalGetBackwardKey() const {
	return keyBackward;
}

int Configuration::internalGetLeftKey() const {
	return keyLeft;
}

int Configuration::internalGetRightKey() const {
	return keyRight;
}

int Configuration::internalGetShootKey() const {
	return keyShoot;
}

void Configuration::setForwardKey( int k ){
	getInstance()->internalSetForwardKey( k );
}

void Configuration::setBackwardKey( int k ){
	getInstance()->internalSetBackwardKey( k );
}

void Configuration::setLeftKey( int k ){
	getInstance()->internalSetLeftKey( k );
}

void Configuration::setRightKey( int k ){
	getInstance()->internalSetRightKey( k );
}

void Configuration::setShootKey( int k ){
	getInstance()->internalSetShootKey( k );
}

void Configuration::internalSetForwardKey( const int k ){
	keyForward = k;
}

void Configuration::internalSetBackwardKey( const int k ){
	keyBackward = k;
}

void Configuration::internalSetLeftKey( const int k ){
	keyLeft = k;
}

void Configuration::internalSetRightKey( const int k ){
	keyRight = k;
}

void Configuration::internalSetShootKey( const int k ){
	keyShoot = k;
}

void Configuration::saveConfiguration(){

	ofstream config( getConfigFile().c_str() );

	cout << "Config file: " << getConfigFile() << endl;
	config << "## Rafkill config file" << endl;
	config << "## Do not hand edit, the loader will get messed up" << endl;
	config << "forward = " << getForwardKey() << endl;
	config << "backward = " << getBackwardKey() << endl;
	config << "left = " << getLeftKey() << endl;
	config << "right = " << getRightKey() << endl;
	config << "shoot = " << getShootKey() << endl;
	config.close();

	delete instance;
	instance = NULL;
}
