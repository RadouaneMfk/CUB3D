/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 10:39:48 by rmouafik          #+#    #+#             */
/*   Updated: 2025/12/20 10:39:49 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_resize(int width, int height, void *param)
{
	t_cube	*game;

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

void	parsing_checks(t_cube game, char **str)
{
	if (check_extension(str[1], ".cub") == 0)
	{
		write(2, "extension not correct!\n", 24);
		exit(1);
	}
	initisalitaion(game.cube);
	game.cube->map = read_map(game.cube, str[1]);
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
		write(2, "Error\n", 7);
		write(2, "element not valid in the map\n", 30);
		exit(1);
	}
}

void	parsing_checks2(t_cube game, t_game *cube)
{
	if (!check_palyer(cube->new_map))
	{
		clean_up(game.cube);
		write(2, "Error\n", 7);
		write(2, "player not found or is duplicated!!\n", 37);
		exit(1);
	}
	if (!valid_walls(cube->new_map))
	{
		clean_up(game.cube);
		write(2, "Error\n", 7);
		write(2, "check teh validation of map!!\n", 31);
		exit(1);
	}
	if (!check_first_char(cube->new_map))
	{
		clean_up(game.cube);
		write(2, "Error\n", 7);
		write(2, "fix the first char\n", 20);
		exit(1);
	}
}
