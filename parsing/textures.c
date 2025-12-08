#include "../includes/cub3d.h"

void assign_texture_path(t_cube *cube,t_game *g)
{
    cube->textures.no.path = g->path_no;
    cube->textures.so.path = g->path_so;
    cube->textures.we.path = g->path_we;
    cube->textures.ea.path = g->path_ea;
}

void load_texture(t_cube *cube, t_texture *tex)
{
    if(!tex->path)
    {
        printf("Texture path missing!\n");
        exit(1);
    }
    tex->tex = mlx_load_png(tex->path);
    if(!tex->tex)
    {
        printf("Failed to load texture: %s\n", tex->path);
        exit(1);
    }
    tex->width = tex->tex->width;
    tex->height = tex->tex->height;
    tex->img = mlx_texture_to_image(cube->mlx,tex->tex);
    if(!tex->img)
    {
        printf("Failed to convert texture: %s\n", tex->path);
        exit(1);
    }
    // mlx_image_to_window(cube->mlx,tex->img , -10000,-10000);
}
void load_all_textures(t_cube *cube)
{
    load_texture(cube,&cube->textures.no);
    load_texture(cube,&cube->textures.so);
    load_texture(cube,&cube->textures.we);
    load_texture(cube,&cube->textures.ea);
}

void init_textures(t_cube *cube,t_game *game)
{
    assign_texture_path(cube, game);
	load_all_textures(cube);
}
