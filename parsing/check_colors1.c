/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 10:40:14 by rmouafik          #+#    #+#             */
/*   Updated: 2025/12/20 10:40:15 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	store_color_floor(t_game *game, char *line)
{
	char	**split_color;

	split_color = NULL;
	game->flag_f++;
	split_color = ft_split(ft_strchr1(line, ' '), ',');
	if (count_commas(line) != 2)
	{
		free_split(split_color);
		write(2, "Erreur\n", 8);
		return (0);
	}
	game->color_floor = split_color;
	return (1);
}

int	store_color_ceiling(t_game *game, char *line)
{
	char	**split_color;

	split_color = NULL;
	game->flag_c++;
	split_color = ft_split(ft_strchr1(line, ' '), ',');
	if (count_commas(line) != 2)
	{
		free_split(split_color);
		write(2, "Erreur\n", 8);
		return (0);
	}
	game->color_ceiling = split_color;
	return (1);
}

int	store_path_color(t_game *game)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	while (game->map[i])
	{
		line = skip_spaces(game->map[i]);
		if (ft_strncmp(line, "F ", 2) == 0)
		{
			if (!store_color_floor(game, line))
				return (0);
		}
		else if (ft_strncmp(line, "C ", 2) == 0)
		{
			if (!store_color_ceiling(game, line))
				return (0);
		}
		i++;
	}
	return (1);
}
