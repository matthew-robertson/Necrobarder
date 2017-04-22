#ifndef MAP_H
#define MAP_H
#include "shared.h"

struct Map {
	char grid[MAXX * MAXY] ;
};

struct Map getMap(int seed, int zone, int floor);
#endif