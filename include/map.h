#ifndef MAP_H
#define MAP_H
#include "shared.h"
#include "entity.h"

struct Map {
	struct Block tileMap[256];
};

// Given a random seed as well as a target floor,
// Generates the random floor as required.
struct Map getMap(int seed, int zone, int floor, struct Entity *e[MAXENEMIES]);

// Given a map and an output array of length 1024, it fills the array with
// The appropriate ids for rendering as a background
void getScreenBlock(struct Map m, unsigned short *screenArray);
#endif