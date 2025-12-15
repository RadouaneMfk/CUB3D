#include "../includes/cub3d.h"

void	ft_cast_ray(int rayId, double angle, t_cube *game)
{
	t_var	v;

	if (rayId < 0 || rayId >= game->win_w)
		return ;
	init_vars(&v, game);
	find_horizontal_hit(&v, angle, game);
	find_vertical_hit(&v, angle, game);
	select_hit(&v);
	compute_projection(&v, rayId, game, angle);
}

void    castRays(t_cube *game)
{
	int		num_rays;
	double	ray_increment;
	double	ray_angle;
	int		rayId;

	num_rays = game->win_w;
	ray_increment = FOV / num_rays;
	ray_angle = game->player->rotate_Angle - (FOV / 2);
	rayId = 0;
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

void ft_resize(int width, int height, void *param)
{
	t_cube *game;

	game = (t_cube *)param;
	if (height < MIN_H)
		height = MIN_H;
	if (width < MIN_W)
		width = MIN_W;
	game->win_w = width;
	game->win_h = height;
	mlx_delete_image(game->mlx, game->img);
	game->img = mlx_new_image(game->mlx, game->win_w, game->win_h);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
}

void clean_up(t_game *game)
{
	if (game->path_no)
		free(game->path_no);
    if (game->path_so)
		free(game->path_so);
	if (game->path_ea)
		free(game->path_ea);
	if (game->path_we)
		free(game->path_we);
	if (game->color_ceiling)
		free_split(game->color_ceiling);
	if (game->color_floor)
		free_split(game->color_floor);
	if (game)
		free(game);
}

void ff()
{
	system("leaks -q cub3D");
}

int main(int ac, char *av[])
{
    t_cube	game;
	t_game	*cube;
	char	**new_map;
	int		start;
	int		count_new_map;
	int		begin;

	game.win_w = WIDTH;
	game.win_h = HEIGHT;
	atexit(ff);
	if (ac != 2)
		return (1);
	game.cube = NULL;
	game.cube = malloc(sizeof(t_game));
	if (!game.cube)
		return (1);
	new_map = NULL;
	if (check_extension(av[1], ".cub") == 0)
	{
		write(2, "extension is not correct!\n", 28);
		exit(1);
	}
	initisalitaion(game.cube);
	game.cube->map = read_map(game.cube, av[1]);
	if (!parse_texture_line(game.cube))
	{
		clean_up(game.cube);
		exit(1);
	}
	if (!parse_color_line(game.cube))
	{
		clean_up(game.cube);
		exit(1);
	}
	if (check_element(game.cube) == 0)
	{
		clean_up(game.cube);
		write(2, "Error\n", 8);
		write(2, "element not valid in the map\n", 25);
		exit(1);
	}
	start = find_start_of_map(game.cube);
	count_new_map = count_line(game.cube->map, start);
	new_map = malloc(sizeof(char *) * (count_new_map + 1));
	begin = 0;
	while (game.cube->map[start])
	{
		new_map[begin] = ft_strdup1(game.cube->map[start]);
		start++;
		begin++;
	}
	new_map[begin] = NULL;
	free_split(game.cube->map);
	game.cube->map = new_map;
	if (!element_valid(game.cube->map))
	{
		clean_up(game.cube);
		write(2, "Erreur\n", 8);
		write(2, "element incorrect in new map !!\n", 34);
		exit(1);    
	}
	game.cube->player_dir = check_palyer(new_map);
	if (!check_palyer(new_map))
	{
		clean_up(game.cube);
		write(2, "Erreur\n", 8);
		write(2, "player not found or is duplicated!!\n", 36);
		exit(1);
	}
	if (!valid_walls(new_map))
	{
		clean_up(game.cube);
		write(2, "Erreur\n", 8);
		write(2, "check validation map!!\n", 24);
		exit(1);
	}
	if (!check_first_char(new_map))
	{
		clean_up(game.cube);
		write(2, "Erreur\n", 8);
		write(2, "fix first char\n", 17);
		exit(1);
	}
	if (!check_last_char(new_map))
	{
		clean_up(game.cube);
		write(2, "Erreur\n", 8);
		write(2, "fix last char\n", 16);
		exit(1);
	}
	if (!valid_map(game.cube))
	{
		clean_up(game.cube);
		write(2, "Error\n", 8);
		write(2, "map invalid!!\n", 18);
		exit(1);
	}
	game.map = game.cube->map;
	game.cube = game.cube;
	game.mlx = mlx_init(game.win_w, game.win_h, "CUB3D", true);
	init_textures(&game, game.cube);
	game.player = malloc(sizeof(t_player));
	if (!game.player)
	{
		free_all_textures(&game);
		clean_up(cube);
		return (1);
	}
	game.img = mlx_new_image(game.mlx, game.win_w, game.win_h);
	if (!game.img)
	{
		free(game.player);
		free_all_textures(&game);
		ft_putendl_fd("Error : mlx image creation failed!\n", 2);
		return (1);
	}
	mlx_image_to_window(game.mlx, game.img, 0, 0);
	mlx_resize_hook(game.mlx, ft_resize, &game);
	init_player(game.map, &game);
	if (game.win_h > 100 && game.win_w > 100)
		draw_map(game.map, &game);
	mlx_loop_hook(game.mlx, update_player, &game);
	mlx_loop(game.mlx);
	free_split(new_map);
	clean_up(game.cube);
	free_all_textures(&game);
	free(game.player);
	return (0);
}
