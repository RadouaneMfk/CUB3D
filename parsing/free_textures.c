#include "../includes/cub3d.h"

void	free_texture(t_cube *cube, t_texture *tex)
{
	if (tex->img)
	{
		mlx_delete_image(cube->mlx, tex->img);
		tex->img = NULL;
	}
}

void	free_all_textures(t_cube *cube)
{
	free_texture(cube, &cube->textures.no);
	free_texture(cube, &cube->textures.so);
	free_texture(cube, &cube->textures.we);
	free_texture(cube, &cube->textures.ea);
}
