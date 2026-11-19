// renderer.c

#include <stdlib.h>

#include "window.h"
#include "renderer.h"
#include "world.h"

int renderer_init(struct renderer *renderer)
{
	if (mesh_init(&renderer->mesh)) return 1;

	return 0;
}

void renderer_free(struct renderer *renderer)
{
	mesh_free(&renderer->mesh);
}

int renderer_render(struct renderer *renderer, struct window *window, struct world *world)
{
	window_before_draw(window);

	glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(-0.5f, -0.5f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(0.5f, -0.5f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(0.0f, 0.5f);
	glEnd();

	window_after_draw(window);

	return 0;
}
