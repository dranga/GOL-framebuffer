#ifndef GOL_H
#define GOL_H

#include "grid.h"

typedef struct game {
	Grid_t *grid;
	int cycleSize;
	int stillLifeOscilation;
	int cycleTime;
	int red;
	int blue;
	int green;
	int transparency;
	char *previousCycle;
	char *currentCycle;
} Game_t;

void newGame(Game_t *game, Grid_t *grid, int fillPercentSeed);

void runGame(Game_t *game);

void drawCycle(Game_t *game);

void computeNextCycle(char *currentCycle, char *nextCycle, int size, int XMax, int YMax);

void fillCycleZeros(char *cycle, int size);

void fillCycleRand(char *cycle, int size, int fillPercent);

int cellLive(char *cycle, int val);

void printCurrentCycle(Game_t *game);
void printPreviousCycle(Game_t *game);
void printCycle(Game_t *game, char* cycle);

void cpyCycle(char *dest, char *src, int size);
int cmpCycle(char *srcA, char *srcB, int size);

#endif