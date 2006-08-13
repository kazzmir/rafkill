#ifndef _rafkill_config_h
#define _rafkill_config_h

#include <string>

class Configuration{
public:

	static std::string getForwardKeyName();
	static std::string getBackwardKeyName();
	static std::string getLeftKeyName();
	static std::string getRightKeyName();
	static std::string getShootKeyName();
	
	static int getForwardKey();
	static int getBackwardKey();
	static int getLeftKey();
	static int getRightKey();
	static int getShootKey();

	static void setForwardKey( int k );
	static void setBackwardKey( int k );
	static void setLeftKey( int k );
	static void setRightKey( int k );
	static void setShootKey( int k );

	static void saveConfiguration();

	static Configuration * getInstance();
private:
	Configuration();
	static Configuration * instance;
	
	void loadConfiguration();

	int internalGetForwardKey() const;
	int internalGetBackwardKey() const;
	int internalGetLeftKey() const;
	int internalGetRightKey() const;
	int internalGetShootKey() const;
	
	void internalSetForwardKey( const int k );
	void internalSetBackwardKey( const int k );
	void internalSetLeftKey( const int k );
	void internalSetRightKey( const int k );
	void internalSetShootKey( const int k );

	int keyForward;
	int keyBackward;
	int keyLeft;
	int keyRight;
	int keyShoot;
};

#endif
