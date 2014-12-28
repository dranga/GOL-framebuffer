#ifndef GRID_H
#define GRID_H

#include "framebuffer.h"

typedef struct grid {
	FrameBuffer_t *frame;
	int XPixelPerDiv;
	int YPixelPerDiv;
	int gridXMax;
	int gridYMax;

} Grid_t;


void newGrid(Grid_t *grid, FrameBuffer_t *frame, int XPixelPerDiv, int YPixelPerDiv);

void GridPaintCell(Grid_t *grid, int x,int y, int red, int blue, int green, int transparency);

void ClearGrid(Grid_t *grid);

#endif