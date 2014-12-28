
#include <stdio.h>
#include "dummygrid.h"

//void newGrid(grid_t *grid, FrameBuffer_t *frame, int pixelPerXdiv, int pixelPerYdiv) {
void newDummyGrid(Grid_t *dummygrid, int XMax, int YMax) {
	dummygrid->gridXMax = XMax;
	dummygrid->gridYMax = YMax;
}

void GridPaintCell(Grid_t *grid, int x,int y, int red, int blue, int green, int transparency) {

	if(red == 255 || blue == 255 || green == 255) {
		printf("o");
	} else {
		printf(".");	
	}
}

void ClearGrid(Grid_t *grid) {
;
}