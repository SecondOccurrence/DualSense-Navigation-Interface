#ifndef MENU_H
#define MENU_H

#include <ncurses.h>

#include "button.h"

struct menu_container {
	char title[MAX_NAME_LENGTH];
	int option_count;
	struct button* options;
};

void create_menu(struct menu_container* menu, const char TITLE[MAX_NAME_LENGTH], struct button options[], const int OPTION_COUNT);

void display_menu(WINDOW* win, struct menu_container menu, const int SELECTED_OPTION, const int MAX_POS_X, const int MAX_POS_Y);

#endif
