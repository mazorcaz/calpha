// chunk.h

#ifndef CALPHA_CHUNK_H
#define CALPHA_CHUNK_H

#include <stdint.h>
#include <GL/gl.h>

struct window;
struct renderstate;

struct chunk {
	int32_t x;
	int32_t z;

	uint8_t blocks[16 * 16 * 128];
	uint8_t states[16 * 16 * 64];

	uint8_t dirtymask;
	GLuint lists[8];

	struct chunk *next;
};

int chunk_init(struct chunk *chunk, int32_t x, int32_t z);
void chunk_free(struct chunk *chunk);

uint16_t chunk_getblock(struct chunk *chunk, int x, int y, int z);
void chunk_setblock(struct chunk *chunk, int x, int y, int z, uint16_t v);

int chunk_render(struct chunk *chunk, struct window *window, struct renderstate *rs,
	struct chunk *front, struct chunk *back, struct chunk *left, struct chunk *right);

int chunk_mesh(struct chunk *chunk, int section, struct window *window, struct renderstate *rs,
	struct chunk *front, struct chunk *back, struct chunk *left, struct chunk *right);

#endif
