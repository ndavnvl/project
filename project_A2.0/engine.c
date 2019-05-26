#include "engine.h"


field generate_field(size_t maxX,
	size_t maxY,
	int walls_per_cent,
	int apples_per_cent) {

	if (maxX  < MIN_MAXX) {
		maxX = MIN_MAXX;
	}

	if (maxY < MIN_MAXY) {
		maxY = MIN_MAXY;
	}

	if (walls_per_cent > 100) {
		walls_per_cent = DEFAULT_WALLS_PER_CENT;
	}

	if (apples_per_cent > 100) {
		apples_per_cent = DEFAULT_APPLES_PER_CENT;
	}

	if (apples_per_cent + walls_per_cent > 100 - MIN_FREE_PLACE_PER_SENT) {
		apples_per_cent = DEFAULT_APPLES_PER_CENT;
		walls_per_cent = DEFAULT_WALLS_PER_CENT;
	}

	field new_field;
	new_field.maxX = maxX;
	new_field.maxY = maxY;
	new_field.id = (char**)malloc(maxX * sizeof(char*));

	for (size_t i = 0; i < maxX; i++) {
		new_field.id[i] = (char*)malloc(maxY * sizeof(char));
	}

	srand(time(NULL));

	for (size_t i = 0; i < maxX; i++) {
		for (size_t j = 0; j < maxY; j++) {
			int rand_val = (float)rand() / (float)RAND_MAX * 100;

			if (i == 0 || i == maxX - 1 ||
				j == 0 || j == maxY - 1) {
				new_field.id[i][j] = WALL_SYMBOL;
			}
			else {
				if (rand_val < apples_per_cent) {	
					new_field.id[i][j] = APPLE_SYMBOL;
				}
				else {
					if (rand_val > apples_per_cent + walls_per_cent) {
						new_field.id[i][j] = EMPTY_SYMBOL;
					}
					else {
						new_field.id[i][j] = WALL_SYMBOL;
					}
				}
			}
		}
	}

	return new_field;
}








snake initial_position(field field_) {
	snake new_snake;

	new_snake.snake_length = 1;
	new_snake.snake_coord = (int **)malloc(sizeof(int *));
	new_snake.snake_coord[0] = (int *)malloc(2 * sizeof(int));
	new_snake.snake_direction = (int *)malloc(2 * sizeof(int));

	int x_coord;
	int y_coord;


	do {
		x_coord = 1 + ((float)rand() / (float)RAND_MAX *
			(field_.maxX - 2));
		y_coord = 1 + ((float)rand() / (float)RAND_MAX *
			(field_.maxY - 2));
	} while (collision_with_wall(field_, x_coord, y_coord));

	new_snake.snake_coord[0][0] = x_coord;
	new_snake.snake_coord[0][1] = y_coord;
	new_snake.snake_direction[0] = 1;
	new_snake.snake_direction[1] = 0;
	
	return new_snake;
}








int collision_with_wall (field field_, int x_coord, int y_coord) {
	if (x_coord > field_.maxX - 1 ||
		x_coord < 0) {
		return 1;
	}

	if (y_coord > field_.maxY - 1 ||
		y_coord < 0) {
		return 1;
	}

	if (field_.id[x_coord][y_coord] == WALL_SYMBOL) {
		return 1;
	}

	return 0;
}








int collision_with_snake (snake snake_, int x_coord, int y_coord) {
	for (size_t i = 2; i < snake_.snake_length; i++) {
		if(x_coord == snake_.snake_coord[i][0] &&
			y_coord == snake_.snake_coord[i][1]) {
			
			return 1;
		}
	}

	return 0;
}








int collision_with_apple (field field_, int x_coord, int y_coord) {
	if (field_.id[x_coord][y_coord] == APPLE_SYMBOL) {
		return 1;
	}

	return 0;
}








void change_snake_position (snake snake_) {
	for(size_t i = snake_.snake_length - 1; i > 0; i--) {
		snake_.snake_coord[i][0] = snake_.snake_coord[i - 1][0];
		snake_.snake_coord[i][1] = snake_.snake_coord[i - 1][1];
	}

	snake_.snake_coord[0][0] += snake_.snake_direction[0];
	snake_.snake_coord[0][1] += snake_.snake_direction[1];
	return;
}








