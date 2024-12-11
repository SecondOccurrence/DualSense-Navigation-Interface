#include <ncurses.h>
#include <stdlib.h>

#include "gui.h"
#include "button.h"
#include "menu.h"
#include "controller_input.h"

static int process_choice(int* in_sub_menu, int* current_menu, int* highlight, int* saved_highlight) {
	int user_choice;

	*in_sub_menu = 0;
	if(*current_menu == 1) {
		// Changing display

		// To distinguish between display return and other menu options return
		//   As there is overlap between options 2 and 3 and change display to 2 or 3
		user_choice = 100 + *highlight + 1;
	}
	else if(*current_menu == 2 || *current_menu == 3) {
		if(*highlight == 1) { // No option pressed. Do not proceed
			*current_menu = 0;
			*in_sub_menu = 0;
			*highlight = *saved_highlight; // using menu highlight as this menus highlight is just confirming
			user_choice = -1;
		}
		else {
			user_choice = *saved_highlight; // using menu highlight as this menus highlight is just confirming
		}
	}

	return user_choice;
}

int menu_loop(WINDOW* win, int input_fd, const int win_x, const int win_y) {
	struct menu_container menus[NUM_MENUS];

	int input;
	int highlight = 0;
	int saved_highlight;
	int current_menu = 0;

	int in_sub_menu = 0;

	int user_choice;


	initialise_menu(menus);

	while(1) {
		display_menu(win, menus[current_menu], highlight, win_x, win_y);
		wrefresh(win);

		input = get_controller_input(input_fd);

		if(input == UP || input == 'k') {
			highlight -= 1;
		}
		else if(input == DOWN || input == 'j') {
			highlight += 1;
		}

		if(highlight == -1) {
			highlight = menus[current_menu].option_count - 1;
		}
		if(highlight == menus[current_menu].option_count) {
			highlight = 0;
		}

		if(in_sub_menu && input == BACK) {
			current_menu = 0;
			in_sub_menu = 0;
			highlight = saved_highlight;
		}

		if(input == CONFIRM) {
			if(in_sub_menu == 0) {
				current_menu = highlight + 1;
				saved_highlight = highlight;

				in_sub_menu = 1;
				if(saved_highlight != 0) {
					highlight = 1;
				}
				else {
					highlight = 0;
				}
			}
			else {
				user_choice = process_choice(&in_sub_menu, &current_menu, &highlight, &saved_highlight);
				if(user_choice != -1) {
					break;
				}
			}
		}
	}

	for(int i = 0; i < NUM_MENUS; i++) {
		if(menus[i].options != NULL) {
			free(menus[i].options);
		}
	}

	return user_choice;
}

static void create_buttons(struct button options[], const int num_options, const char* labels[]) {
	int opt_pos_x = 1;
	int opt_pos_y;
	for(int i = 0 ; i < num_options; i++) {
		opt_pos_y = i + 1;
		options[i] = create_button(opt_pos_x, opt_pos_y, labels[i]);
	}
}

static void init_main_menu(struct menu_container* menu, const char* title) {
	struct button options[NUM_MAIN_OPTIONS];

	const char* option_labels[NUM_MAIN_OPTIONS] = {
		" Change Display ",
		" Shut Down ",
		" Turn Off Monitor ",
	};

	create_buttons(options, NUM_MAIN_OPTIONS, option_labels);
	create_menu(menu, title, options, NUM_MAIN_OPTIONS);
}

// TODO: show in grid with 2 cols?
static void init_display_menu(struct menu_container* menu, const char* title) {
	struct button options[NUM_DISPLAY_OPTIONS];

	const char* option_labels[NUM_DISPLAY_OPTIONS] = {
		" 1 ", " 2 ", " 3 ", " 4 ", " 5 ", " 9 "
	};

	create_buttons(options, NUM_DISPLAY_OPTIONS, option_labels);
	create_menu(menu, title, options, NUM_DISPLAY_OPTIONS);
}


static void init_confirm_menu(struct menu_container* menu, const char* title) {
	struct button options[NUM_CONFIRM_OPTIONS];

	const char* option_labels[NUM_CONFIRM_OPTIONS] = {
		"Yes", "No"
	};

	create_buttons(options, NUM_CONFIRM_OPTIONS, option_labels);
	create_menu(menu, title, options, NUM_CONFIRM_OPTIONS);
}

void initialise_menu(struct menu_container menus[NUM_MENUS]) {
	init_main_menu(&menus[0], " Menu ");
	init_display_menu(&menus[1], " Change Display ");
	init_confirm_menu(&menus[2], " Shut Down ");
	init_confirm_menu(&menus[3], " Turn Off Monitor ");
}
