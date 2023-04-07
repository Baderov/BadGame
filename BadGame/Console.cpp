#include "pch.h"
#include "Console.h" // header file for working with the console.

void consoleSettings() // function for console settings.
{
	setlocale(LC_ALL, "RUS"); // for Cyrillic in the console.
	// remove the ability to select and perform various actions in the console.
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hStdin, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE;
	mode &= ~ENABLE_INSERT_MODE;
	mode &= ~ENABLE_MOUSE_INPUT;
	SetConsoleMode(hStdin, mode);
}