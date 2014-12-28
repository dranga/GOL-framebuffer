framebuffer-GOL
===============

Conway's Game of Life [(Wikipedia)](http://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) implemented with the Linux framebuffer.

This is a fun little experiment written in C, barebones writting to the Linux framebuffer device. The Game of Life is mesmerizing and the Linux framebuffer makes for a good canvas. 

If errors occur when starting the program, you may have a different system as mine and the framebuffer may have another name. See the 'How to Use Files and Modify' section.

**WARNING** : Sudo is required to run the program
**WARNING** : Writting to the framebuffer could break things like the display system (it has not happened to me) and would require restarting, save any work in progress. But it's fun.

###How to Compile and Run
1. Move into a virtual TTY with `ctrl + F1-6`  and Log in.
2. Move into game's directory (using `cd`)
3. Run `make playgame`
4. To run game, `sudo bin/playgame`

###How to Use Files and Modify

#### Different Graphics Configuration
If you have a different graphic chipset or a graphics card/chip you may not have `/dev/fb0`, however the program can still be used with a slight modification. First, check if any other fb device exists by running `ls /dev/fb*`, this will list fb devices. If one exists replace it in playgame.c on the line `fbfd = open("/dev/fb0", O_RDWR);`. If a graphics chip/card is present the framebuffer will be named differently: e.g. with an Nvidia chip the framebuffer device may be `/dev/nvfb`; running `ls /dev/*fb*` might display all framebuffer devices.

#### Other Colors
The display color can be changed by modifying the red, blue and green values in GOL.c in the newGame function, in the red, blue, green elements in the game struct.

#### Bigger/Smaller Grid Elements
Cells (unit elements) can be increased/decreased by modifying the `int gridsize = 16` line in playgame.c to the desired number (powers of 2 prefered).

#### Initial Seed Percentage
Initial population can be changed by modifying the `int seedpop = 20;` line in playgame.c to the desired number (from 1 to 99).

#### Slower/Faster changes and Longer Wait Times Before Quitting After a Still-Life
Changing the refresh rate can be done by modifying the cycleTime element of the game struct in GOL.c in the newGame function.

Similarly, the number of still-life/oscilatory generations to display before quiting can be changed by modifying the stillLifeOscilation element of the game struct in GOL.c in the newGame function.

#### Development
4 demos are available, showing some initial starting points and progress using the framebuffer and grid modules. Compiling these can be done through make

Dummygrid.c is used to debug the game, printing the grid as characters in the terminal instead of to framebuffer, just replace grid.c and .h by dummygrid.c and .h .
