// texture.c

#define STBI_NO_SIMD
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <stdio.h>

#include "resources.h"

GLuint load_texture(const char *path)
{
	int w, h, n;
	unsigned char *data = stbi_load(path, &w, &h, &n, 4);
	if (!data) {
		fprintf(stderr, "load_texture: stbi_load failed for '%s'\n", path);
		return 0;
	}

	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);
	return tex;
}

int resources_init(struct resources *resources)
{
	resources->terrain = load_texture("resources/terrain.png");
	if (!resources->terrain) return 1;

	return 0;
}

void resources_free(struct resources *resources)
{
	glDeleteTextures(1, &resources->terrain);
}
