// textbuf.c

#include <stdio.h>
#include <stdlib.h>

#include "textbuf.h"

int textbuf_init(struct textbuf *buf, int width, int height)
{
	buf->buf = malloc(width * height * 2);
	if (!buf->buf) {
		fprintf(stderr, "textbuf_init: malloc failed\n");
		return 1;
	}
	buf->width = width;
	buf->height = height;
	return 0;
}

void textbuf_free(struct textbuf *buf)
{
	free(buf->buf);	
	buf->buf = NULL;
}

void textbuf_copy(struct textbuf *buf, struct textbuf *src, int x, int y)
{
	for (int sy=0; sy<src->height; sy++) {
		for (int sx=0; sx<src->width; sx++) {
			int dx = x + sx;
			int dy = y + sy;
			if (dx >= 0 && dx < buf->width && dy >= 0 && dy < buf->height) {
				buf->buf[dx + dy * buf->width] = src->buf[sx + sy * src->width];
			}
		}
	}
}

int textbuf_render(struct textbuf *buf, struct dstr *dst)
{
	dst->len = 0;
	if (dstr_addstr(dst, "\x1b[H")) return 1;
	for (int y=0; y<buf->height; y++) {
		for (int x=0; x<buf->width; x++) {
			if (dstr_addchar(dst, buf->buf[x + y * buf->width] & 0xFF)) return 1;
		}
		if (dstr_addstr(dst, "\x1b[E")) return 1;
	}
	char tmp[32];
	snprintf(tmp, 32, "\x1b[%d;1H\x1b[0m", buf->height);
	if (dstr_addstr(dst, tmp)) return 1;
	return 0;
}

int textbuf_render_changes(struct textbuf *buf, struct textbuf *old, struct dstr *dst)
{
	dst->len = 0;
	if (dstr_addstr(dst, "\x1b[H")) return 1;

	int last_was_drawn;
	int i=0;
	for (int y=0; y<buf->height; y++) {
		last_was_drawn = 0;
		for (int x=0; x<buf->width; x++) {
			uint16_t newc = buf->buf[i];
			uint16_t oldc = old->buf[i];
			
			if (oldc != newc) {
				if (!last_was_drawn) {
					char tmp[32];
					snprintf(tmp, 32, "\x1b[%d;%dH", y + 1, x + 1);
					if (dstr_addstr(dst, tmp)) return 1;
				}
				if (dstr_addchar(dst, newc & 0xFF)) return 1;
				last_was_drawn = 1;
			} else {
				last_was_drawn = 0;
			}
			i++;
		}
	}
	char tmp[32];
	snprintf(tmp, 32, "\x1b[%d;1H\x1b[0m", buf->height);
	if (dstr_addstr(dst, tmp)) return 1;

	return 0;
}
