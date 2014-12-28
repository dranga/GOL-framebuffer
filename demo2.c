/* Demo originaly from stackoverflow
 * Hiding terminal output using termios lib
 * 
 * http://stackoverflow.com/questions/6856635/hide-password-input-on-terminal
 */
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <termios.h>

//#include <fcntl.h>
//#include <linux/fb.h>
//#include <sys/mman.h>
//#include <sys/ioctl.h>

int main()
{
	FILE *stream;
	stream = stdin;

	struct termios old_termios, new_termios;

	fputs("\e[?25l",stdout);
		
	/* Turn echoing off and fail if we can't. */
	if (tcgetattr (fileno (stream), &old_termios) != 0)
    	return -1;
	new_termios = old_termios;
	new_termios.c_lflag &= ~ECHO;
	if (tcsetattr (fileno (stream), TCSAFLUSH, &new_termios) != 0)
		return -1;

	/*********************************************/
	/* DO STUFF*/
	getchar();
	/*********************************************/

	/* Restore terminal. */
	(void) tcsetattr (fileno (stream), TCSAFLUSH, &old_termios);
	printf("\e[?25h"); /* show the cursor */
	return 0;
}