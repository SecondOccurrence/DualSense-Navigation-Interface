# Project Description

I use an old monitor of mine as a TV. Naturally, a monitor like that does not have a remote or menu that I can interact with from away from the monitor or my keyboard & mouse. So, rather than get up every time to say, turn it off, I've made an interface that works with a PS5 DualSense controller which, for now, performs very basic tasks.

This was designed specific to my computer configuration. I use linux, so a lot of the code uses linux system calls. Reading input from a wireless controller is done reading device files found in `/dev/input`. As for the menu interface, the configuration for the terminal window that holds the interface is done in a configuration file for the Window Manager that I use, Qtile.

This repository consists of 2 programs. One for the actual menu interface, the other which listens for the shortcut combination to open/close the menu. The latter is designed to be ran as a background process.

# Building the Project

This was built using cmake. In the root directory of this repository, run `cmake -S . -B build`. The interface executable is found at `./build/menu_interface/interface`, the launcher at `./build/menu_launcher/launcher`

## Interface

*The launcher will call this executable. It assumes that it is located at `/usr/local/bin/`. I have a custom wrapper script which will call the executable, as I had an odd issue where the window dimensions ncurses calculated were incorrect when calling the program as an argument in the `exec` call. Below is the wrapper script i use.*

### `/usr/local/bin/controller_menu.sh`
```bash
#!/bin/bash

resize
exec /usr/local/bin/container/controller_menu
```


This was made using ncurses. I've went for a crude, but pleasantly nostalgic look for this interface. It represents the kind of menu you would see on old TVs, and other electronics. It currently consists of 3 options

### 1. Change Display

As mentioned before, this solution is specific to my computer. I have 6 possible 'groups' to choose from. These are hard-coded in. As I use Qtile, this option calls a qtile command to switch displays:
```bash
qtile cmd-obj -o screen -f toggle_group -a X
```
- where X represents the name of the group to switch to. The names of these groups are numbers.

### 2. Shut Down

Shuts down the computer using `shutdown now`

### 3. Turn Off Monitor

Will turn off the monitor using `xrandr`. Again, this is specific to my computers configuration. The "TV" monitor is connected through HDMI-4.

## Launcher

I have this executable launch as a background process every time the monitor is turned on. That process is killed when the monitor turns off, to avoid duplicate processes.

This program begins by searching for a device under the name `Wireless Controller`, in `/dev/input/`. After each search, it will wait 3 seconds if no match. Once the device is found, the program will wait for 2 buttons to be pressed. On the DualSense controller, I have chosen the SHARE button and PLAYSTATION button in combination, as you dont frequently press both of those at the same time.

Pressing them once spawns a terminal that runs the menu, pressing them again sends SIGTERM to the terminal, closing it.

As I mentioned in the [Project Description](#project-description), I use qtile configuration file to set dimensions and positions to the terminal that holds the interface. For completeness sake, below shows a snippet from that configuration file.

*As this will apply for all windows under the name `Alacritty`, I have dedicated this terminal for the menu. I use a different one for other tasks.*

```python
@hook.subscribe.client_new
def floating_alacritty(client):
	if "Alacritty" in client.get_wm_class():
		client.keep_above()
		client.enable_floating()
		client.toscreen(2)
```
