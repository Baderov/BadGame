#include "Console.h" // ���������� ������������ ����.

void consoleSettings() // ������� ���������� ��������.
{
	setlocale(LC_ALL, "RUS"); // ������� ����������� ��� �������.
	// ������� ����������� ��������� � ���������� ��������� �������� � �������.
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hStdin, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE;
	mode &= ~ENABLE_INSERT_MODE;
	mode &= ~ENABLE_MOUSE_INPUT;
	SetConsoleMode(hStdin, mode);
}