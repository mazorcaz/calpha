// dbuf.h

#ifndef CALPHA_DBUF_H
#define CALPHA_DBUF_H

#include <stdint.h>
#include <stddef.h>

struct dbuf {
	uint8_t *buf;
	size_t len; // array length
	size_t sz; // byte size of buffer
};

int dbuf_init(struct dbuf *buf, size_t initsz);
void dbuf_free(struct dbuf *buf);

int dbuf_addbyte(struct dbuf *buf, uint8_t v);
int dbuf_addbuf(struct dbuf *buf, const uint8_t *src, size_t sz);

#endif
