
#ifndef ENTITY_H
#define ENTITY_H
#include "shared.h"

struct Entity{
	struct Pos pos;
	unsigned short health;
	unsigned short maxHealth;
	unsigned short digStrength;
	unsigned short sprite;
	unsigned short movementPattern;
};
#endif
