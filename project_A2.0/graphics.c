#include "graphics.h"


int classify_event () {
	if (KeyPressed() != 0) {
		return GetKey();
	}

	return 0;
}








void renew_screen(field field_, snake snake_, int snake_mode) {
	
	for (size_t i = 0; i < field_.maxX; i++) {
		for (size_t j = 0; j < field_.maxY; j++) {
			GotoXY(i, j);

			switch (field_.id[i][j]) {
			case WALL_SYMBOL:
				SetColor(WALL_COLOR);
				break;
			case APPLE_SYMBOL:
				SetColor(APPLE_COLOR);
				break;
			}

			if(!FULL_SNAKE_COLLISION(snake_, i, j) || !snake_mode) {
				putchar(field_.id[i][j]);
			}
			
		}
	}

	if (snake_mode) {
		for (size_t i = 0; i < snake_.snake_length; i++) {
			GotoXY(snake_.snake_coord[i][0], snake_.snake_coord[i][1]);
			SetColor(SNAKE_COLOR);
			putchar(SNAKE_SYMBOL);
		}
	}

	return;
}








void timeout() {
	Sleep(TIMEOUT);
	return;
}