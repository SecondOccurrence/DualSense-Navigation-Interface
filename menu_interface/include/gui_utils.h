#ifndef GUI_UTILS_H
#define GUI_UTILS_H

#include <ncurses.h>

void clear_menu(WINDOW* win, const int win_x, const int win_y);

void draw_box_with_title(WINDOW* win, char* title, const int WIN_X, const int WIN_Y);

#endif
