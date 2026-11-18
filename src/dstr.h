// dstr.h

#ifndef CALPHA_DSTR_H
#define CALPHA_DSTR_H

#include <stddef.h>

struct dstr {
	char *buf;
	size_t len; // array length
	size_t sz; // byte size of buffer
};

// 0 on success
int dstr_init(struct dstr *dstr, size_t initsz);
void dstr_free(struct dstr *dstr);

int dstr_addchar(struct dstr *dstr, char c);
int dstr_addstr(struct dstr *dstr, const char *str);

#endif
