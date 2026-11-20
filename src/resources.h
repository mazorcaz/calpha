// resources.h

#ifndef CALPHA_RESOURCES_H
#define CALPHA_RESOURCES_H

#include <GL/gl.h>

struct resources {
	GLuint terrain;
};

int resources_init(struct resources *resources);
void resources_free(struct resources *resources);

#endif
