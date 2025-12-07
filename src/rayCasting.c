#include "../includes/cub3d.h"

void	ft_cast_ray(int rayId, double angle, t_cube *game)
{
	t_var	v;

	if (rayId < 0 || rayId >= WIDTH)
		return ;
	init_vars(&v, game);
	find_horizontal_hit(&v, angle, game);
	find_vertical_hit(&v, angle, game);
	select_hit(&v);
	compute_projection(&v, rayId, game, angle);
}

void castRays(t_cube *game)
{
	// int start_x = game->player->pos_x * (TILE_SIZE + 1);
	// int start_y = game->player->pos_y * (TILE_SIZE + 1);
	int num_rays = WIDTH;
	double ray_increment = FOV / num_rays;
	double ray_angle = game->player->rotate_Angle - (FOV / 2);

	int rayId = 0;
	while (rayId < num_rays)
	{
		if (ray_angle < 0)
			ray_angle += 2 * M_PI;
		if (ray_angle > 2 * M_PI)
			ray_angle -= 2 * M_PI;
		ft_cast_ray(rayId, ray_angle, game);
		ray_angle += ray_increment;
		rayId++;
	}
}
// void debug_textures(t_game *game)
// {
//     if (!game->textures.tex_no || !game->textures.tex_no->pixels)
//         printf("NO texture not loaded!\n");
//     else
//         printf("NO texture loaded, first pixel RGBA: %d %d %d %d\n",
//             game->textures.tex_no->pixels[0],
//             game->textures.tex_no->pixels[1],
//             game->textures.tex_no->pixels[2],
//             game->textures.tex_no->pixels[3]);

//     if (!game->textures.tex_so || !game->textures.tex_so->pixels)
//         printf("SO texture not loaded!\n");
//     if (!game->textures.tex_we || !game->textures.tex_we->pixels)
//         printf("WE texture not loaded!\n");
//     if (!game->textures.tex_ea || !game->textures.tex_ea->pixels)
//         printf("EA texture not loaded!\n");
// }

void clean_up(t_game *game)
{
    if(game->path_no)
        free(game->path_no);
    if(game->path_so)
        free(game->path_so);
    if(game->path_ea)
        free(game->path_ea);
    if(game->path_we)
        free(game->path_we);
    if(game->color_ceiling)
        free_split(game->color_ceiling);
    if(game->color_floor)
        free_split(game->color_floor);
    if(game)
        free(game);
}

int main(int ac, char *av[])
{
    t_cube game;
	t_game *cube;

	if(ac != 2)
        return 1;
    cube = NULL;
    cube = malloc(sizeof(t_game));
    if(!cube)
        return 1;
    char **new_map = NULL;
    // check extenstion d'argv
    if (check_extension(av[1],".cub") == 0)
    {
        write(2,"extension is not correcte!!\n",28);
        exit(1);
    }
    // initialition struct cube;
    initisalitaion(cube);
    // store cube.map
    cube->map = read_map(cube,av[1]);
    // parser textures
    if(!parse_texture_line(cube))
    {
        clean_up(cube);
        exit(1);
    }
    // parser colors RGB
    if(!parse_color_line(cube))
    {
        clean_up(cube);
        exit(1);
    }
    // check element not valid in map
    if(check_element(cube) == 0)
    {
        clean_up(cube);
        write(2,"Erreur\n",8);
        write(2,"element no vlaid in map\n",25);
        exit(1);
    }
    // find map start 
    int start = find_start_of_map(cube);
    int count_new_map = count_line(cube->map,start);
    new_map = malloc(sizeof(char *) * (count_new_map + 1));
    int begin = 0;
    while(cube->map[start])
    {
        new_map[begin] = ft_strdup1(cube->map[start]);
        start++;
        begin++;
    }
    new_map[begin] = NULL;
    free_split(cube->map);
    cube->map = new_map;
    if(!element_valid(cube->map))
    {
        clean_up(cube);
        write(2,"Erreur\n",8);
        write(2,"element incorrecte in new map !!\n",34);
        exit(1);    
    }
    cube->player_dir = check_palyer(new_map);
    if(!check_palyer(new_map))
    {
        clean_up(cube);
        write(2,"Erreur\n",8);
        write(2, "player not found or is duplicate!!\n", 36);
        exit(1);
    }
    if(!valid_walls(new_map))
    {
        clean_up(cube);
        write(2,"Erreur\n",8);
        write(2,"check valadition map!!\n",24);
        exit(1);
    }
    if(!check_first_char(new_map))
    {
        clean_up(cube);
        write(2,"Erreur\n",8);
        write(2,"fixe first char\n",17);
        exit(1);
    }
    if(!check_last_char(new_map))
    {
        clean_up(cube);
        write(2,"Erreur\n",8);
        write(2,"fixe last char\n",16);
        exit(1);
    }
    if(!valid_map(cube))
    {
        clean_up(cube);
        write(2,"Erreur\n",8);
        write(2,"le map invalid!!\n",18);
        exit(1);
    }
    
	game.map = cube->map;
    game.mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true);
    init_textures(&game,cube);
	game.player = malloc(sizeof(t_player));
	if (!game.player)
		return 1;
    game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
    if(!game.img)
    {
        printf("Erreur : impossible de créer l'image MLX !\n");
        return 1 ;
    }
    mlx_image_to_window(game.mlx ,game.img, 0, 0);
	init_player(game.map, &game);
	draw_map(game.map, &game);
	mlx_loop_hook(game.mlx, update_player, &game);
    mlx_loop(game.mlx);
  
    free_split(new_map);
    clean_up(cube);
    // free_split(cube->color_ceiling);
    // free_split(cube->color_floor);
    // free(cube->path_ea);
    // free(cube->path_we);
    // free(cube->path_so);
    // free(cube->path_no);
    return 0;
}
