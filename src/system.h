#ifndef _happy_stupid_face_system_h_
#define _happy_stupid_face_system_h_

#include <string>

namespace System{
	bool onUnix();
	bool onWindows();

	std::string getHomeDirectory();
}

#endif
