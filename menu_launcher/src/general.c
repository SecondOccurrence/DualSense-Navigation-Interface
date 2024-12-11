#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "general.h"

void toggle_terminal(int* terminal_open, int* terminal_pid) {
	if(*terminal_open) {
		if(*terminal_pid > 0) {
			kill(*terminal_pid, SIGTERM);
			waitpid(*terminal_pid, NULL, 0);
			*terminal_pid = -1;
		}
		*terminal_open = 0;
	}
	else {
		*terminal_pid = fork();
		if(*terminal_pid == 0) {
			execlp("alacritty", "alacritty", "-e", "/usr/local/bin/controller_menu.sh", NULL);
			exit(0);
		}
		else if(*terminal_pid < 0) {
			perror("fork");
		}
		*terminal_open = 1;
	}
}









