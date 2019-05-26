#pragma once


#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "conlib.h"
#include "additional.h"

typedef struct {
	size_t maxX;
	size_t maxY;
	char **id;
} field;

typedef struct {
	size_t snake_length;
	int **snake_coord;
	int *snake_direction;
} snake;


#define DEFAULT_WALLS_PER_CENT		20
#define DEFAULT_APPLES_PER_CENT		10
#define MIN_FREE_PLACE_PER_SENT		40
#define MIN_MAXX					17
#define MIN_MAXY					10


#ifndef WALL_SYMBOL
#define WALL_SYMBOL					61
#endif // !WALL_SYMBOL

#ifndef APPLE_SYMBOL
#define APPLE_SYMBOL				64
#endif // !APPLE_SYMBOL

#ifndef SNAKE_SYMBOL
#define SNAKE_SYMBOL				94
#endif // !SNAKE_SYMBOL

#ifndef EMPTY_SYMBOL
#define EMPTY_SYMBOL				32
#endif // !EMPTY_SYMBOL


#define SELF_SNAKE_COLLISION(snake_) \
		collision_with_snake(snake_, (snake_).snake_coord[0][0], (snake_).snake_coord[0][1])

#define SNAKE_WITH_WALL_COLLISION(field_, snake_) \
		collision_with_wall(field_, (snake_).snake_coord[0][0], (snake_).snake_coord[0][1])

#define SNAKE_WITH_APPLE_COLLISION(field_, snake_) \
		collision_with_apple(field_, (snake_).snake_coord[0][0], (snake_).snake_coord[0][1])

#define FULL_SNAKE_COLLISION(snake_, x , y) \
		(collision_with_snake(snake_, x, y) || \
		((snake_).snake_coord[0][0] == x && \
		(snake_).snake_coord[0][1] == y) || \
		((snake_).snake_length > 1 && \
		((snake_).snake_coord[1][0] == x && \
		(snake_).snake_coord[1][1] == y)))


field generate_field(size_t maxX,
	size_t maxY,
	int walls_per_cent,
	int apples_per_cent);

snake initial_position (field field_);

int collision_with_wall(field field_, int x_coord, int y_coord);

int collision_with_snake(snake snake_, int x_coord, int y_coord);

int collision_with_apple(field field_, int x_coord, int y_coord);

void change_snake_position(snake snake_);

void change_direction(int direction, snake snake_);

void eat_apple(snake* snake_, field field_);

field menu(field field_);

field game_over(field field_, snake snake_);

void map_saving(field field_, snake snake_);

void open_map(field *field_, snake *snake_);

void delete_field(field *field_);

void delete_snake(snake* snake_);