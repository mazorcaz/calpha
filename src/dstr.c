// dstr.c

#include <stdio.h>
#include <stdlib.h>

#include "dstr.h"

int dstr_init(struct dstr *dstr)
{
	dstr->len = 0;
	dstr->sz = 16;
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
	if (dstr->len >= dstr->sz) {
		do {
			dstr->sz <<= 1;
		} while (dstr->len >= dstr->sz);
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
		//printf("added char 0x%x ('%c')\n", c, c);
	}
	return 0;
}
