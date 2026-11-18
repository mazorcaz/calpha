// mesh.c

#include "mesh.h"

int mesh_init(struct mesh *mesh)
{
	if (dbuf_init(&mesh->buffer, 256*sizeof(struct vertice))) return 1;
	mesh->count = 0;
	return 0;
}

void mesh_free(struct mesh *mesh)
{
	dbuf_free(&mesh->buffer);
}

void mesh_reset(struct mesh *mesh)
{
	mesh->count = 0;
}

int mesh_push(struct mesh *mesh, struct vertice vertice)
{
	if (dbuf_addbuf(&mesh->buffer, (const uint8_t*)&vertice, sizeof(vertice))) return 1;
	mesh->count++;
	return 0;
}
