#include "../includes/cub3d.h"

int	find_start_of_map(t_game *game)
{
	int		i;
	char	*line;

	i = 0;
	while (game->map[i])
	{
		line = skip_spaces(game->map[i]);
		if (*line == '\0')
		{
			i++;
			continue ;
		}
		if (check_element_valid_in_map(line))
		{
			i++;
			continue ;
		}
		if (check_start_map(line))
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

int	element_valid(char **file)
{
	int	i;
	int	j;

	i = 0;
	while (file[i])
	{
		j = 0;
		while (file[i][j])
		{
			if (file[i][j] != '0' && file[i][j] != '\n' && file[i][j] != '1'
				&& file[i][j] != ' ' && file[i][j] != 'N' && file[i][j] != 'S'
				&& file[i][j] != 'E' && file[i][j] != 'W')
			{
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_first_line(char **map)
{
	int	i;

	i = 0;
	while (map[0][i])
	{
		if (map[0][i] == '0' || map[0][i] == 'N' || map[0][i] == 'S'
			|| map[0][i] == 'W' || map[0][i] == 'E')
			return (0);
		i++;
	}
	return (1);
}

int	check_last_line(char **map)
{
	int	last_line;
	int	i;

	last_line = count_line(map, 0);
	last_line = last_line - 1;
	i = 0;
	while (map[last_line][i])
	{
		if (map[last_line][i] == '0' || map[last_line][i] == 'N'
			|| map[last_line][i] == 'S' || map[last_line][i] == 'W'
			|| map[last_line][i] == 'E')
			return (0);
		i++;
	}
	return (1);
}

int	valid_walls(char **map)
{
	if (check_first_line(map) == 0)
		return (0);
	else if (check_last_line(map) == 0)
		return (0);
	return (1);
}