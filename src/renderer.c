// renderer.c

#include <stdlib.h>
#include <stdio.h>

#include "window.h"
#include "renderer.h"

int renderer_init(struct renderer *renderer, struct window *window)
{
	renderer->window = window;

	renderer->buffer = malloc(256 * 128 * 64);
	if (!renderer->buffer) {
		fprintf(stdout, "renderer_init: malloc failed\n");
		return 1;
	}

	return 0;
}
