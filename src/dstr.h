// dstr.h

#ifndef CALPHA_DSTR_H
#define CALPHA_DSTR_H

struct dstr {
	char *buf;
	int len;
	int sz;
};

// 0 on success
int dstr_init(struct dstr *dstr);
void dstr_free(struct dstr *dstr);

int dstr_addchar(struct dstr *dstr, char c);
int dstr_addstr(struct dstr *dstr, const char *str);

#endif
