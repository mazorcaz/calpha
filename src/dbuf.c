// dbuf.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dbuf.h"

int dbuf_init(struct dbuf *buf, size_t initsz)
{
	buf->len = 0;
	buf->sz = initsz;
	if (buf->sz < 16) buf->sz = 16;
	buf->buf = malloc(buf->sz);
	if (!buf->buf) {
		fprintf(stderr, "dbuf_init: malloc failed\n");
		return 1;
	}
	return 0;
}

void dbuf_free(struct dbuf *buf)
{
	free(buf->buf);
	buf->buf = NULL;
}

int dbuf_addbyte(struct dbuf *buf, uint8_t v)
{
	if (buf->len >= buf->sz) {
		do {
			buf->sz <<= 1;
		} while (buf->len >= buf->sz);
		void *newbuf = realloc(buf->buf, buf->sz);
		if (!newbuf) {
			fprintf(stderr, "dbuf_addbyte: realloc failed\n");
			return 1;
		}
		buf->buf = newbuf;
	}
	buf->buf[buf->len++] = v;
	return 0;
}

int dbuf_addbuf(struct dbuf *buf, const uint8_t *src, size_t sz)
{
	if (buf->len + sz > buf->sz) {
		do {
			buf->sz <<= 1;
		} while (buf->len + sz > buf->sz);
		void *newbuf = realloc(buf->buf, buf->sz);
		if (!newbuf) {
			fprintf(stderr, "dbuf_addbuf: realloc failed\n");
			return 1;
		}
		buf->buf = newbuf;
	}
	memcpy(buf->buf + buf->len, src, sz);
	buf->len += sz;
	return 0;
}
