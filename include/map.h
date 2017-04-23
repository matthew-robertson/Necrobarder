#ifndef MAP_H
#define MAP_H
#include "shared.h"

struct Map {
	const unsigned short map[2048];
};

struct Map getMap(int seed, int zone, int floor);
#endif