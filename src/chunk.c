// chunk.c

#include "nibblearr.h"
#include "mesh.h"
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
		if (chunk->lists[i]) glDeleteLists(chunk->lists[i], 1);
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

int chunk_render(struct chunk *chunk, struct mesh *mesh,
	struct chunk *front, struct chunk *back, struct chunk *left, struct chunk *right)
{
	for (int i=0; i<8; i++) {
		if ((chunk->dirtymask >> i) & 1) {
			if (chunk_mesh(chunk, i, mesh, front, back, left, right)) return 1;
		}
		glCallList(chunk->lists[i]);
	}

	return 0;
}

int chunk_mesh(struct chunk *chunk, int section, struct mesh *mesh,
	struct chunk *front, struct chunk *back, struct chunk *left, struct chunk *right)
{
	mesh_reset(mesh);

	int xo = chunk->x*16;
	int yo = section*16;
	int zo = chunk->z*16;

	for (int x=0; x<16; x++) {
		for (int y=0; y<16; y++) {
			for (int z=0; z<16; z++) {
				if (mesh_cube_front(mesh, x + xo, y + yo, z + zo, 0, 0)) return 1;
			}
		}
	}

	if (!chunk->lists[section]) chunk->lists[section] = glGenLists(1);
	if (!chunk->lists[section]) return 1;

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, GL_FLOAT, 5 * sizeof(GLfloat), mesh->buffer.buf);
	glTexCoordPointer(2, GL_FLOAT, 5 * sizeof(GLfloat), (float *)mesh->buffer.buf + 3);
	glNewList(chunk->lists[section], GL_COMPILE);

	glDrawArrays(GL_QUADS, 0, mesh->count);

	glEndList();
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	chunk->dirtymask &= ~(1 << section);

	return 0;
}