void change_direction (int direction, snake snake_) {
	switch (direction) {
	case KEY_DOWN:
		if (snake_.snake_direction[1] == -1 ||
			snake_.snake_direction[1] == 1) {
			break;
		}

		snake_.snake_direction[0] = 0;
		snake_.snake_direction[1] = 1;
		break;

	case KEY_LEFT:
		if (snake_.snake_direction[0] == 1 ||
			snake_.snake_direction[0] == -1) {
			break;
		}

		snake_.snake_direction[0] = -1;
		snake_.snake_direction[1] = 0;
		break;

	case KEY_RIGHT:
		if (snake_.snake_direction[0] == -1 ||
			snake_.snake_direction[0] == 1) {
			break;
		}

		snake_.snake_direction[0] = 1;
		snake_.snake_direction[1] = 0;
		break;

	case KEY_UP:
		if (snake_.snake_direction[1] == 1 ||
			snake_.snake_direction[1] == -1) {
			break;
		}

		snake_.snake_direction[0] = 0;
		snake_.snake_direction[1] = -1;
		break;
	}

	return;
}








void eat_apple (snake *snake_, field field_) {
	srand(time(NULL));

	int new_x_coord;
	int new_y_coord;

	do {
	new_x_coord = ((float)rand() / 
		(float)RAND_MAX * (field_.maxX - 3));

	new_y_coord = ((float)rand() /
		(float)RAND_MAX * (field_.maxY - 3));

	} while (collision_with_apple(field_, new_x_coord, new_y_coord) ||
		FULL_SNAKE_COLLISION(*snake_, new_x_coord, new_y_coord) ||
		collision_with_wall(field_, new_x_coord, new_y_coord));

	field_.id[new_x_coord][new_y_coord] = APPLE_SYMBOL;
	field_.id[snake_->snake_coord[0][0]][snake_->snake_coord[0][1]] = EMPTY_SYMBOL;
	snake_->snake_length ++;
	
	int **tmp_snake_coord = (int**)malloc(snake_->snake_length * sizeof(int*));

	for(size_t i = 0; i < snake_->snake_length - 1; i++) {
		tmp_snake_coord[i] = (int*)malloc(2 * sizeof(int));
		tmp_snake_coord[i][0] = snake_->snake_coord[i][0];
		tmp_snake_coord[i][1] = snake_->snake_coord[i][1];
		free(snake_->snake_coord[i]);
	}

	tmp_snake_coord[snake_->snake_length - 1] =
		(int*)malloc(2 * sizeof(int));

	tmp_snake_coord[snake_->snake_length - 1][0] =
		tmp_snake_coord[snake_->snake_length - 2][0];

	tmp_snake_coord[snake_->snake_length - 1][1] =
		tmp_snake_coord[snake_->snake_length - 2][1];
	
	free(snake_->snake_coord);
	snake_->snake_coord = tmp_snake_coord;
	return;
}








static field copy_field (field field_) {
	field new_field;

	new_field.maxY = field_.maxY;
	new_field.maxX = field_.maxX;

	new_field.id = (char**)malloc(field_.maxX * sizeof(char*));

	for (size_t i = 0; i < field_.maxX; i++) {
		new_field.id[i] = (char*)malloc(field_.maxY * sizeof(char));

		for(size_t j = 0; j < field_.maxY; j++) {
			new_field.id[i][j] = field_.id[i][j];
		}
	}

	return new_field;
}








field menu (field field_)  {
	field_ = copy_field(field_);

	for (size_t i = 0; i < 10; i++) {
		field_.id[0][i] = '#';
		field_.id[16][i] = '#';
	}

	for (size_t i = 1; i < 16; i++) {
		field_.id[i][0] = '#';
		field_.id[i][2] = '#';
		field_.id[i][9] = '#';
	}

	char title[16] = "PAUSE          ";
	char menu[6][16] = {"Button|Function",
						"      |        ",
						"     1.save map",
						"     2.open map",
						"     3.new map ",
						"     4.exit    "};

	for (size_t i = 1; i < 16; i++) {
		field_.id[i][1] = title[i - 1];
	}

	for (size_t i = 3; i < 9; i++) {
		for (size_t j = 1; j < 16; j++) {
			field_.id[j][i] = menu[i - 3][j - 1];
		}
	}
	return field_;
}








