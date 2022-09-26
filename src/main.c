#include "../inc/header.h"

int mx_random_range(int min, int max) {
	return rand() % (max - min + 1) + min;
}

char mx_get_random_char() {
	return mx_random_range(33, 126);
}

bool mx_is_printable(char c) {
	return c >= 33 && c <= 126 ? true : false;
}

void mx_print_matrix(t_cell **matrix, t_vector2 size, int color) {
	for (int x = 0; x < size.x; x++) {
		for (int y = 0; y < size.y; y++) {
			if (y + 1 < size.y && matrix[x][y + 1].symbol == ' ') {
				attrset(COLOR_PAIR(1));
			} else {
				attrset(COLOR_PAIR(color));
			}
			char a = matrix[x][y].symbol;
			mvaddch(y, x, a);
		}
	}
	refresh();
}

void mx_print_Neo(char *str) {
	for (int i = 0; str[i] != '\0'; i++) {
		/*if (getch() != 'q') {*/
			mvaddch(0, i, str[i] | COLOR_PAIR(COLOR_GREEN));
			refresh();
			if (str[i] != ' ')
				sleep(1);
			else sleep(0);
		/*}
		else {
			endwin();
			exit(0);
		}*/
	}
	clear();
}

int main() {
	t_vector2 matrix_size;

	srand(time(NULL));

	initscr();
	raw();
	start_color();
	curs_set(0);

	int color = 2;
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_RED, COLOR_BLACK);
	
	getmaxyx(stdscr, matrix_size.y, matrix_size.x);

	t_cell **matrix = malloc(matrix_size.x * sizeof(t_cell *));
	for (int x = 0; x < matrix_size.x; x++) {
		matrix[x] = malloc(matrix_size.y * sizeof(t_cell));
		for (int y = 0; y < matrix_size.y; y++) {
			matrix[x][y].symbol = ' ';
			matrix[x][y].life = 0;
		}
	}

	char *greetings1 = "Wake up , Neo";
	char *greetings2 = "The Matrix has you..." ;
	char *greetings3 = "Follow the white rabbit";
	char *greetings4 = "Knock , knock , Neo";

	mx_print_Neo(greetings1);
	mx_print_Neo(greetings2);
	mx_print_Neo(greetings3);
	mx_print_Neo(greetings4);

	int speed = 100;
	while (true) {
		wtimeout(stdscr, speed);

		switch (getch()) {
			case 'w':
				if ((speed - 30) > 0) {
					speed -= 30;
				}
				break;

			case 's':
				if ((speed + 30) <= 300) {
					speed += 30;
				}
				break;

			case '1':
				color = 1;
				break;

			case '2':
				color = 2;
				break;

			case '3':
				color = 3;
				break;

			case '4':
				color = 4;
				break;

			case '5':
				color = 5;
				break;	

			case 'q':
				endwin();
				exit(0);
		}

		char random_char = mx_get_random_char();
		t_vector2 random_position = {mx_random_range(0, matrix_size.x - 1), 0};
		matrix[random_position.x][random_position.y].symbol = random_char;
		matrix[random_position.x][random_position.y].life = 6;
		for (int x = 0; x < matrix_size.x; x++) {
			for (int y = matrix_size.y - 1; y >= 0; y--) {
				if (y + 1 < matrix_size.y && matrix[x][y + 1].symbol == ' ' && matrix[x][y].symbol != ' ') {
					matrix[x][y + 1].symbol = mx_get_random_char();
					matrix[x][y + 1].life = mx_random_range(0, 10);
				}
				if (matrix[x][y].life <= 0) {
					matrix[x][y].symbol = ' ';
				}
			}
		}

		for (int x = 0; x < matrix_size.x; x++) {
			for (int y = 0; y < matrix_size.y; y++) {
				if (matrix[x][y].symbol != ' ') {
					matrix[x][y].life--;
				}
			}
		}
		mx_print_matrix(matrix, matrix_size, color);
		//refresh();
	}

	return 0;
}

