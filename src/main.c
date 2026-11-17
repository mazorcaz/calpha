// main.c

#include <GL/gl.h>
#include <stdio.h>
#include <unistd.h>

#include "window.h"

int main()
{
	struct window w;
	if (window_init(&w, 800, 600)) return 1;

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

		glClearColor(0.0f, 0.1f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBegin(GL_TRIANGLES);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex2f(-0.5f, -0.5f);

			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex2f(0.5f, -0.5f);

			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex2f(0.0f, 0.5f);
		glEnd();

		window_after_draw(&w);

		usleep(16000);
	}

	window_free(&w);

	return 0;
}
