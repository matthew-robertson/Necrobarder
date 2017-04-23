#ifndef MAP_H
#define MAP_H
#include "shared.h"

struct Block {
	unsigned short id;
	bool isWall;
	unsigned short health;

};

struct Map {
	struct Block tileMap[256];
};

struct Map getMap(int seed, int zone, int floor);
void getScreenBlock(struct Map m, unsigned short *screenArray);
#endif