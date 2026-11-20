// renderstate.c

#include "texture.h"
#include "renderstate.h"

int renderstate_init(struct renderstate *rs)
{
	if (mesh_init(&rs->mesh)) goto out;

	rs->terrain = load_texture("resources/terrain.png");
	if (!rs->terrain) goto out_free_mesh;

	return 0;
	
out_free_terrain:
	glDeleteTextures(1, &rs->terrain);
out_free_mesh:
	mesh_free(&rs->mesh);
out:
	return 1;
}

void renderstate_free(struct renderstate *rs)
{
	mesh_free(&rs->mesh);
	glDeleteTextures(1, &rs->terrain);
}
