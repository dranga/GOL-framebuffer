/* Demo originaly from stackoverflow
 * Framebuffer writting
 *  http://stackoverflow.com/questions/4996777/paint-pixels-to-screen-via-linux-framebuffer
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

int main()
{
    int fbfd = 0;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    long int screensize = 0;
    char *fbp = 0;
    int x = 0, y = 0;
    long int location = 0;

    // Open framebuffer for reading and writing
    fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1) {
        perror("Error: cannot open framebuffer device");
        exit(1);
    }
    printf("The framebuffer device was opened successfully.\n");

    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
        perror("Error reading fixed information");
        exit(2);
    }

    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("Error reading variable information");
        exit(3);
    }

    printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

    // Figure out the size of the screen in bytes
    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

    // Map the device to memory
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if ((int)fbp == -1) {
        perror("Error: failed to map framebuffer device to memory");
        exit(4);
    }
    printf("The framebuffer device was mapped to memory successfully.\n");
	//-----------------------------------------------------------------

	//start position
    x = 100; y = 100;       // Where we are going to put the pixel
    
	//printf("\e[?25l"); /* hide the cursor */
	fputs("\e[?25l",stdout);
	//close stdout
    //fclose(stdout);
    //fclose(stdin);


	//while(1){
    // Figure out where in memory to put the pixel
    //for (y = 100; y < 300; y++)
        //for (x = 100; x < 300; x++) {
	int i = 0;
	while (i<1000) {
        for(x = 0; x < vinfo.xres; x++) {
        	for(y = 0; y < vinfo.yres; y++) {
        	//given (x,y) compute memory location
			location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (y+vinfo.yoffset) * finfo.line_length;
        	
			//draw square
			if((y >= 100+i && y < 300+i) && (x >= 100+i && x < 300+i)) {

          	  if (vinfo.bits_per_pixel == 32) {
            	    *(fbp + location) = 100;        // Some blue
        	        *(fbp + location + 1) = 15+(x-100)/2;     // A little green
    	            *(fbp + location + 2) = 200-(y-100)/5;    // A lot of red
	                *(fbp + location + 3) = 0;      // No transparency
 	       			//location += 4;
	            } else  { //assume 16bpp
	                int b = 10;
	                int g = (x-100)/6;     // A little green
                	int r = 31-(y-100)/16;    // A lot of red
                	unsigned short int t = r<<11 | g << 5 | b;
                	*((unsigned short int*)(fbp + location)) = t;
            	}
            }
            else{
            //make black
            	if (vinfo.bits_per_pixel == 32) {
                	*(fbp + location) = 0;        // Some blue
                	*(fbp + location + 1) = 0;     // A little green
                	*(fbp + location + 2) = 0;    // A lot of red
                	*(fbp + location + 3) = 0;      // No transparency
        		//location += 4;
				}
        	}
        }
        }
    //}
	sleep(1);
	i=i+10;
}
    munmap(fbp, screensize);
 
    close(fbfd);
    getchar();
    printf("\e[?25h"); /* show the cursor */
    return 0;
}
