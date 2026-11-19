// chunk.c

#include "renderer.h"
#include "chunk.h"

int chunk_init(struct chunk *chunk, int32_t x, int32_t z)
{
	chunk->x = x;
	chunk->z = z;
	chunk->dirtymask = 255;
	return 0;
}

uint16_t chunk_getblock(struct chunk *chunk, int x, int y, int z)
{
	int i = y + z * 128 + x * 16 * 128;
	uint16_t block = chunk->blocks[i];
	uint16_t state = (chunk->states[i >> 1] >> (i & 1) * 8) & 15;
	return block | (state << 8);
}

void chunk_setblock(struct chunk *chunk, int x, int y, int z, uint16_t v)
{
	int i = y + z * 128 + x * 16 * 128;
	chunk->blocks[i] = v & 255;
	chunk->states[i >> 1] = (chunk->states[i >> 1] & (255 << (~i & 1) * 8)) | (((v >> 8) & 15) << (i & 1) * 8);
	chunk->dirtymask |= 1 << (y / 16);
}

int chunk_render(struct chunk *chunk, struct renderer *renderer,
	struct chunk *front, struct chunk *back, struct chunk *left, struct chunk *right)
{
	if (chunk->dirtymask) {
		for (int i=0; i<8; i++) {
			if ((chunk->dirtymask >> i) & 1) {
				if (chunk_mesh(chunk, i, renderer, front, back, left, right)) return 1;
			}
		}
	}
	return 0;
}

int chunk_mesh(struct chunk *chunk, int section, struct renderer *renderer,
	struct chunk *front, struct chunk *back, struct chunk *left, struct chunk *right)
{
	for (int x=0; x<16; x++) {
		for (int y=0; y<16; y++) {
			for (int z=0; z<16; z++) {
				
			}
		}
	}

	return 0;
}
