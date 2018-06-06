#include "map.h"

struct Block fb = {0x0000, false, false, 0};
struct Block w1b = {0x0004, true, true, 1};
struct Block w2b = {0x0008, true, true, 2};

struct Entity slime = {{0,0}, 1, 8, 1, 1, 1, 0};

struct Map getMap(int seed, int zone, int floor, struct Entity *e[MAXENEMIES]){
	struct Map m;

    for (int i = 0; i < MAXY; i++){
    	for (int j = 0; j < MAXX; j++){
    			int index = i*16 + j;
    			if (i <= 3 || i >= MAXY-3 || j <= 3 || j >= MAXX - 3){
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
    	int index = ny*16+nx;
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

void getScreenBlock(struct Map m, unsigned short *screenArray){
	for (int i = 0; i < MAXY; i++){
		for (int j = 0; j < MAXX; j++){
			int ind1 = i*64 + j*2;
			int ind2 = ind1 + 1;
			int ind3 = ind1 + 32;
			int ind4 = ind2 + 32;
			screenArray[ind1] = m.tileMap[i*16 + j].id;
			screenArray[ind2] = m.tileMap[i*16 + j].id+1;
			screenArray[ind3] = m.tileMap[i*16 + j].id+2;
			screenArray[ind4] = m.tileMap[i*16 + j].id+3;
		}
	}
}