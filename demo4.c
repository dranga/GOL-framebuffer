/*
 *
 */


#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <time.h>

#include "framebuffer.h"
#include "grid.h"

int main()
{
	int fbfd = 0;

	FrameBuffer_t *frame;
	frame = malloc(sizeof(frame));

    Grid_t *grid;
    grid = malloc(sizeof(grid));


	FILE *stream;
	stream = stdout;

	struct termios old_termios, new_termios;

	// Open framebuffer for reading and writing
    fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1) {
        perror("Error: cannot open framebuffer device");
        exit(1);
    }

    
    //hide cursor
    fputs("\e[?25l",stdout);

    //turn off terminal behaviour
    if (tcgetattr (fileno (stream), &old_termios) != 0)
    	return -1;
	new_termios = old_termios;
	new_termios.c_lflag &= ~(ECHO);
	if (tcsetattr (fileno (stream), TCSAFLUSH, &new_termios) != 0)
		return -1;
	

    FrameBufferOpen(frame, fbfd);
    newGrid(grid, frame, 16, 16);

    srand(time(NULL));
    
    int x,y;
    for(x = 0; x < grid->gridXMax; x++) {
    	for(y = 0; y < grid->gridYMax; y++) {
    		GridPaintCell(grid, x, y, 0, 0, 0, 0);
    	}
    }

    for(x = 0; x < grid->gridXMax; x++) {
    	for(y = 0; y < grid->gridYMax; y++) {

            if((x % 2 == 0 && y % 2 == 1) || (x % 2 == 1 && y % 2 == 0)) {
                //GridPaintCell(grid, x, y, 255, 0, 0, 0);
		GridPaintCell(grid, x, y, rand()%255, rand()%255, rand()%255, 0);
            }
            else {
                //GridPaintCell(grid, x, y, 0, 255, 0, 0);
		GridPaintCell(grid, x, y, rand()%255, rand()%255, rand()%255, 0);
            }
    		
    	}
    }

    getchar();

    //perform clean up and show cursor
    FrameBufferClose(frame);
    close(fbfd);
    
    
    //turn on terminal behaviour
    (void) tcsetattr (fileno (stream), TCSAFLUSH, &old_termios);

    //show cursor
    fputs("\e[?25h",stdout);
	

    return 0;
}
