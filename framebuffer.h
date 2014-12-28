#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <linux/fb.h>

typedef struct framebuffer{
	int framebufferfd;
	struct fb_fix_screeninfo finfo;
	struct fb_var_screeninfo vinfo;
	char *fb_memp;

	long int xmax;
	int xoffset;
	long int ymax;
	int yoffset;
	int bpp; //bits per pixel
	long int screensize;
} FrameBuffer_t;

//typedef struct framebuffer FrameBuffer;

void FrameBufferOpen(FrameBuffer_t *frame, int framebufferfd);

void FrameBufferWritePixel(FrameBuffer_t *frame, long int x, long int y, int red, int blue, int green, int transparency);

void FrameBufferClose(FrameBuffer_t *frame);

long int FrameBufferLocation(FrameBuffer_t *frame, long int x, long int y);

#endif