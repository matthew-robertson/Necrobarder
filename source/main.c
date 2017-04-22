
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

    volatile ObjectAttributes *spriteAttribs = &MEM_OAM[0];

    spriteAttribs->attr0 = 0x2032; // 8bpp tiles, SQUARE shape, at y coord 50
    spriteAttribs->attr1 = 0x4064; // 16x16 size when using the SQUARE shape
    spriteAttribs->attr2 = 2;      // Start at the first tile in tile

    REG_DISPLAYCONTROL =  VIDEOMODE_0 | ENABLE_OBJECTS | MAPPINGMODE_1D;

    struct Pos p = {0, 0};
    bool updateNeeded = true;
    while(1)
    {
    	scanKeys();
    	uint16 keys = keysDown();
    	struct Pos np = updatePlayerPos(keys);

    	if (np.x != 0 || np.y != 0){
    		if (!(np.x < 0 && p.x == 0) && !(np.x > 0 && p.x == MAXX)){
    			p.x += np.x;
    		}
    		if (!(np.y < 0 && p.y == 0) && !(np.y > 0 && p.y == MAXY)){
    			p.y += np.y;
    		}

    		updateNeeded = true;
    	}
    	if (updateNeeded){
        	vsync();
        	spriteAttribs->attr0 = 0x2000 | (0x00FF & (4 * 16)); 
        	spriteAttribs->attr1 = 0x4000 | (0x1FF & (7 * 16));
        	updateNeeded = false;
        }

    }
    return 0;
}