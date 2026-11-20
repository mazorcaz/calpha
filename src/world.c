// world.c

#include <stddef.h>

#include "chunk.h"
#include "world.h"
#include "window.h"

void set_perspective(int width, int height)
{
	if (height == 0) height = 1;
	double aspect = (double)width / (double)height;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	double near = 0.1;
	double far = 100.0;
	double top = near * 0.4142;
	double bottom = -top;
	double right = top * aspect;
	double left = -right;

	glFrustum(left, right, bottom, top, near, far);
}

int world_init(struct world *world)
{
	if (chunk_init(&world->chunk, 0, 0)) return 1;
	return 0;
}

void world_free(struct world *world)
{
	chunk_free(&world->chunk);
}

int world_render(struct world *world, struct window *window, struct renderstate *rs)
{
	set_perspective(window->width, window->height);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(-8.0f, -64.0f, -64.0f);

	if (chunk_render(&world->chunk, window, rs, NULL, NULL, NULL, NULL)) return 1;
	return 0;
}
