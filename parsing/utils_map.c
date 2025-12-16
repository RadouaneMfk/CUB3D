#include "../includes/cub3d.h"

int	check_element_valid_in_map(char *line)
{
	if ((ft_strncmp(line, "NO ", 3) == 0) || (ft_strncmp(line, "SO ", 3) == 0)
		|| (ft_strncmp(line, "EA ", 3) == 0) || (ft_strncmp(line, "WE ",
				3) == 0) || (ft_strncmp(line, "F ", 2) == 0)
		|| (ft_strncmp(line, "C ", 2) == 0))
		return (1);
	return (0);
}

int	check_element_start_map(char *line)
{
	if (line[0] == '0' || line[0] == '1' || line[0] == 'N' || line[0] == 'S'
		|| line[0] == 'E' || line[0] == 'W')
		return (1);
	return (0);
}

int	check_element(t_game *game)
{
	int		i;
	int		count;
	char	*line;

	i = 0;
	count = 0;
	while (game->map[i])
	{
		line = skip_spaces(game->map[i]);
		if (*line == '\0')
		{
			i++;
			continue ;
		}
		if (check_element_valid_in_map(line))
			count++;
		else if (check_element_start_map(line))
			break ;
		else
			return (0);
		i++;
	}
	if (count == 6)
		return (1);
	return (0);
}

void	aide_player(char **map, int *count, char *player)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'W' || map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E')
			{
				(*count)++;
				(*player) = map[i][j];
			}
			j++;
		}
		i++;
	}
	return ;
}

char	check_palyer(char **map)
{
	int		count_player;
	char	player_dir;

	player_dir = 0;
	count_player = 0;
	aide_player(map, &count_player, &player_dir);
	if (count_player > 1)
		return (0);
	else if (count_player == 0)
		return (0);
	return (player_dir);
}
