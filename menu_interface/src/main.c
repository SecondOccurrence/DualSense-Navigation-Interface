#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <limits.h>
#include <fcntl.h>

#include "gui.h"
#include "gui_utils.h"
#include "controller_input.h"

static void finish(int sig);

int main(int argc, char* argv[]) {
	int num = 0;

	signal(SIGINT, finish);

	initscr(); // initialise curses library
	noecho();
	cbreak(); // take input chars one at a time, no wait for \n
	curs_set(0);

	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLUE);

	int event_num = wait_for_controller(DEVICE_NAME, POLL_INTERVAL);

	char device_name[NAME_MAX];
	snprintf(device_name, NAME_MAX, "%s/event%d", EVENT_DIR, event_num);

	int fd = open(device_name, O_RDONLY | O_NONBLOCK);
	if(fd == -1) {
		perror("open");
		return 1;
	}
	
	int y_max, x_max;
	getmaxyx(stdscr, y_max, x_max);

	WINDOW* menu_window = newwin(y_max, x_max, 0, 0);
	draw_box_with_title(menu_window, " Menu ", x_max, y_max);
	wrefresh(menu_window);

	keypad(menu_window, TRUE); // enable keyboard mapping
	
	int option = menu_loop(menu_window, fd, x_max, y_max);
	
	endwin();

	if(option > 100) {
		printf("Changing display to display %d\n", option - 100);

		char switch_command[64];
		snprintf(switch_command, sizeof(switch_command), "qtile cmd-obj -o screen -f toggle_group -a %d", option - 100);
		system(switch_command);
	}
	else if(option == 1) {
		system("shutdown now");
	}
	else if(option == 2) {
		system("xrandr --output HDMI-4 --off");
	}

	return 0;
}

static void finish(int sig) {
	endwin();

	exit(0);
}
