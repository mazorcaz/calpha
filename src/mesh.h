// mesh.h

#ifndef CALPHA_MESH_H
#define CALPHA_MESH_H

#include "dbuf.h"

struct mesh {
	struct dbuf buffer;
	int count; // number of vertices added
};

int mesh_init(struct mesh *mesh);
void mesh_free(struct mesh *mesh);

void mesh_reset(struct mesh *mesh);
int mesh_push(struct mesh *mesh, float x, float y, float z, float u, float v);

int mesh_cube_front(struct mesh *mesh, float x, float y, float z, float u, float v);
int mesh_cube_back(struct mesh *mesh, float x, float y, float z, float u, float v);
int mesh_cube_left(struct mesh *mesh, float x, float y, float z, float u, float v);
int mesh_cube_right(struct mesh *mesh, float x, float y, float z, float u, float v);
int mesh_cube_top(struct mesh *mesh, float x, float y, float z, float u, float v);
int mesh_cube_bottom(struct mesh *mesh, float x, float y, float z, float u, float v);

#endif
