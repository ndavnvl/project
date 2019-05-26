#pragma once

#include <time.h>
#include <windows.h>
#include "conlib.h"
#include "engine.h"


#ifndef SNAKE_COLOR
#define SNAKE_COLOR			FOREGROUND_BLUE
#endif // !SNAKE_COLOR

#ifndef WALL_COLOR
#define WALL_COLOR			FOREGROUND_GREEN
#endif // !WALL_COLOR

#ifndef APPLE_COLOR
#define APPLE_COLOR			FOREGROUND_RED
#endif // !APPLE_COLOR


#define TIMEOUT				1


int classify_event();

void renew_screen(field field_, snake snake_, int snake_mode);

void timeout();