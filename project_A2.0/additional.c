#include "additional.h"


void int_to_str (int input_int, char *buffer, size_t buffer_size) {
	int divider = 1;

	while (input_int / divider > 9) {
		divider *= 10;
	}

	int tmp = 0;

	for (size_t i = 0; i < buffer_size - 1 && divider > 0; i++) {
		buffer[i] = (char) (input_int / divider - tmp + 48);
		buffer[i + 1] = '\0';
		tmp = (input_int / divider) * 10;
		divider /= 10;
	}

	return;
}