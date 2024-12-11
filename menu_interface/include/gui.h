#ifndef GUI_H
#define GUI_H

#include <ncurses.h>

#include "button.h"
#include "menu.h"

#define NUM_MENUS 4
#define NUM_MAIN_OPTIONS 3
#define NUM_DISPLAY_OPTIONS 6
#define NUM_CONFIRM_OPTIONS 2

#define BACK 305
#define CONFIRM 304
#define UP 310
#define DOWN 311

int menu_loop(WINDOW* win, int input_fd, const int win_x, const int win_y);

void initialise_menu(struct menu_container menus[NUM_MENUS]);

#endif
