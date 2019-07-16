#include "console.h"

#include <algorithm>

#ifdef __linux__ 
#include <termios.h>
#include <cstdio>
#elif _WIN32
#include <conio.h>
#else
#error Only Windows and Linux supported
#endif

namespace NConsoleUtil {
	char GetPressedKey() {
#ifdef __linux__ 
		termios old, current;
		tcgetattr(0, &old);
		current = old;
		current.c_lflag &= ~ICANON;
		current.c_lflag &= ~ECHO;
		tcsetattr(0, TCSANOW, &current);

		char ch = getchar();
		  
		tcsetattr(0, TCSANOW, &old);
		return ch;
#elif _WIN32
		return _getch();
#endif
	}

	void ClearConsole() {
#ifdef __linux__ 
		std::system("clear");
#elif _WIN32
		std::system("CLS");
#endif
	}
};
