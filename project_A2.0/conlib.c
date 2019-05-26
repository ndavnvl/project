// CONLIB.c : imlementation of console helper functions for Advanced Programming Workshop
//
// This is a part of the Message-Driven Enviroment C library.
// Copyright (C) 1999 Denis V. Kosykh
// All rights reserved.

#include <stdio.h>
#include <stdarg.h>
#include <assert.h>

#ifdef __GNUC__

#include <windows.h>

#include <mingw32/conio.h>

#else	// default: MSVC

#include <wtypes.h>
#include <wincon.h>
#include <conio.h>

#endif // __GNUC__

#include "CONLIB.h"

int GotoXY(int x, int y)
{
	COORD pos = { x, y };

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	return SetConsoleCursorPosition(hStdOut, pos);
}

int MaxXY(int *px, int *py)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		*px = csbi.srWindow.Right - csbi.srWindow.Left;
		*py = csbi.srWindow.Bottom - csbi.srWindow.Top;
		return 1;
	}
	return 0; // error
}

int ClearConsole()
{
	int mx, my;

	if (MaxXY(&mx, &my))
	{
		COORD szBuf = {mx + 1, my + 1};
		COORD BufferCoord= {0, 0};
		SMALL_RECT srWriteRegion = {0, 0, mx, my};

		CHAR_INFO *lpBuffer = (CHAR_INFO *)calloc(szBuf.X * szBuf.Y, sizeof(CHAR_INFO));
		
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		int result = WriteConsoleOutput(hStdOut, lpBuffer, szBuf, BufferCoord, &srWriteRegion); 
		free (lpBuffer);
		return result;
	}
	return 0; // error
}

int SetColor(int color)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	return SetConsoleTextAttribute(hStdOut, (short)color);
}

int ConShowCursor(int bVisible)
{
	CONSOLE_CURSOR_INFO ci;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (GetConsoleCursorInfo(hStdOut, &ci))
	{
		ci.bVisible = bVisible;
		return SetConsoleCursorInfo(hStdOut, &ci);
	}

	return 0; // error
}
////////////////////////////////////////////////////////
// Input functions

int KeyPressed()
{
	return _kbhit();
}

int GetKey()
{
	int ch = _getch();

	if (ch == 0 || ch == 224) // extended code
		return - _getch();

	return ch;
}
