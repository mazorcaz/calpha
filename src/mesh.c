// mesh.c

#include "mesh.h"

int mesh_init(struct mesh *mesh)
{
	if (dbuf_init(&mesh->buffer, 256*5*sizeof(float))) return 1;
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
	mesh->buffer.len = 0;
}

int mesh_push(struct mesh *mesh, float x, float y, float z, float u, float v)
{
	float vertice[5] = {x, y, z, u, v};
	if (dbuf_addbuf(&mesh->buffer, (const uint8_t*)&vertice, 5*sizeof(float))) return 1;
	mesh->count++;
	return 0;
}

int mesh_cube_front(struct mesh *mesh, float x, float y, float z, float u, float v)
{
	if (mesh_push(mesh, x+0.0f, y+0.0f, z+1.0f, u+0/16.0f, v+1/16.0f)) return 1;
	if (mesh_push(mesh, x+1.0f, y+0.0f, z+1.0f, u+1/16.0f, v+1/16.0f)) return 1;
	if (mesh_push(mesh, x+1.0f, y+1.0f, z+1.0f, u+1/16.0f, v+0/16.0f)) return 1;
	if (mesh_push(mesh, x+0.0f, y+1.0f, z+1.0f, u+0/16.0f, v+0/16.0f)) return 1;
	return 0;
}

int mesh_cube_back(struct mesh *mesh, float x, float y, float z, float u, float v)
{
	if (mesh_push(mesh, x+1.0f, y+0.0f, z+0.0f, u+0/16.0f, v+1/16.0f)) return 1;
	if (mesh_push(mesh, x+0.0f, y+0.0f, z+0.0f, u+1/16.0f, v+1/16.0f)) return 1;
	if (mesh_push(mesh, x+0.0f, y+1.0f, z+0.0f, u+1/16.0f, v+0/16.0f)) return 1;
	if (mesh_push(mesh, x+1.0f, y+1.0f, z+0.0f, u+0/16.0f, v+0/16.0f)) return 1;
	return 0;
}

int mesh_cube_left(struct mesh *mesh, float x, float y, float z, float u, float v)
{
	if (mesh_push(mesh, x+0.0f, y+0.0f, z+1.0f, u+0/16.0f, v+1/16.0f)) return 1;
	if (mesh_push(mesh, x+0.0f, y+0.0f, z+0.0f, u+1/16.0f, v+1/16.0f)) return 1;
	if (mesh_push(mesh, x+0.0f, y+1.0f, z+0.0f, u+1/16.0f, v+0/16.0f)) return 1;
	if (mesh_push(mesh, x+0.0f, y+1.0f, z+1.0f, u+0/16.0f, v+0/16.0f)) return 1;
	return 0;
}
