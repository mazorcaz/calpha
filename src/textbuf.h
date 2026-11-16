// textbuf.h

#ifndef CALPHA_TEXTBUF_H
#define CALPHA_TEXTBUF_H

#include "dstr.h"

struct textbuf {
	uint16_t *buf;
	int width;
	int height;
};

// 0 on success
int textbuf_init(struct textbuf *buf, int width, int height);
void textbuf_free(struct textbuf *buf);

void textbuf_copy(struct textbuf *buf, struct textbuf *src, int x, int y);
int textbuf_render(struct textbuf *buf, struct dstr *dst);
int textbuf_render_changes(struct textbuf *buf, struct textbuf *old, struct dstr *dst);

#endif
