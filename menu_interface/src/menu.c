#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include "menu.h"
#include "button.h"
#include "gui_utils.h"

void create_menu(struct menu_container* menu, const char TITLE[MAX_NAME_LENGTH], struct button options[], const int OPTION_COUNT) {
	const int TITLE_LENGTH = strlen(TITLE);
	strncpy(menu->title, TITLE, TITLE_LENGTH);
	menu->title[TITLE_LENGTH] = '\0';

	menu->option_count = OPTION_COUNT;
	menu->options = malloc(menu->option_count * sizeof(struct button));
	for(int i = 0; i < menu->option_count; i++) {
		menu->options[i] = create_button(options[i].pos_x, options[i].pos_y, options[i].text);
	}
}

void display_menu(WINDOW* win, struct menu_container menu, const int SELECTED_OPTION, const int MAX_POS_X, const int MAX_POS_Y) {
	clear_menu(win, MAX_POS_X, MAX_POS_Y);
	draw_box_with_title(win, menu.title, MAX_POS_X, MAX_POS_Y);

	display_buttons(win, menu.options, menu.option_count, SELECTED_OPTION, MAX_POS_X);
}
