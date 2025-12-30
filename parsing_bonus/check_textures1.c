/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 13:10:04 by haboucha          #+#    #+#             */
/*   Updated: 2025/12/21 13:10:06 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*texture_no_space(char *path)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	while (ft_isspace(path[start]))
		start++;
	end = ft_strlen(path) - 1;
	while (end >= 0 && path[end])
	{
		if (ft_atoi(&path[end]))
			path[end] = '\0';
		end--;
	}
	return (path + start);
}

int	store_path_no(t_game *game, char *line)
{
	char	**split;

	split = NULL;
	game->flag_no++;
	line = trim_spaces(line);
	split = ft_split(line, ' ');
	if (count_line(split, 0) != 2)
	{
		free_split(split);
		return (0);
	}
	game->path_no = ft_strdup1(trim_spaces(split[1]));
	free_split(split);
	split = NULL;
	return (1);
}

int	store_path_so(t_game *game, char *line)
{
	char	**split;

	split = NULL;
	game->flag_so++;
	line = trim_spaces(line);
	split = ft_split(line, ' ');
	if (count_line(split, 0) != 2)
	{
		free_split(split);
		return (0);
	}
	game->path_so = ft_strdup1(trim_spaces(split[1]));
	free_split(split);
	split = NULL;
	return (1);
}

int	store_path_ea(t_game *game, char *line)
{
	char	**split;

	split = NULL;
	game->flag_ea++;
	line = trim_spaces(line);
	split = ft_split(line, ' ');
	if (count_line(split, 0) != 2)
	{
		free_split(split);
		return (0);
	}
	game->path_ea = ft_strdup1(trim_spaces(split[1]));
	free_split(split);
	split = NULL;
	return (1);
}

int	store_path_we(t_game *game, char *line)
{
	char	**split;

	split = NULL;
	game->flag_we++;
	line = trim_spaces(line);
	split = ft_split(line, ' ');
	if (count_line(split, 0) != 2)
	{
		free_split(split);
		return (0);
	}
	game->path_we = ft_strdup1(trim_spaces(split[1]));
	free_split(split);
	split = NULL;
	return (1);
}
