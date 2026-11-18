// chunk.h

#ifndef CALPHA_CHUNK_H
#define CALPHA_CHUNK_H

#include <stdint.h>

struct world;
struct renderer;

struct chunk {
	int32_t x;
	int32_t z;

	uint8_t blocks[16 * 16 * 128];
	uint8_t states[16 * 16 * 64];

	struct chunk *next;
};

int chunk_render(struct chunk *chunk, struct world *world, struct renderer *renderer);
int chunk_mesh(struct chunk *chunk, struct world *world, struct renderer *renderer);

#endif
