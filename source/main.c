
#include <gba_console.h>
#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_input.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shared.h"
#include "map.h"
#include "mapTiles.h"
#include "testSprite.h"

inline void vsync()
{
    while (REG_VCOUNT >= 160);
    while (REG_VCOUNT < 160);
}


struct Pos{
	int x;
	int y;
};

struct actor{
	struct Pos pos;
	int health;
};

struct Pos updatePlayerPos( uint16 keys){
	struct Pos diff = {0,0};
	if (keys & KEY_RIGHT){
		diff.x += 1;
	}
	if (keys & KEY_LEFT){
		diff.x -= 1;
	}

	if (keys & KEY_UP){
		diff.y -= 1;
   	}

	if (keys & KEY_DOWN){
		diff.y += 1;
   	}

    return diff;
}

int main()
{
    memcpy(MEM_SP_PALETTE, spritePal,  spritePalLen );
	memcpy(MEM_BG_PALETTE, bgPal,  bgPalLen );
    memcpy(&MEM_TILE[4][1], spriteTiles, spriteTilesLen);
    memcpy(&MEM_TILE[0][0], dfloor, bgTileLen);
    memcpy(&MEM_TILE[0][1], wallU, bgTileLen);
    memcpy(&MEM_TILE[0][2], wallB, bgTileLen);

    REG_BG0CNT = 0x1F83;
//    memcpy(&MEM_TILE[0][0], dfloor, 3*bgTileLen);
    struct Map t = getMap(0,0,0);
    unsigned short screenBlock[1024];
    getScreenBlock(t, screenBlock);
    memcpy(&se_mem[31], screenBlock, 2048);
//    REG_BG0HOFS = 0;
//    REG_BG0VOFS = 0;

    volatile ObjectAttributes *spriteAttribs = &MEM_OAM[0];

    spriteAttribs->attr0 = 0x2032; // 8bpp tiles, SQUARE shape, at y coord 50
    spriteAttribs->attr1 = 0x4064; // 16x16 size when using the SQUARE shape
    spriteAttribs->attr2 = 2;      // Start at the first tile in tile

    REG_DISPLAYCONTROL =  VIDEOMODE_0 | ENABLE_OBJECTS | MAPPINGMODE_1D | 0x0100;

    struct Pos p = {8, 8};
    //bool updateNeeded = true;
    while(1)
    {
    	scanKeys();
    	uint16 keys = keysDown();
    	struct Pos np = updatePlayerPos(keys);

    	if (np.x != 0 || np.y != 0){
    		if (!(np.x < 0 && p.x == 0) && !(np.x > 0 && p.x == MAXX)){
    			if (!(t.tileMap[p.y*MAXX + p.x + np.x].isWall)){
    				p.x += np.x;
    			}
    		}
    		if (!(np.y < 0 && p.y == 0) && !(np.y > 0 && p.y == MAXY)){
    			if (!(t.tileMap[(p.y+np.y)*MAXX + p.x].isWall)){
    				p.y += np.y;
    			}
    		}

    		//updateNeeded = true;
    	}
    	REG_BG0HOFS = (p.x - 7) * 16;
    	REG_BG0VOFS = (p.y - 4) * 16;
    	//if (updateNeeded){
        	vsync();
        	spriteAttribs->attr0 = 0x2000 | (0x00FF & (4 * 16)); 
        	spriteAttribs->attr1 = 0x4000 | (0x1FF & (7 * 16));
        	//updateNeeded = false;
        //}

    }
    return 0;
}