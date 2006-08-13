#include "config.h"
#include "keyboard.h"
#include "system.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

static const char * filename = "rafkill.config";

Configuration * Configuration::instance = NULL;

Configuration * Configuration::getInstance(){
	if ( Configuration::instance == NULL ){
		Configuration::instance = new Configuration();
	}
	return Configuration::instance;
}

Configuration::Configuration(){
	keyForward = Keyboard::UP;
	keyBackward = Keyboard::DOWN;
	keyLeft = Keyboard::LEFT;
	keyRight = Keyboard::RIGHT;
	keyShoot = Keyboard::SPACE;
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

string getConfigFile(){
	if ( System::onWindows() ){
		return System::getHomeDirectory() + "/" + filename;
	} else if ( System::onUnix() ){
		return System::getHomeDirectory() + "/.rafkill";
	}
	return filename;
}

void Configuration::saveConfiguration(){

	ofstream config( getConfigFile().c_str() );

	cout << "Config file: " << getConfigFile() << endl;
	config << "## Rafkill config file" << endl;
	config.close();

	delete instance;
	instance = NULL;
}
