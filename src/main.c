// main.c

#include <GL/gl.h>
#include <stdio.h>
#include <unistd.h>

#include "window.h"
#include "renderer.h"
#include "chunk.h"

int main()
{
	struct window w;
	if (window_init(&w, 800, 600)) return 1;

	struct renderer renderer;
	if (renderer_init(&renderer)) return 1;

	struct chunk chunk;
	if (chunk_init(&chunk, 0, 0)) return 1;

	struct event event;
	while (!w.closed) {
		while (window_next_event(&w, &event)) {
			if (event.type == EVENT_WINDOW_RESIZE) {
				printf("resize %dx%d\n", w.width, w.height);
				glViewport(0, 0, w.width, w.height);
			} else if (event.type == EVENT_MOUSE_DOWN && event.button == 2) {
				window_close(&w);
			}
		}

		window_before_draw(&w);

		renderer_render(&renderer, &w, NULL);

		chunk_render(&chunk, &renderer, NULL, NULL, NULL, NULL);

		window_after_draw(&w);

	}

	chunk_free(&chunk);
	renderer_free(&renderer);
	window_free(&w);

	return 0;
}
