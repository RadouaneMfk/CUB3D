/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 13:09:38 by haboucha          #+#    #+#             */
/*   Updated: 2025/12/22 12:44:41 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_extension(char *file, char *ext)
{
	int	position;

	position = ft_strlen(file) - ft_strlen(ext);
	if (ft_strlen(file) < ft_strlen(ext))
		return (0);
	if (ft_strcmp(file + position, ext) != 0)
		return (0);
	return (1);
}

int	check_types(char *file)
{
	int	i;

	i = 0;
	while (ft_isspace(file[i]))
		i++;
	if (file[i] == '\0')
		return (0);
	while (file[i])
	{
		if (!ft_isdigit(file[i]))
			return (0);
		i++;
	}
	return (1);
}

int	color_floor(t_game *game)
{
	int	i;

	i = 0;
	while (game->color_floor[i])
	{
		game->color_floor[i] = trim_spaces(game->color_floor[i]);
		if (!check_types(game->color_floor[i]))
			return (0);
		i++;
	}
	game->f_r = ft_atoi(game->color_floor[0]);
	game->f_g = ft_atoi(game->color_floor[1]);
	game->f_b = ft_atoi(game->color_floor[2]);
	if ((game->f_r >= 0 && game->f_g >= 0 && game->f_b >= 0)
		&& (game->f_r <= 255 && game->f_g <= 255 && game->f_b <= 255))
		game->floor_color = (game->f_r << 24) | (game->f_g << 16) 
			| (game->f_b << 8) | 0xFF;
	else
		return (0);
	return (1);
}

int	color_ceiling(t_game *game)
{
	int	i;

	i = 0;
	while (game->color_ceiling[i])
	{
		game->color_ceiling[i] = trim_spaces(game->color_ceiling[i]);
		if (!check_types(game->color_ceiling[i]))
			return (0);
		i++;
	}
	game->c_r = ft_atoi(game->color_ceiling[0]);
	game->c_g = ft_atoi(game->color_ceiling[1]);
	game->c_b = ft_atoi(game->color_ceiling[2]);
	if ((game->c_r >= 0 && game->c_g >= 0 && game->c_b >= 0)
		&& (game->c_r <= 255 && game->c_g <= 255 && game->c_b <= 255))
		game->ceiling_color = (game->c_r << 24) | (game->c_g << 16) 
			| (game->c_b << 8) | 0xFF;
	else
		return (0);
	return (1);
}

int	parse_color_line(t_game *game)
{
	if (!store_path_color(game))
	{
		write(2, "fix color numbers\n", 19);
		return (0);
	}
	if (game->flag_f != 1 || game->flag_c != 1)
	{
		write(2, "Erreur\n", 8);
		write(2, "Dupplicate or color missing\n", 29);
		return (0);
	}
	if (!color_floor(game))
	{
		write(2, "Erreur\n", 8);
		write(2, "fix floor color\n", 17);
		return (0);
	}
	if (!color_ceiling(game))
	{
		write(2, "Erreur\n", 8);
		write(2, "fix ceiling color\n", 19);
		return (0);
	}
	return (1);
}
