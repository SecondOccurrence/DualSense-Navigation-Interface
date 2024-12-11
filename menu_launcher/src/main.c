#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <linux/input.h>
#include <limits.h>
#include <sys/select.h>

#include "general.h"
#include "controller_input.h"



#define SHARE_KEY 314 // Equivalent to dualsense share button
#define HOME_KEY 316 // Equivalent to dualsense playstation button

int main(void) {
	int event_num = wait_for_controller(DEVICE_NAME, POLL_INTERVAL);

	char device_name[NAME_MAX];
	snprintf(device_name, NAME_MAX, "%s/event%d", EVENT_DIR, event_num);

	int fd = open(device_name, O_RDONLY);
	if(fd == -1) {
		perror("open");
		return 1;
	}

	int terminal_open = 0;
	pid_t terminal_pid = -1;
	struct input_event ev;

	int share_pressed = 0;
	int home_pressed = 0;

	fd_set fds;
	while(1) {
		FD_ZERO(&fds);
		FD_SET(fd, &fds);

		struct timeval* tv = NULL;
		int retval = select(fd + 1, &fds, NULL, NULL, tv);

		if(retval == -1) {
			perror("select");
			break;
		}

		int nread = read(fd, &ev, sizeof(ev));
		if(nread == -1) {
			perror("read");
			break;
		}

		if(nread != sizeof(ev)) {
			continue;
		}

		if(ev.value == 1) {
			if(ev.code == SHARE_KEY) {
				share_pressed = 1;
			}
			else if(ev.code == HOME_KEY) {
				home_pressed = 1;
			}
			else if(share_pressed || home_pressed){
				share_pressed = 0;
				home_pressed = 0;
			}

			if(share_pressed && home_pressed) {
				toggle_terminal(&terminal_open, &terminal_pid);
			}
		}
		else if(ev.value == 0) {
			if(ev.code == SHARE_KEY) {
				share_pressed = 0;
			}
			else if(ev.code == HOME_KEY) {
				home_pressed = 0;
			}
		}
	}

	close(fd);
	return EXIT_SUCCESS;
}
