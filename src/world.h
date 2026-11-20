// world.h

#ifndef CALPHA_WORLD_H
#define CALPHA_WORLD_H

#include "chunk.h"

struct window;
struct mesh;

struct world {
	struct chunk *chunks[256]; // chunk hash table

	struct chunk chunk; // TEMPORARY
};

int world_init(struct world *world);
void world_free(struct world *world);

int world_render(struct world *world, struct window *window, struct mesh *mesh, struct resources *resources);

#endif
