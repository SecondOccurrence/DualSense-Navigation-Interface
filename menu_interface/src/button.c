#include <ncurses.h>
#include <string.h>

#include "button.h"

struct button create_button(int x, int y, const char str[MAX_NAME_LENGTH]) {
	struct button btn;

	btn.pos_x = x;
	btn.pos_y = y;
	
	size_t len = strlen(str);
	strncpy(btn.text, str, len);
	btn.text[len] = '\0';

	return btn;
}

void display_buttons(WINDOW* win, struct button buttons[], const int NUM_BUTTONS, const int SELECTED_OPTION, const int MAX_POS_X) {
	const int HIGHLIGHT_LENGTH = MAX_POS_X - 2;
	int highlight_pos_x = 1;
	int highlight_pos_y;
	for(int i = 0; i < NUM_BUTTONS; i++) {
		highlight_pos_y = i + 1;

		mvwprintw(win, buttons[i].pos_y, buttons[i].pos_x, "%s", buttons[i].text);

		if(i == SELECTED_OPTION) {
			mvwchgat(win, highlight_pos_y, highlight_pos_x, HIGHLIGHT_LENGTH, COLOR_PAIR(1), 1, NULL);
		}
		else {
			mvwchgat(win, highlight_pos_y, highlight_pos_x, HIGHLIGHT_LENGTH, A_STANDOUT, 0, NULL);
		}
	}
}
