
#include <gba_console.h>
#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_input.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shared.h"
#include "entity.h"
#include "map.h"
#include "mapTiles.h"
#include "sprites.h"

struct Map t;
struct Entity p = {{8,8}, 3, 1};
bool playerMoved = false;
bool tileChanged = false;

inline void vsync()
{
    while (REG_VCOUNT >= 160);
    while (REG_VCOUNT < 160);
}

volatile ObjectAttributes * healthAttribs [5];
void initUI(){
	// Set up Health
	for (int i = 0; i < 5; i++){
		healthAttribs[i] = &MEM_OAM[i+1];
		healthAttribs[i]->attr0 = 0x2002; // 8bpp tiles, SQUARE shape, at y coord 50
		unsigned short xCoord = 16 * i;
    	healthAttribs[i]->attr1 = 0x4000 + xCoord; // 16x16 size when using the SQUARE shape
    	if (i <= p.health){
    		healthAttribs[i]->attr2 = 0xA;      // What tile to start at. 2 means [4][1]
    	} else {
    		healthAttribs[i]->attr2 = 0x12;
    	}
	}
}

void updatePlayerHealth(unsigned short diff){
	if (-diff >= p.health){
		p.health = 0;
	} else{
		p.health += diff;
	}

	for (int i = 0; i < 5; i++){
		healthAttribs[i] = &MEM_OAM[i+1];
		healthAttribs[i]->attr0 = 0x2002; // 8bpp tiles, SQUARE shape, at y coord 50
		unsigned short xCoord = 16 * i;
    	healthAttribs[i]->attr1 = 0x4000 + xCoord; // 16x16 size when using the SQUARE shape
    	if (i <= p.health){
    		healthAttribs[i]->attr2 = 0xA;      // What tile to start at. 2 means [4][1]
    	} else {
    		healthAttribs[i]->attr2 = 0x12;
    	}
	}
}

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

// Updates the world based on the player's input for the turn.
void playerTurn(struct Pos np){
	// We want to deal with every combination of inputs	
	if (np.x == 1 && np.y == 1){
		updatePlayerHealth(-1);
	} else if (np.x == 1 && np.y == -1){

	} else if (np.x == -1 && np.y == 1){

	} else if (np.x == -1 && np.y == -1){
		updatePlayerHealth(1);
	} else {
		// For x-axis motion and y-axis motion, ensure we aren't trying to go out of bounds
		// then ensure we can actually move into the tile (it isn't occupied or a wall)
		if (!(np.x < 0 && p.pos.x == 0) && !(np.x > 0 && p.pos.x == MAXX)){
			if (!(t.tileMap[p.pos.y*MAXX + p.pos.x + np.x].isWall) && !(t.tileMap[p.pos.y*MAXX + p.pos.x + np.x].isOccupied)){
				t.tileMap[p.pos.y*MAXX + p.pos.x].isOccupied = false;
				p.pos.x += np.x;
				t.tileMap[p.pos.y*MAXX + p.pos.x].isOccupied = true;
			} else {
				unsigned short bhealth = t.tileMap[p.pos.y*MAXX + p.pos.x + np.x].health;
				if (p.digStrength >= bhealth){
					t.tileMap[p.pos.y*MAXX + p.pos.x + np.x] = fb;
					tileChanged = true;
				}
			}
		}
		if (!(np.y < 0 && p.pos.y == 0) && !(np.y > 0 && p.pos.y == MAXY)){
			if (!(t.tileMap[(p.pos.y+np.y)*MAXX + p.pos.x].isWall) && !(t.tileMap[(p.pos.y+np.y)*MAXX + p.pos.x].isOccupied)){
				t.tileMap[p.pos.y*MAXX + p.pos.x].isOccupied = false;
				p.pos.y += np.y;
				t.tileMap[p.pos.y*MAXX + p.pos.x].isOccupied = true;
			} else {
				unsigned short bhealth = t.tileMap[(p.pos.y+np.y)*MAXX + p.pos.x].health;
				if (p.digStrength >= bhealth){
					t.tileMap[(p.pos.y+np.y)*MAXX + p.pos.x] = fb;
					tileChanged = true;
				}
			}
		}
	}
}

int main()
{
	// Upload the object and background palettes.
    memcpy(MEM_SP_PALETTE, spritePal,  spritePalLen );
	memcpy(MEM_BG_PALETTE, bgPal,  bgPalLen );
	// Upload sprite tiles to the first sprite page (page 5)
    memcpy(&MEM_TILE[4][1], bard, spriteTilesLen);
    memcpy(&MEM_TILE[4][5], fullHeart, spriteTilesLen);
    memcpy(&MEM_TILE[4][9], emptyHeart, spriteTilesLen);

    // Upload bg tiles to the first page
    memcpy(&MEM_TILE[0][0], dfloor, bgTileLen);
    memcpy(&MEM_TILE[0][4], wallU, bgTileLen);
    memcpy(&MEM_TILE[0][8], wallB, bgTileLen);

    // Set up the bg0 control address and initialize the map
    REG_BG0CNT = 0x1F83;
    t = getMap(0,0,0);
    unsigned short screenBlock[1024];
    getScreenBlock(t, screenBlock);
    memcpy(&se_mem[31], screenBlock, 2048);

    initUI();

    volatile ObjectAttributes *spriteAttribs = &MEM_OAM[0];

    spriteAttribs->attr0 = 0x2032; // 8bpp tiles, SQUARE shape, at y coord 50
    spriteAttribs->attr1 = 0x4064; // 16x16 size when using the SQUARE shape
    spriteAttribs->attr2 = 2;      // What tile to start at. 2 means [4][1]

    REG_DISPLAYCONTROL =  VIDEOMODE_0 | ENABLE_OBJECTS | MAPPINGMODE_1D | 0x0100;

    while(1)
    {
    	scanKeys();
    	uint16 keys = keysDown();
    	struct Pos np = updatePlayerPos(keys);

    	if (np.x != 0 || np.y != 0){
    		playerMoved = true;
    		playerTurn(np);
    		//updateNeeded = true;
    	}
    	REG_BG0HOFS = (p.pos.x - 7) * 16;
    	REG_BG0VOFS = (p.pos.y - 4) * 16;

    	if (playerMoved){
    		playerMoved = false;
    	}

    	if (tileChanged){
    		getScreenBlock(t, screenBlock);
    		memcpy(&se_mem[31], screenBlock, 2048);
    		tileChanged = false;
    	}
    	//if (updateNeeded){
        	vsync();
        	spriteAttribs->attr0 = 0x2000 | (0x00FF & (4 * 16)); 
        	spriteAttribs->attr1 = 0x4000 | (0x1FF & (7 * 16));
        	//updateNeeded = false;
        //}

    }
    return 0;
}