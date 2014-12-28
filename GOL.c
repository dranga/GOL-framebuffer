
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h> 
//#include "dummygrid.h"
#include "grid.h"
#include "GOL.h"

void newGame(Game_t *game, Grid_t *grid, int fillPercentSeed) {

	int cycleSize = grid->gridXMax * grid->gridYMax /8;
	cycleSize = ((grid->gridXMax * grid->gridYMax) % 8)? cycleSize + 1: cycleSize;
	
	game->grid = grid;

	game->cycleSize = cycleSize;

	game->previousCycle = (char *) malloc(cycleSize * sizeof(char));
	fillCycleZeros(game->previousCycle, game->cycleSize);

	game->currentCycle = (char *) malloc(cycleSize * sizeof(char));
	fillCycleRand(game->currentCycle, game->cycleSize, fillPercentSeed);


	game->stillLifeOscilation = 3;
	game->cycleTime = 1; //sec
	game->red = 255;
	game->blue = 255;
	game->green = 255;
	game->transparency = 0;
	
	/*
	printf("stillLifeOscilation %d\n", game->stillLifeOscilation);
	printf("game->cycleSize %d\n", game->cycleSize);
	printf("game->cycleTime %d\n", game->cycleTime);
	printf("game->red %d\n", game->red);
	printf("game->green %d\n", game->green);
	printf("game->blue %d\n", game->blue);
	printf("game->transparency %d\n", game->transparency);
	*/
}

void runGame(Game_t *game){
	int stillLife;
	char *nextCycle = (char *) malloc(game->cycleSize * sizeof(char));
	fillCycleZeros(nextCycle, game->cycleSize);
	int stillLifeOscilation = game->stillLifeOscilation;

	int n = 0;
	drawCycle(game);
	sleep(game->cycleTime);
	do {
		stillLife = 0;
		n++;
		fillCycleZeros(nextCycle, game->cycleSize);
		//compute next cycle
		computeNextCycle(game->currentCycle, nextCycle, game->cycleSize, game->grid->gridXMax, game->grid->gridYMax);

		stillLife = (cmpCycle(game->currentCycle, nextCycle, game->cycleSize) == 0) || 
					cmpCycle(game->previousCycle, nextCycle, game->cycleSize) == 0;

		if(stillLife) {
			stillLifeOscilation--;
		}
		else {
			stillLifeOscilation = game->stillLifeOscilation;
		}

		/*
		printf("CURRENT CYCLE:\n");
		printCycle(game, game->currentCycle);

		printf("NEXT CYCLE:\n");
		printCycle(game, nextCycle);


		printf("PREVIOUS CYCLE:\n");
		printCycle(game, game->previousCycle);

		printf("-----------\n");
		*/

		cpyCycle(game->previousCycle, game->currentCycle, game->cycleSize);
		cpyCycle(game->currentCycle, nextCycle, game->cycleSize);

		/*
		printf(">>%d\n",n);
		printf("stillLifeOscilation %d\n", stillLifeOscilation);
		printf("stillLife %d\n", stillLife);
		*/

		drawCycle(game);

		sleep(game->cycleTime);
	}while(stillLifeOscilation > 0);
	free(nextCycle);
}

/**************/
void drawCycle(Game_t *game) {
	int x, y;
	int draw;

	for (x = 0; x < game->grid->gridXMax; x++) {
		for(y = 0; y < game->grid->gridYMax; y++) {

			draw = cellLive(game->currentCycle, x + y * game->grid->gridXMax);
			//check draw variable
			if(draw) {
				GridPaintCell( game->grid, x, y, game->red, game->blue, game->green, game->transparency);
			}
			else {
				GridPaintCell( game->grid, x, y, 0, 0, 0, 0);
			}
		}
		printf("\n");
	}
	printf("\n");
}

