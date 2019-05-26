#include "graphics.h"
#include "engine.h"


#define MAP_WIDTH			20
#define MAP_LENGTH			20
#define WALL_PER_CENT		5
#define APPLE_PER_CENT		5
#define SNAKE_VELOCITY		10







int main() {
	field new_field = generate_field(MAP_WIDTH,
		MAP_LENGTH,
		WALL_PER_CENT,
		APPLE_PER_CENT);

	field tmp_field = new_field;
	snake new_snake = initial_position(new_field);
	int menu_indicator = 0;									//	-1 - game-over-menu		0 - game-field, menu is closed	1 - pause-menu
	int time_indicator = 0;									//	number of timeout cycles only in game since last position changing
	int snake_mode = 1;										//	1 - snake is visible	0 - snake is invisible
	int direction_indicator = 0;							//	1 - chnging direction is prohibited
	
	while(1) {
		ConShowCursor(0);
		timeout();

		int event_type = classify_event();

		if (menu_indicator == 0) {							//	ingame operations
			time_indicator++;

			if (event_type == KEY_UP ||						//	changing direction event
				event_type == KEY_LEFT ||
				event_type == KEY_RIGHT ||
				event_type == KEY_DOWN &&
				(direction_indicator == 0)) {

				change_direction(event_type, new_snake);
				direction_indicator = 1;
			}

			if (event_type == '0') {						//	zero is pressed, opening pause menu
				tmp_field = menu(new_field);
				snake_mode = 0;
				menu_indicator = 1;
			}

			if (SELF_SNAKE_COLLISION(new_snake) ||			//	collision processing
				SNAKE_WITH_WALL_COLLISION(new_field, new_snake)) {

				tmp_field = game_over(new_field, new_snake);
				snake_mode = 0;
				menu_indicator = -1;
			}

			if (SNAKE_WITH_APPLE_COLLISION(new_field, new_snake)) {		//	apple eating processing
				eat_apple(&new_snake, new_field);
			}
		}

		if(menu_indicator == 1) {							//	inpause-menu operations
			switch (event_type) {
			case KEY_ESC:									//	go back to game
				delete_field(&tmp_field);
				tmp_field = new_field;
				snake_mode = 1;
				menu_indicator = 0;
				break;

			case '1':										//	map saving
				map_saving(new_field, new_snake);
				break;

			case '2':										//	map opening
				delete_field(&new_field);
				delete_snake(&new_snake);
				open_map(&new_field, &new_snake);
				delete_field(&tmp_field);
				tmp_field = new_field;
				snake_mode = 1;
				menu_indicator = 0;
				break;

			case '3':										//	renew game
				delete_field(&new_field);
				new_field = generate_field(MAP_WIDTH,
				MAP_LENGTH,
				WALL_PER_CENT,
				APPLE_PER_CENT);

				delete_snake(&new_snake);
				new_snake = initial_position(new_field);
				tmp_field = new_field;
				snake_mode = 1;
				menu_indicator = 0;
				break;

			case '4':										//	exit
				delete_field(&tmp_field);
				delete_field(&new_field);
				delete_snake(&new_snake);
				return 0;
			}
		}

		if (menu_indicator == -1) {							//	ingame-over-menu operations
			switch (event_type) {
			case '1':										//	renew game
				delete_field(&new_field);
				new_field = generate_field(MAP_WIDTH,
				MAP_LENGTH,
				WALL_PER_CENT,
				APPLE_PER_CENT);

				delete_snake(&new_snake);
				new_snake = initial_position(new_field);
				delete_field(&tmp_field);
				tmp_field = new_field;
				snake_mode = 1;
				menu_indicator = 0;
				break;

			case '2':										//	map opening
				delete_field(&new_field);
				delete_snake(&new_snake);
				open_map(&new_field, &new_snake);
				delete_field(&tmp_field);
				tmp_field = new_field;
				snake_mode = 1;
				menu_indicator = 0;
				break;

			case '3':										//	exit
				delete_field(&tmp_field);
				delete_field(&new_field);
				delete_snake(&new_snake);
				return 0;					
			}
		}

		if(time_indicator == SNAKE_VELOCITY) {				//	snake position changing
			change_snake_position(new_snake);
			time_indicator = 0;
			direction_indicator = 0;
		}

		renew_screen(tmp_field, new_snake, snake_mode);		//	sending prepared image to screen
	}

	return 0;
}