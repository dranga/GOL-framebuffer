
#include "grid.h"
#include "framebuffer.h"

//void newGrid(grid_t *grid, FrameBuffer_t *frame, int pixelPerXdiv, int pixelPerYdiv) {
void newGrid(Grid_t *grid, FrameBuffer_t *frame, int XPixelPerDiv, int YPixelPerDiv) {
	grid->frame = frame;
	grid->XPixelPerDiv = XPixelPerDiv;
	grid->YPixelPerDiv = YPixelPerDiv;
	grid->gridXMax = frame->xmax/XPixelPerDiv;
	grid->gridYMax = frame->ymax/YPixelPerDiv;
}

void GridPaintCell(Grid_t *grid, int x,int y, int red, int blue, int green, int transparency) {

	int xMax = (x + 1) * grid->XPixelPerDiv;
	int yMax = (y + 1) * grid->YPixelPerDiv;
	int border = 2;
	int frameX, frameY;
	for(frameX = x * grid->XPixelPerDiv + border; frameX < xMax - border; frameX++) {
		for(frameY = y * grid->YPixelPerDiv + border; frameY < yMax - border; frameY++) {
			FrameBufferWritePixel(grid->frame, frameX, frameY, red, blue, green, transparency);
		}
	}
}

void ClearGrid(Grid_t *grid) {
	int x, y;
	for (x = 0; x < grid->gridXMax; x++)
	{
		for (y = 0; y < grid->gridYMax; y++)
		{
			GridPaintCell(grid, x, y, 0, 0, 0, 0);
		}
	}
}