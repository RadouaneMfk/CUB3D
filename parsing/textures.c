#include "../includes/cub3d.h"

int upload_textures(t_game *game)
{
    game->textures.tex_no = mlx_load_png(game->path_no);
    if(!game->textures.tex_no)
        return(write(2, "Failed to load texture NO\n", 26),0);
    game->textures.tex_so = mlx_load_png(game->path_so);
    if(!game->textures.tex_so)
        return(write(2, "Failed to load texture SO\n", 26),0);
    game->textures.tex_ea = mlx_load_png(game->path_ea);
    if(!game->textures.tex_ea)
        return(write(2, "Failed to load texture EA\n", 26),0);
    game->textures.tex_we = mlx_load_png(game->path_we);
    if(!game->textures.tex_we)
        return(write(2, "Failed to load texture WE\n", 26),0);
    return 1;
}

int convert_textures_to_img(t_game *game,t_cube *cube)
{
    game->textures.tex_no_img = mlx_texture_to_image(cube->mlx,game->textures.tex_no);
    if(!game->textures.tex_no_img)
        return(write(2,"Failed to convert NO\n",21),0);
    game->textures.tex_so_img = mlx_texture_to_image(cube->mlx,game->textures.tex_so);
    if(!game->textures.tex_so_img)
        return(write(2,"Failed to convert SO\n",21),0);
    game->textures.tex_we_img = mlx_texture_to_image(cube->mlx,game->textures.tex_we);
    if(!game->textures.tex_we_img)
        return(write(2,"Failed to convert WE\n",21),0);
    game->textures.tex_ea_img = mlx_texture_to_image(cube->mlx,game->textures.tex_ea);
    if(!game->textures.tex_ea_img)
        return(write(2,"Failed to convert EA\n",21),0);
    
    return 1;
}


// void free_png(t_game *game)
// {
//     mlx_delete_texture(game->textures.so.tex);
//     game->textures.so.tex =NULL;
//     mlx_delete_texture(game->textures.no.tex);
//     game->textures.no.tex =NULL;
//     mlx_delete_texture(game->textures.we.tex);
//     game->textures.we.tex =NULL;
//     mlx_delete_texture(game->textures.ea.tex);
//     game->textures.ea.tex =NULL;
// }