#include "../includes/cub3d.h"

void	assign_texture_path(t_cube *cube, t_game *g)
{
	cube->textures.no.path = g->path_no;
	cube->textures.so.path = g->path_so;
	cube->textures.we.path = g->path_we;
	cube->textures.ea.path = g->path_ea;
}

int	load_texture(t_cube *cube, t_texture *tex)
{
	if (!tex->path)
		return (write(2, "Erreur\n", 8), write(2, "Texture path missing\n", 22),
			0);
	tex->tex = mlx_load_png(tex->path);
	if (!tex->tex)
	{
		write(2, "Erreur\n", 8);
		write(2, "Failed to load texture\n", 24);
		return (0);
	}
	tex->width = tex->tex->width;
	tex->height = tex->tex->height;
	tex->img = mlx_texture_to_image(cube->mlx, tex->tex);
	if (!tex->img)
	{
		write(2, "Erreur\n", 8);
		write(2, "Failed to convert texture\n", 27);
		mlx_delete_texture(tex->tex);
		tex->tex = NULL;
		return (0);
	}
	mlx_delete_texture(tex->tex);
	tex->tex = NULL;
	return (1);
}

int	load_all_textures(t_cube *cube)
{
	if (!load_texture(cube, &cube->textures.no))
		return (0);
	if (!load_texture(cube, &cube->textures.so))
	{
		free_texture(cube, &cube->textures.no);
		return (0);
	}
	if (!load_texture(cube, &cube->textures.we))
	{
		free_texture(cube, &cube->textures.no);
		free_texture(cube, &cube->textures.so);
		return (0);
	}
	if (!load_texture(cube, &cube->textures.ea))
	{
		free_texture(cube, &cube->textures.no);
		free_texture(cube, &cube->textures.so);
		free_texture(cube, &cube->textures.we);
		return (0);
	}
	return (1);
}

int	init_textures(t_cube *cube, t_game *game)
{
	assign_texture_path(cube, game);
	if (!load_all_textures(cube))
		return (0);
	return (1);
}


