/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 13:09:57 by haboucha          #+#    #+#             */
/*   Updated: 2025/12/21 13:09:59 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_path_exist(void)
{
	int	fd_no;
	int	fd_so;
	int	fd_we;
	int	fd_ea;

	fd_no = open("./textures/north.png", O_RDONLY);
	if (fd_no == -1)
		return (0);
	fd_so = open("./textures/south.png", O_RDONLY);
	if (fd_so == -1)
		return (close(fd_no), 0);
	fd_we = open("./textures/west.png", O_RDONLY);
	if (fd_we == -1)
		return (close(fd_no), close(fd_so), 0);
	fd_ea = open("./textures/east.png", O_RDONLY);
	if (fd_ea == -1)
		return (close(fd_no), close(fd_so), close(fd_we), 0);
	return (close(fd_no), close(fd_so), close(fd_we), close(fd_ea), 1);
}

int	initialtion_path(t_game *game)
{
	game->path_no = texture_no_space(game->path_no);
	if (check_extension(game->path_no, ".png") == 0)
		return (0);
	game->path_so = texture_no_space(game->path_so);
	if (check_extension(game->path_so, ".png") == 0)
		return (0);
	game->path_we = texture_no_space(game->path_we);
	if (check_extension(game->path_we, ".png") == 0)
		return (0);
	game->path_ea = texture_no_space(game->path_ea);
	if (check_extension(game->path_ea, ".png") == 0)
		return (0);
	return (1);
}

int	check_all_path(t_game *game, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (!store_path_no(game, line))
			return (0);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (!store_path_so(game, line))
			return (0);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (!store_path_ea(game, line))
			return (0);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (!store_path_we(game, line))
			return (0);
	}
	return (1);
}

int	store_path(t_game *game)
{
	int		i;
	char	*line;

	i = 0;
	while (game->map[i])
	{
		line = skip_spaces(game->map[i]);
		if (!check_all_path(game, line))
			return (0);
		i++;
	}
	return (1);
}

int	parse_texture_line(t_game *game)
{
	if (!store_path(game))
		return (write(2, "Erreur\n", 8), write(2,
				"used some word not need in the path\n", 37), 0);
	if (!game->path_no || !game->path_so || !game->path_we || !game->path_ea)
		return (write(2, "Erreur\n", 8), write(2, "not store all the path\n",
				24), 0);
	if (game->flag_no != 1 || game->flag_ea != 1 || game->flag_we != 1
		|| game->flag_so != 1)
		return (write(2, "Erreur\n", 8), write(2, "duplicate path erreur!!!\n",
				26), 0);
	if (initialtion_path(game) == 0)
		return (write(2, "Erreur\n", 8), write(2, "path not exist\n", 16), 0);
	if (check_path_exist() == 0)
		return (write(2, "Erreur\n", 8), write(2, "path not found\n", 16), 0);
	return (1);
}