void computeNextCycle(char *currentCycle, char *nextCycle, int size, int XMax, int YMax) {
	int x, y, byteOffset;
	int neighborCount;
	int N, NE, NW, E, W, S, SE, SW;
	int crtCellLive;
	char *crtC = currentCycle; 
	for (x = 0; x < XMax; x++) {
		for(y = 0; y < YMax; y++) {

			byteOffset = (x + y * XMax) / 8;
			crtCellLive = cellLive(crtC, x + y * XMax);
			N = (x + (y - 1) * XMax);
			NE = ((x + 1) + (y - 1) * XMax);
			NW = ((x - 1) + (y - 1) * XMax);
			E = ((x + 1) + y * XMax);
			W = ((x - 1) + y * XMax);
			S = (x + (y + 1) * XMax);
			SE = ((x + 1) + (y + 1) * XMax);
			SW = ((x - 1) + (y + 1) * XMax);

			//printf("(%d,%d) byteOffset(%d) crtval(%d)\n N(%d) NE(%d) NW(%d)\n E(%d) W(%d)\n S(%d) SE(%d) SW(%d)\n", x, y, byteOffset, x + y * XMax, N, NE, NW, E, W, S, SE, SW);

			if(x == 0 && y == 0) {
				neighborCount = cellLive(crtC, E) +
								cellLive(crtC, S) +
								cellLive(crtC, SE);
			}
			else if(x == XMax - 1 && y == YMax - 1) {
				neighborCount = cellLive(crtC, N) +
								cellLive(crtC, NW) +
								cellLive(crtC, W);
			}
			else if(x == 0 && y == YMax - 1) {
				neighborCount = cellLive(crtC, N) +
								cellLive(crtC, NE) +
								cellLive(crtC, E);
			}
			else if(x == XMax - 1 && y == 0) {
				neighborCount = cellLive(crtC, W) +
								cellLive(crtC, S) +
								cellLive(crtC, SW);
			}
			else if(x == 0) {
				neighborCount = cellLive(crtC, N) +
								cellLive(crtC, NE) +
								cellLive(crtC, E) +
								cellLive(crtC, S) +
								cellLive(crtC, SE);
			}
			else if(y == 0) {
				neighborCount = cellLive(crtC, E) +
								cellLive(crtC, W) +
								cellLive(crtC, S) +
								cellLive(crtC, SE) +
								cellLive(crtC, SW);
			}
			else if(x == XMax - 1) {
				neighborCount = cellLive(crtC, N) +
								cellLive(crtC, NW) +
								cellLive(crtC, W) +
								cellLive(crtC, S) +
								cellLive(crtC, SW);
			}
			else if(y == YMax - 1) {
				neighborCount = cellLive(crtC, N) +
								cellLive(crtC, NE) +
								cellLive(crtC, NW) +
								cellLive(crtC, E) +
								cellLive(crtC, W);
			}
			else {
				neighborCount = cellLive(crtC, N) +
								cellLive(crtC, NE) +
								cellLive(crtC, NW) +
								cellLive(crtC, E) +
								cellLive(crtC, W) +
								cellLive(crtC, S) +
								cellLive(crtC, SE) +
								cellLive(crtC, SW);
			}

			//printf("(%d,%d) crtCellLive(%d) neighborCount(%d)",x,y,crtCellLive,neighborCount);

			if((crtCellLive == 1 && (neighborCount == 2 || neighborCount == 3)) ||
				(crtCellLive == 0 && neighborCount == 3)) {
				//printf("cell lives to next cycle\n\n");
				//printf("new live cell!\n previous val : %d new val: %d\n\n", nextCycle[byteOffset], nextCycle[byteOffset] | (1 << (x + y * XMax) % 8));
				nextCycle[byteOffset] = nextCycle[byteOffset] | (1 << (x + y * XMax) % 8); 
			}
			else {
				nextCycle[byteOffset] = nextCycle[byteOffset] | (0 << (x + y * XMax) % 8);
				//printf("\n\n");
			}
		}
	}
}

void fillCycleZeros(char *cycle, int size) {
	int i;
	for(i = 0; i < size; i++) {
		cycle[i] = '\0';
	}
}

void fillCycleRand(char *cycle, int size, int fillPercent) {
	int i;
	for(i = 0; i < size; i++) {
		cycle[i] = (unsigned char)(rand()%100 < fillPercent)?(rand() % 255):0;
	}
}

int cellLive(char *cycle, int val) {
	return (cycle[val/8] >> val % 8) & 1;
}

//for debug with dummy grid
void printCycle(Game_t *game, char* cycle) {
	int x, y, draw;
	for (x = 0; x < game->grid->gridXMax; x++) {
		for(y = 0; y < game->grid->gridYMax; y++) {

			draw = cellLive(cycle, x + y * game->grid->gridXMax);
			
			if(draw == 1) {
				GridPaintCell( game->grid, x, y, game->red, game->blue, game->green, game->transparency);
			}
			else {
				GridPaintCell( game->grid, x, y, 0, 0, 0, 0);
			}
		}
		printf("\n");
	}
	printf("\n");
}

//for debug with dummy grid
void printPreviousCycle(Game_t *game) {
	printCycle( game, game->previousCycle);
}

//for debug with dummy grid
void printCurrentCycle(Game_t *game) {
	printCycle( game, game->currentCycle);
}

void cpyCycle(char *dest, char *src, int size) {
	int i;
	for(i = 0; i < size; i++){
		dest[i] = src[i];
	}
}

int cmpCycle(char *srcA, char *srcB, int size) {
	int i;
	int val = 0;
	for(i = 0; i < size; i++){
		if(srcA[i] != srcB[i]) {
			val = 1;
			break;
		}
	}

	return val;
}