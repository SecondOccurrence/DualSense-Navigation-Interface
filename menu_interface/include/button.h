#ifndef BUTTON_H
#define BUTTON_H

#include <ncurses.h>

#define MAX_NAME_LENGTH 64

struct button {
	int pos_x;
	int pos_y;
	char text[MAX_NAME_LENGTH];
};

struct button create_button(int x, int y, const char str[MAX_NAME_LENGTH]);

void display_buttons(WINDOW* win, struct button buttons[], const int NUM_BUTTONS, const int SELECTED_OPTION, const int MAX_POS_X);

#endif
