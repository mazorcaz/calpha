// chunk.c

#include "nibblearr.h"
#include "renderer.h"
#include "chunk.h"

int chunk_init(struct chunk *chunk, int32_t x, int32_t z)
{
	chunk->x = x;
	chunk->z = z;
	chunk->dirtymask = 255;
	for (int i=0; i<8; i++) {
		chunk->lists[i] = 0;
	}
	return 0;
}

void chunk_free(struct chunk *chunk)
{
	for (int i=0; i<8; i++) {
		glDeleteLists(chunk->lists[0], 8);
	}
}

uint16_t chunk_getblock(struct chunk *chunk, int x, int y, int z)
{
	int i = y + z * 128 + x * 16 * 128;
	return (uint16_t)chunk->blocks[i] | ((uint16_t)nibblearr_get(chunk->states, i) << 8);
}

void chunk_setblock(struct chunk *chunk, int x, int y, int z, uint16_t v)
{
	int i = y + z * 128 + x * 16 * 128;
	chunk->blocks[i] = v & 255;
	nibblearr_set(chunk->states, i, v >> 8);
}

int chunk_render(struct chunk *chunk, struct renderer *renderer,
	struct chunk *front, struct chunk *back, struct chunk *left, struct chunk *right)
{
	for (int i=0; i<8; i++) {
		if ((chunk->dirtymask >> i) & 1) {
			if (chunk_mesh(chunk, i, renderer, front, back, left, right)) return 1;
		}
		glCallList(chunk->lists[i]);
	}

	return 0;
}

int chunk_mesh(struct chunk *chunk, int section, struct renderer *renderer,
	struct chunk *front, struct chunk *back, struct chunk *left, struct chunk *right)
{
	mesh_reset(&renderer->mesh);

	for (int x=0; x<16; x++) {
		for (int y=0; y<16; y++) {
			for (int z=0; z<16; z++) {
				if (mesh_cube_front(&renderer->mesh, x + chunk->x, y + section * 16, z + chunk->z, 0, 0)) return 1;
			}
		}
	}

	if (!chunk->lists[section]) chunk->lists[section] = glGenLists(1);
	if (!chunk->lists[section]) return 1;

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 5 * sizeof(GLfloat), renderer->mesh.buffer.buf);
	glNewList(chunk->lists[section], GL_COMPILE);

	glDrawArrays(GL_QUADS, 0, renderer->mesh.count);

	glEndList();
	glDisableClientState(GL_VERTEX_ARRAY);

	return 0;
}
