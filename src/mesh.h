// mesh.h

#ifndef CALPHA_MESH_H
#define CALPHA_MESH_H

#include "dbuf.h"

struct vertice {
	float x, y, z;
	float u, v;
};

struct mesh {
	struct dbuf buffer;
	int count; // number of vertices added
};

int mesh_init(struct mesh *mesh);
void mesh_free(struct mesh *mesh);

void mesh_reset(struct mesh *mesh);
int mesh_push(struct mesh *mesh, struct vertice vertice);

#endif
