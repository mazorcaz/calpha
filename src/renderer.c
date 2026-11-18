// renderer.c

#include "window.h"
#include "renderer.h"

int renderer_init(struct renderer *renderer, struct window *window)
{
	renderer->window = window;

	renderer->buffer = malloc(256 * 128 * 64);
}
