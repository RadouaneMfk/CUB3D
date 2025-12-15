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
	game->F_r = ft_atoi(game->color_floor[0]);
	game->F_g = ft_atoi(game->color_floor[1]);
	game->F_b = ft_atoi(game->color_floor[2]);
	if ((game->F_r >= 0 && game->F_g >= 0 && game->F_b >= 0)
		&& (game->F_r <= 255 && game->F_g <= 255 && game->F_b <= 255))
		game->floor_color = (game->F_r << 16) + (game->F_g << 8) + game->F_b;
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
	game->C_r = ft_atoi(game->color_ceiling[0]);
	game->C_g = ft_atoi(game->color_ceiling[1]);
	game->C_b = ft_atoi(game->color_ceiling[2]);
	if ((game->C_r >= 0 && game->C_g >= 0 && game->C_b >= 0)
		&& (game->C_r <= 255 && game->C_g <= 255 && game->C_b <= 255))
		game->ceiling_color = (game->C_r << 16) | (game->C_g << 8) | game->C_b;
	else
		return (0);
	return (1);
}

int	parse_color_line(t_game *game)
{
	if (!store_path_color(game))
	{
		write(2, "fixe numbers\n", 14);
		return (0);
	}
	if (game->flag_F != 1 || game->flag_C != 1)
	{
		write(2, "Erreur\n", 8);
		write(2, "Dupplicate colors\n", 19);
		return (0);
	}
	if (!color_floor(game))
	{
		write(2, "Erreur\n", 8);
		write(2, "fixe color floor\n", 20);
		return (0);
	}
	if (!color_ceiling(game))
	{
		write(2, "Erreur\n", 8);
		write(2, "fixe color ceiling\n", 20);
		return (0);
	}
	return (1);
}
