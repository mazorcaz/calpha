// chunk.h

#ifndef CALPHA_CHUNK_H
#define CALPHA_CHUNK_H

#include <stdint.h>

struct chunk {
	int32_t x;
	int32_t z;

	uint8_t blocks[16 * 16 * 128];
	uint8_t states[16 * 16 * 64];
};

int chunk_render(struct chunk *chunk);
int chunk_mesh(struct chunk *chunk);

#endif
