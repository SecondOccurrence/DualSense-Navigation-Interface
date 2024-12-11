#include <stdlib.h>
#include <string.h>

#include "gui_utils.h"

void clear_menu(WINDOW* win, const int win_x, const int win_y) {
	char* blank_cell = malloc(win_x + 1);
	if(blank_cell == NULL) {
		perror("malloc");
		exit(0);
	}

	memset(blank_cell, ' ', win_x);
	blank_cell[win_x] = '\0';

	for(int i = 0; i < win_y; i++) {
		mvwprintw(win, i, 0, "%s", blank_cell);
	}

	free(blank_cell);
}

void draw_box_with_title(WINDOW* win, char* title, const int WIN_X, const int WIN_Y) {
	box(win, 0, 0);

	const int TITLE_LENGTH = strlen(title);
	const int TITLE_POS_X = (WIN_X - TITLE_LENGTH) / 2;
	const int TITLE_POS_Y = 0;

	mvwprintw(win, TITLE_POS_Y, TITLE_POS_X, "%s", title);
}
