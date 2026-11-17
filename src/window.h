// window.h

#ifndef CALPHA_WINDOW_H
#define CALPHA_WINDOW_H

#include <X11/Xlib.h>
#include <GL/glx.h>
#include <stdint.h>

enum event_type {
	EVENT_NONE = 0,
	EVENT_KEY_DOWN,
	EVENT_KEY_UP,
	EVENT_MOUSE_MOVE,
	EVENT_MOUSE_DOWN,
	EVENT_MOUSE_UP
};

struct event {
	enum event_type type;
	int x, y, dx, dy; // mouse coords & delta for movement
	int button; // 0 = left, 1 = middle, 2 = right
	int keycode;
	int keysym; // key_code translated to char
};

struct window {
	Display *display;
	Window win;
	GLXContext glc;

	int closed;

	int mousex;
	int mousey;

	uint8_t keys[256];
};

// 0 on success
int window_init(struct window *window);
void window_free(struct window *window);

void window_close(struct window *window);
void window_before_draw(struct window *window);
void window_after_draw(struct window *window);
int window_next_event(struct window *window, struct event *event); // 0 when no events

#endif
