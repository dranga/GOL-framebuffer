
#include <stdlib.h>
#include <stdio.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include "framebuffer.h"


 void FrameBufferOpen(FrameBuffer_t *frame, int framebufferfd) {

	// Get fixed screen information
    if (ioctl(framebufferfd, FBIOGET_FSCREENINFO, &(frame->finfo)) == -1) {
        perror("Error: failed to read fixed information");
        exit(21);
    }

    // Get variable screen information
    if (ioctl(framebufferfd, FBIOGET_VSCREENINFO, &(frame->vinfo)) == -1) {
        perror("Error: failed to read variable information");
        exit(22);
    }


    //get framebuffer information
    
    frame->xmax = frame->vinfo.xres;
    frame->ymax = frame->vinfo.yres;
    frame->bpp = frame->vinfo.bits_per_pixel;

    // Figure out the size of the screen in bytes
    frame->screensize = frame->xmax * frame->ymax * frame->bpp / 8;

    //printf("%dx%d, %dbpp\n", frame->xmax, frame->ymax, frame->bpp);

    // Map the device to memory
    frame->fb_memp = (char *)mmap(0, frame->screensize, PROT_READ | PROT_WRITE, MAP_SHARED, framebufferfd, 0);
    if ((int)(frame->fb_memp) == -1) {
        perror("Error: failed to map framebuffer device to memory");
        exit(23);
    }
}

void FrameBufferWritePixel(FrameBuffer_t *frame, long int x, long int y, int red, int blue, int green, int transparency) {

	long int location = FrameBufferLocation(frame, x, y);
	//32 bits per pixel paint
	if (frame->bpp == 32) {
	    *(frame->fb_memp + location) = blue;        // blue
	    *(frame->fb_memp + location + 1) = green;     // green
	    *(frame->fb_memp + location + 2) = red;    // red
	    *(frame->fb_memp + location + 3) = transparency;      // transparency
	}
	//assume 16 bits per pixel paint 
	else  {
		unsigned short int temp = red<<11 | green << 5 | blue;
		*((unsigned short int*)(frame->fb_memp + location)) = temp;
	}
}

/* FrameBufferClose
 * Clean up
 */
void FrameBufferClose(FrameBuffer_t *frame) {
	munmap(frame->fb_memp, frame->screensize);
}

/* FrameBufferLocation
 * returns an int, memory byte-offset of framebuffer location (X,Y)
 *
 */
long int FrameBufferLocation(FrameBuffer_t *frame, long int x, long int y) {
	long int location;
	//location = (x + frame->vinfo.xoffset) * (frame->vinfo.bits_per_pixel/8) +
    //                   (y+frame->vinfo.yoffset) * frame->finfo.line_length;
    location = (x + frame->xoffset) * (frame->bpp/8) +
                       (y+frame->yoffset) * frame->finfo.line_length;

    return location;
}