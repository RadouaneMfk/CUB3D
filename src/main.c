#include "../includes/cub3d.h"

void	parsing_checks3(t_cube game, t_game *cube)
{
	if (!check_last_char(cube->new_map))
	{
		clean_up(game.cube);
		write(2, "Error\n", 7);
		write(2, "fix the last char\n", 19);
		exit(1);
	}
	if (!valid_map(game.cube))
	{
		clean_up(game.cube);
		write(2, "Error\n", 7);
		write(2, "map invalid!!\n", 15);
		exit(1);
	}
	if (!element_valid(game.cube->map))
	{
		clean_up(game.cube);
		write(2, "Error\n", 7);
		write(2, "element incorrect in new map !!\n", 33);
		exit(1);
	}
}

int	check_alloc_failed(t_cube *game, t_game *cube)
{
	if (!game->player)
	{
		free_all_textures(game);
		clean_up(cube);
		return (1);
	}
	game->img = mlx_new_image(game->mlx, game->win_w, game->win_h);
	if (!game->img)
	{
		free(game->player);
		free_all_textures(game);
		ft_putendl_fd("Error : mlx image creation failed!\n", 2);
		return (1);
	}
	return (0);
}

void	create_the_map(t_cube game, int start, int begin, t_game *cube)
{
	while (game.cube->map[start])
	{
		cube->new_map[begin] = ft_strdup1(game.cube->map[start]);
		start++;
		begin++;
	}
	cube->new_map[begin] = NULL;
	free_split(game.cube->map);
	game.cube->map = cube->new_map;
	game.cube->player_dir = check_palyer(cube->new_map);
}

int	ft_mlx_render(t_game *cube, t_cube game)
{
	game.mlx = mlx_init(game.win_w, game.win_h, "CUB3D", true);
	init_textures(&game, game.cube);
	game.player = malloc(sizeof(t_player));
	if (check_alloc_failed(&game, cube) == 1)
		return (1);
	mlx_image_to_window(game.mlx, game.img, 0, 0);
	mlx_resize_hook(game.mlx, ft_resize, &game);
	init_player(game.map, &game);
	if (game.win_h > 100 && game.win_w > 100)
		draw_map(game.map, &game);
	mlx_loop_hook(game.mlx, update_player, &game);
	mlx_loop(game.mlx);
	free_split(cube->new_map);
	clean_up(game.cube);
	free_all_textures(&game);
	free(game.player);
	return (0);
}

int	main(int ac, char *av[])
{
	t_cube	game;

	int (start), (count_new_map), (begin);
	if (ac != 2)
		return (1);
	game.win_w = WIDTH;
	game.win_h = HEIGHT;
	game.cube = NULL;
	game.cube = malloc(sizeof(t_game));
	if (!game.cube)
		return (1);
	game.cube->new_map = NULL;
	parsing_checks(game, av);
	start = find_start_of_map(game.cube);
	count_new_map = count_line(game.cube->map, start);
	game.cube->new_map = malloc(sizeof(char *) * (count_new_map + 1));
	begin = 0;
	create_the_map(game, start, begin, game.cube);
	parsing_checks2(game, game.cube);
	parsing_checks3(game, game.cube);
	game.map = game.cube->map;
	game.cube = game.cube;
	ft_mlx_render(game.cube, game);
	return (0);
}
