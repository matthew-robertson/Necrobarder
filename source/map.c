#include "map.h"

struct Block fb = {0x0000, false, false, 0};
struct Block w1b = {0x0004, true, true, 1};
struct Block w2b = {0x0008, true, true, 2};

struct Entity slime = {{0,0}, 1, 8, 1, 1, 1, 0};

struct Map getMap(int seed, int zone, int floor, struct Entity *e[MAXENEMIES]){
	struct Map m;

    for (int i = 0; i < MAXY; i++){
    	for (int j = 0; j < MAXX; j++){
    			int index = i*MAXX + j;
    			if (i <= 4 || i >= MAXY-4 || j <= 7 || j >= MAXX - 7){
    				if (index % 3 == 0){
    					m.tileMap[index] = w2b;
    				} else{
    					m.tileMap[index] = w1b;
    				}
    			} else{
    				m.tileMap[index] = fb;
    			}
    	}
    }

    for (int i = 0; i < MAXENEMIES; i++){
    	int nx = 9;//rand() % MAXX;
    	int ny = 9;//rand() % MAXY;
    	int index = ny*MAXX+nx;
    	/*while (m.tileMap[index].isWall != false || m.tileMap[index].isWall != false ){
    		nx = rand() % MAXX;
    		ny = rand() % MAXY;
    	}*/

    	m.tileMap[index].isOccupied = true;
    	//e[i] = slime;
    	e[i]->pos.x = nx;
    	e[i]->pos.y = ny;
    }

	return m;
}

void getScreenBlock(struct Map m, unsigned short *screenArray, struct Pos playerPos){
	for (int i = 0; i < SCREENMAXY; i++){
		for (int j = 0; j < SCREENMAXX; j++){
			int ind1 = i*64 + j*2;
			int ind2 = ind1 + 1;
			int ind3 = ind1 + 32;
			int ind4 = ind2 + 32;
			screenArray[ind1] = m.tileMap[(i + playerPos.y - 4)*MAXX + (j + playerPos.x - 7)].id;
			screenArray[ind2] = m.tileMap[(i + playerPos.y - 4)*MAXX + (j + playerPos.x - 7)].id+1;
			screenArray[ind3] = m.tileMap[(i + playerPos.y - 4)*MAXX + (j + playerPos.x - 7)].id+2;
			screenArray[ind4] = m.tileMap[(i + playerPos.y - 4)*MAXX + (j + playerPos.x - 7)].id+3;
		}
	}
}