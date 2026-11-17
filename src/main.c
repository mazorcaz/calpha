// main.c

#include <GL/gl.h>
#include <stdio.h>
#include <unistd.h>

#include "window.h"

int main()
{
	struct window w;
	if (window_init(&w)) return 1;

	while (!w.closed) {
		window_handle_events(&w);

		window_before_draw(&w);

		glClearColor(0.0f, 0.1f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		window_after_draw(&w);

		usleep(16000);
	}

	window_free(&w);

	return 0;
}
