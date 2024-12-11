#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/input.h>

#include "controller_input.h"

int get_controller_input(int fd) {
	struct input_event ev;
	while(1) {
		int nread = read(fd, &ev, sizeof(ev));
		if(nread == sizeof(ev)) {
			if(ev.type == EV_KEY && ev.value == 1) {
				return ev.code;
			}
		}
	}
}

int wait_for_controller(const char* NAME, const int INTERVAL) {
	int event_num;

	while(1) {
		event_num = find_controller(NAME);
		if(event_num != -1) {
			break;
		}

		sleep(INTERVAL);
	}

	return event_num;
}

int find_controller(const char* NAME) {
	DIR* dir = opendir("/dev/input");
	struct dirent* entry;
	char device_path[PATH_MAX];
	char device_name[NAME_MAX];
	int fd;

	if(!dir) {
		perror("opendir");
		return -1;
	}

	while((entry = readdir(dir)) != NULL) {
		if(strncmp(entry->d_name, "event", 5) != 0) {
			continue;
		}
		
		snprintf(device_path, PATH_MAX, "%s/%s", EVENT_DIR, entry->d_name);

		fd = open(device_path, O_RDONLY);
		if(fd == -1) {
			continue;
		}

		if(ioctl(fd, EVIOCGNAME(NAME_MAX), device_name) == -1) {
			perror("EVIOCGNAME");
			close(fd);
			continue;
		}

		if(strcmp(device_name, NAME) == 0) {
			int device_num = atoi(&entry->d_name[5]);

			close(fd);
			closedir(dir);
			return device_num;
		}
	}

	closedir(dir);
	return -1;
}
