// window.c

#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <stdio.h>

#include "window.h"

int window_init(struct window *window)
{
	window->closed = 0;

	window->display = XOpenDisplay(NULL);
	if (!window->display) {
		fprintf(stderr, "window_create: XOpenDisplay failed\n");
		return 1;
	}

	int root = DefaultRootWindow(window->display);

	GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
	XVisualInfo *vi = glXChooseVisual(window->display, 0, att);

	Colormap cmap = XCreateColormap(window->display, root, vi->visual, AllocNone);
	XSetWindowAttributes swa;
	swa.colormap = cmap;
	swa.event_mask = ExposureMask | KeyPressMask;

	window->win = XCreateWindow(window->display, root, 0, 0, 800, 600, 0, vi->depth,
		InputOutput, vi->visual, CWColormap | CWEventMask, &swa);

	XMapWindow(window->display, window->win);
	XStoreName(window->display, window->win, "calpha");

	window->glc = glXCreateContext(window->display, vi, NULL, GL_TRUE);
	if (!window->glc) {
		fprintf(stderr, "window_create: glXCreateContext failed\n");
		return 1;
	}
	glXMakeCurrent(window->display, window->win, window->glc);

	return 0;
}

void window_free(struct window *window)
{
	glXMakeCurrent(window->display, None, NULL);
	glXDestroyContext(window->display, window->glc);
	XDestroyWindow(window->display, window->win);
	XCloseDisplay(window->display);
}

void window_close(struct window *window)
{
	window->closed = 1;
}

void window_before_draw(struct window *window)
{
	glXMakeCurrent(window->display, window->win, window->glc);
}

void window_after_draw(struct window *window)
{
	glXSwapBuffers(window->display, window->win);
}

void window_handle_events(struct window *window)
{
	XEvent xevent;
	while (XPending(window->display) > 0) {
		XNextEvent(window->display, &xevent);
		if (xevent.type == KeyPress) {
			window_close(window);
			return;
		}
	}
}

