#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

#include "textbuf.h"
#include "dstr.h"

int main()
{
	int err = 1;

	struct winsize w;
	int width, height;
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
		width = w.ws_col;
		height = w.ws_row;
	} else {
		fprintf(stderr, "main: failed to get terminal dimensions, defaulting to 80x25\n");
	}

	struct textbuf buf1;
	if (textbuf_init(&buf1, width, height)) goto out;

	struct textbuf buf2;
	if (textbuf_init(&buf2, width, height)) goto out_free_buf1;

	struct dstr text;
	if (dstr_init(&text)) goto out_free_buf2;

	for (int y=0; y<buf1.height; y++) {
		for (int x=0; x<buf1.width; x++) {
			buf1.buf[x + y * buf1.width] = 'a';
			buf2.buf[x + y * buf1.width] = 0;
		}
	}

	while (1) {
		int x = random() % buf1.width;
		int y = random() % buf1.height;
		int v = (random() % 95) + 32;
		buf1.buf[x + y * buf1.width] = v;
		if (textbuf_render_changes(&buf1, &buf2, &text)) goto out_free_text;
		//if (textbuf_render(&buf1, &text)) goto out_free_text;

		printf("%s", text.buf);
		fflush(stdout);

		memcpy(buf2.buf, buf1.buf, buf1.width * buf1.height * 2);

		//sleep(1);
	}
	
	
	err = 0;
out_free_text:
	dstr_free(&text);
out_free_buf2:
	textbuf_free(&buf2);
out_free_buf1:
	textbuf_free(&buf1);
out:
	return err;
}
