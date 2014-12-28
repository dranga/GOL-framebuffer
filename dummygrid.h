#ifndef GRID_H
#define GRID_H

typedef struct grid {
	int gridXMax;
	int gridYMax;

} Grid_t;


void newDummyGrid(Grid_t *grid, int XMax, int YMax);

void GridPaintCell(Grid_t *grid, int x,int y, int red, int blue, int green, int transparency);

void ClearGrid(Grid_t *grid);

#endif