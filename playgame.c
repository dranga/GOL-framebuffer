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
#include "GOL.h"

int main()
{
	int fbfd = 0;
    int gridsize = 32;
    int seedpop = 20;

	FrameBuffer_t *frame;
	frame = malloc(sizeof(FrameBuffer_t));

    Grid_t *grid;
    grid = malloc(sizeof(Grid_t));

    Game_t *game;
    game = malloc(sizeof(Game_t));


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
	
    srand(time(NULL));

    
    FrameBufferOpen(frame, fbfd);
    newGrid(grid, frame, gridsize, gridsize);
    newGame(game, grid, seedpop);

    runGame(game);
    
    //perform clean up and show cursor
    FrameBufferClose(frame);
    close(fbfd);
    
    free(game);
    free(grid);
    free(frame);
    
    //turn on terminal behaviour
    (void) tcsetattr (fileno (stream), TCSAFLUSH, &old_termios);

    //show cursor
    fputs("\e[?25h",stdout);
	//printf("DONE\n");

    return 0;
}
