#ifndef PCH_H
#define PCH_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/String.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <windows.h>
#include <chrono>
#include <thread>
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
#define DEBUG_MSG(str) do { std::wcout << str << L"\n"; } while(false)
#else
#define DEBUG_SET_FUNC_NAME
#define DEBUG_MSG(str) do { } while (false)
#endif

#endif