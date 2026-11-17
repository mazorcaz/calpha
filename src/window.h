// window.h

#ifndef CALPHA_WINDOW_H
#define CALPHA_WINDOW_H

#include <X11/Xlib.h>
#include <GL/glx.h>

struct window {
	Display *display;
	Window win;
	GLXContext glc;

	int closed;

	int mousex;
	int mousey;
};

// 0 on success
int window_init(struct window *window);
void window_free(struct window *window);

void window_close(struct window *window);
void window_before_draw(struct window *window);
void window_after_draw(struct window *window);
void window_handle_events(struct window *window);

#endif
