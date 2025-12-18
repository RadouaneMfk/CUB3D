#include "../includes/cub3d.h"

char	**read_map(t_game *game, char *av)
{
	int		count;
	int		fd;
	int		i;
	char	*line;

	count = number_line(av);
	fd = open(av, O_RDONLY);
	game->map = malloc(sizeof(char *) * (count + 1));
	if (!game->map)
		return (free(game), NULL);
	i = 0;
	line = get_next_line(fd);
	while ((line) != NULL)
	{
		game->map[i] = line;
		i++;
		line = get_next_line(fd);
	}
	game->map[i] = NULL;
	close(fd);
	return (game->map);
}

int	aide_map(t_game *game, int i, int j)
{
	int	row_len;
	int	rows;

	rows = count_number(game->map);
	while (game->map[i][j])
	{
		if (game->map[i][j] == '0' || game->map[i][j] == 'N'
			|| game->map[i][j] == 'S' || game->map[i][j] == 'E'
			|| game->map[i][j] == 'W')
		{
			row_len = ft_strlen(game->map[i]);
			if (j == 0 || game->map[i][j - 1] == ' ')
				return (0);
			if (j == row_len - 1 || game->map[i][j + 1] == ' ')
				return (0);
			if (i == 0 || j >= (int)ft_strlen(game->map[i - 1]) || 
				game->map[i - 1][j] == ' ')
				return (0);
			if (i == rows - 1 || j >= (int)ft_strlen(game->map[i + 1])
				|| game->map[i + 1][j] == ' ')
				return (0);
		}
		j++;
	}
	return (1);
}

int	valid_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	if (empty_line(game->map) == 0)
		return (0);
	while (game->map[i])
	{
		j = 0;
		if (!aide_map(game, i, j))
			return (0);
		i++;
	}
	return (1);
}

int	check_first_char(char **map)
{
	int	i;
	int	j;

	i = 1;
	while (map[i])
	{
		j = 0;
		while (isspace(map[i][j]))
			j++;
		if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S'
			|| map[i][j] == 'E' || map[i][j] == 'W')
			return (0);
		i++;
	}
	return (1);
}

int	check_last_char(char **map)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (map[i])
	{
		j = ft_strlen(map[i]) - 2;
		while (j > 0 && ft_isspace(map[i][j]))
			j--;
		if (j > 0 && (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W'))
			return (0);
		i++;
	}
	return (1);
}
