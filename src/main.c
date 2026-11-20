// main.c

#include <GL/gl.h>
#include <stdio.h>
#include <unistd.h>

#include "renderstate.h"
#include "window.h"
#include "world.h"

int main()
{
	struct window window;
	if (window_init(&window, 800, 600)) return 1;

	struct renderstate rs;
	if (renderstate_init(&rs)) return 1;

	struct world world;
	if (world_init(&world)) return 1;

	struct event event;
	while (!window.closed) {
		while (window_next_event(&window, &event)) {
			if (event.type == EVENT_WINDOW_RESIZE) {
				glViewport(0, 0, window.width, window.height);
			} else if (event.type == EVENT_MOUSE_DOWN && event.button == 2) {
				window_close(&window);
			}
		}

		window_before_draw(&window);

		glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		world_render(&world, &window, &rs);

		window_after_draw(&window);

	}

	world_free(&world);
	renderstate_free(&rs);
	window_free(&window);

	return 0;
}