field game_over(field field_, snake snake_) {
	field_ = copy_field(field_);

	for (size_t i = 0; i < 10; i++) {
		field_.id[0][i] = '#';
		field_.id[16][i] = '#';
	}

	for (size_t i = 1; i < 16; i++) {
		field_.id[i][0] = '#';
		field_.id[i][2] = '#';
		field_.id[i][9] = '#';
	}

	size_t snake_length = snake_.snake_length;
	char score[10];

	int_to_str(snake_length, score, 10);

	char title[16] = "GAME OVER      ";
	char menu[6][16] = {"Score:         ",
						"Button|Function",
						"      |        ",
						"     1.new map ",
						"     2.open map",
						"     3.exit    " };

	for (size_t i = 1; i < 16; i++) {
		field_.id[i][1] = title[i - 1];
	}

	for (size_t i = 7; i < 16 && score[i - 7] != '\0'; i++) {
		menu[0][i] = score[i - 7];
	}

	for (size_t i = 3; i < 9; i++) {
		for (size_t j = 1; j < 16; j++) {
			field_.id[j][i] = menu[i - 3][j - 1];
		}
	}
	return field_;
}








void map_saving (field field_, snake snake_) {
	FILE *new_file_ptr;

	if(fopen_s(&new_file_ptr, "save_0x00.snake", "w")) {
		return;
	}

	fprintf_s(new_file_ptr,"%d\n", field_.maxX);
	fprintf_s(new_file_ptr, "%d", field_.maxY);
	
	for (size_t i = 0; i < field_.maxX; i++) {
		for(size_t j = 0; j < field_.maxY; j++) {
			fprintf_s(new_file_ptr, "%c", field_.id[i][j]);
		}
	}
	
	fprintf_s(new_file_ptr, "%d\n", snake_.snake_length);

	for (size_t i = 0; i < snake_.snake_length; i++) {
		fprintf_s(new_file_ptr, "%d %d\n", snake_.snake_coord[i][0],
			snake_.snake_coord[i][1]);
	}

	fprintf_s(new_file_ptr, "%d %d", snake_.snake_direction[0],
		snake_.snake_direction[1]);

	fclose(new_file_ptr);
	return;
}








void open_map (field *field_, snake *snake_) {
	FILE* file_ptr;

	if(fopen_s(&file_ptr, "save_0x00.snake", "r")) {
		return;
	}
	
	fscanf_s(file_ptr, "%d", &(field_->maxX));
	fscanf_s(file_ptr, "%d", &(field_->maxY));
	field_->id = (char**)malloc(field_->maxX * sizeof(char*));
	
	for (size_t i = 0; i < field_->maxX; i++) {
		field_->id[i] = (char*)malloc(field_->maxY * sizeof(char));

		for (size_t j = 0; j < field_->maxY; j++) {
			fscanf_s(file_ptr, "%c", &(field_->id[i][j]));
		}
	}

	fscanf_s(file_ptr, "%d", &(snake_->snake_length));
	snake_->snake_coord = (int **)malloc(snake_->snake_length * sizeof(int *));
	
	for (size_t i = 0; i < snake_->snake_length; i++) {
		snake_->snake_coord[i] = (int*)malloc(2 * sizeof(int));
		fscanf_s(file_ptr, "%d %d", &(snake_->snake_coord[i][0]),
			&(snake_->snake_coord[i][1]));
	}

	snake_->snake_direction = (int*)malloc(2 * sizeof(int));
	fscanf_s(file_ptr, "%d %d", &(snake_->snake_direction[0]),
		&(snake_->snake_direction[1]));

	fclose(file_ptr);
	return;
}








void delete_field(field* field_) {

	for (size_t i = 0; i < field_->maxX; i++) {
		free(field_->id[i]);
	}

	free(field_->id);
	field_->maxX = 0;
	field_->maxY = 0;
	return;
}








void delete_snake(snake *snake_) {
	for (size_t i = 0; i < snake_->snake_length; i++) {
		free(snake_->snake_coord[i]);
	}

	free(snake_->snake_coord);
	free(snake_->snake_direction);
	snake_->snake_length = 0;
	return;
}