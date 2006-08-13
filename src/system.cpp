#include "system.h"
#include <strings.h>
#include <string>

#ifdef WINDOWS
static const char * type(){
	return "WINBLOWS";
}

static string homeDir(){
	return string( "." );
}

#else
#include <sys/types.h>
#include <pwd.h>

static const char * type(){
	return "UNIX";
}

static std::string homeDir(){
	struct passwd * fields = getpwuid( getuid() );
	return std::string( fields->pw_dir );
}

#endif

bool System::onWindows(){
	return strcasecmp( type(), "WINBLOWS" ) == 0;
}

bool System::onUnix(){
	return strcasecmp( type(), "UNIX" ) == 0;
}

std::string System::getHomeDirectory(){
	return homeDir();
}
