// renderer.c

#include <stdlib.h>

#include "window.h"
#include "renderer.h"

int renderer_init(struct renderer *renderer, struct window *window)
{
	renderer->window = window;

	if (!mesh_init(&renderer->mesh)) return 1;

	return 0;
}
