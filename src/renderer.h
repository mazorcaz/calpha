// renderer.h

#ifndef CALPHA_RENDERER_H
#define CALPHA_RENDERER_H

#include <stdint.h>

#include "mesh.h"

struct window;

#define RENDERER_BUFFER_SZ (256*128*64)

struct renderer {
	struct window *window;

	struct mesh mesh;
};

int renderer_init(struct renderer *renderer, struct window *window);
void renderer_free(struct renderer *renderer);

int renderer_render(struct renderer *renderer);

#endif
