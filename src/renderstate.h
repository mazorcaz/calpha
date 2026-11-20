// renderstate.h

#ifndef CALPHA_RENDERSTATE_H
#define CALPHA_RENDERSTATE_H

#include <GL/gl.h>

#include "mesh.h"

struct renderstate {
	struct mesh mesh;

	GLuint terrain;
};

int renderstate_init(struct renderstate *renderstate);
void renderstate_free(struct renderstate *renderstate);

#endif
