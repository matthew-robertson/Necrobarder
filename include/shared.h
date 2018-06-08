#ifndef SHARED_H
#define SHARED_H

#include <stdbool.h>
#include <stdlib.h>

typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned int       uint32;

typedef uint32 Tile[16];
typedef Tile   TileBlock[256];
typedef uint16 ScreenBlock[1024];

#define VIDEOMODE_0    0x0000
#define ENABLE_OBJECTS 0x1000
#define MAPPINGMODE_1D 0x0040

#define REG_DISPLAYCONTROL      (*(volatile uint16*) 0x04000000)

#define MEM_VRAM      ((volatile uint16*)0x6000000)
#define MEM_TILE      ((TileBlock*)MEM_VRAM)
#define se_mem        ((ScreenBlock*)MEM_VRAM)
#define MEM_SP_PALETTE   ((uint16*)(0x05000200))
#define MEM_BG_PALETTE   ((uint16*)(0x05000000))
#define SCREEN_W      240
#define SCREEN_H      160

typedef struct ObjectAttributes {
    uint16 attr0;
    uint16 attr1;
    uint16 attr2;
    uint16 pad;
} __attribute__((packed, aligned(4))) ObjectAttributes;

#define MEM_OAM       ((volatile ObjectAttributes *)0x07000000)

#define KEY_A        0x0001
#define KEY_B        0x0002
#define KEY_SELECT   0x0004
#define KEY_START    0x0008
#define KEY_RIGHT    0x0010
#define KEY_LEFT     0x0020
#define KEY_UP       0x0040
#define KEY_DOWN     0x0080
#define KEY_R        0x0100
#define KEY_L        0x0200

#define MAXX 32
#define MAXY 32
#define SCREENMAXX 16
#define SCREENMAXY 16
#define MAXHEARTS 5
#define MAXENEMIES 16

struct Pos{
	int x;
	int y;
};

struct Block {
	char id;
	bool isWall;
	bool isOccupied;
	char health;

};

extern struct Block fb;
extern struct Block w1b;
extern struct Block w2b;

#endif