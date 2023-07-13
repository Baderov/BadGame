#ifndef PCH_H
#define PCH_H

#include <iostream> // header that defines the standard input/output stream objects.
#include <SFML/Graphics.hpp> // SFML library for working with graphics.
#include <SFML/Network.hpp> // SFML library for networking.
#include <SFML/System/Vector2.hpp>
#include <SFML/System/String.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <windows.h> // windows-specific header file for the C and C++ programming languages which contains declarations for all of the functions in the Windows API.
#include <chrono> // time library.
#include <thread> // header file for threads.
#include <mutex>
#include <array>
#include <vector>
#include <cassert>
#include <cmath>
#include <string>
#include <utility>
#include <condition_variable>
#include "profile.hpp"

#ifdef _DEBUG
#define DEBUG_SET_FUNC_NAME gv->setFuncName(__func__);
#define DEBUG_MSG(str) do { std::cout << str << "\n"; } while(false)
#else
#define DEBUG_SET_FUNC_NAME
#define DEBUG_MSG(str) do { } while (false)
#endif

#endif