// dstr.c

#include <stdio.h>
#include <stdlib.h>

#include "dstr.h"

int dstr_init(struct dstr *dstr, size_t initsz)
{
	dstr->len = 0;
	dstr->sz = initsz;
	if (dstr->sz < 16) dstr->sz = 16;
	dstr->buf = malloc(dstr->sz);
	if (!dstr->buf) {
		fprintf(stderr, "dstr_init: malloc failed\n");
		return 1;
	}
	dstr->buf[0] = '\0';
	return 0;
}

void dstr_free(struct dstr *dstr)
{
	free(dstr->buf);
	dstr->buf = NULL;
}

int dstr_addchar(struct dstr *dstr, char c)
{
	if (dstr->len + 1 >= dstr->sz) {
		do {
			dstr->sz <<= 1;
		} while (dstr->len + 1 >= dstr->sz);
		char *newbuf = realloc(dstr->buf, dstr->sz);
		if (!newbuf) {
			fprintf(stderr, "dstr_addchar: realloc failed\n");
			return 1;
		}
		dstr->buf = newbuf;
	}
	dstr->buf[dstr->len++] = c;
	dstr->buf[dstr->len] = '\0';
	return 0;
}

int dstr_addstr(struct dstr *dstr, const char *str)
{
	char c;
	while ((c = *str++) != '\0') {
		if (dstr_addchar(dstr, c)) return 1;
	}
	return 0;
}
