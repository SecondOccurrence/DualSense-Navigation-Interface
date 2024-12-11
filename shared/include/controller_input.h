#ifndef CONTROLLER_INPUT_H
#define CONTROLLER_INPUT_H

#define EVENT_DIR "/dev/input"
#define DEVICE_NAME "Wireless Controller"
#define POLL_INTERVAL 3

int wait_for_controller(const char* NAME, const int INTERVAL);

int find_controller(const char* NAME);

int get_controller_input(int fd);

#endif
