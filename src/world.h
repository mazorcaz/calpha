// world.h

#ifndef CALPHA_WORLD_H
#define CALPHA_WORLD_H

struct chunk;

struct world {
	struct chunk *chunks[256]; // chunk hash table
};

#endif
