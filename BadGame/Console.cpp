#include "Console.h" // подключаем заголовочный файл.

void consoleSettings() // функция консольных настроек.
{
	setlocale(LC_ALL, "RUS"); // русская локализация для консоли.
	// убираем возможность выделения и выполнения различных действий в консоли.
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hStdin, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE;
	mode &= ~ENABLE_INSERT_MODE;
	mode &= ~ENABLE_MOUSE_INPUT;
	SetConsoleMode(hStdin, mode);
}