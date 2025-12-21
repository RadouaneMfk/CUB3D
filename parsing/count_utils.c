#include "../includes/cub3d.h"

void	initisalitaion(t_game *game)
{
	game->map = NULL;
	game->ceiling_color = 0;
	game->floor_color = 0;
	game->path_ea = NULL;
	game->path_no = NULL;
	game->path_we = NULL;
	game->path_so = NULL;
	game->flag_no = 0;
	game->flag_so = 0;
	game->flag_we = 0;
	game->flag_ea = 0;
	game->color_floor = NULL;
	game->color_ceiling = NULL;
	game->flag_c = 0;
	game->flag_f = 0;
}

int	number_line(char *line)
{
	int	i;
	int	fd;

	i = 0;
	fd = open(line, O_RDONLY);
	if (fd == -1)
		exit(1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (i);
}

int	count_line(char **map, int i)
{
	int	count;

	count = 0;
	while (map[i])
	{
		count++;
		i++;
	}
	return (count);
}

int	count_number(char **file)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (file[i])
	{
		count++;
		i++;
	}
	return (count);
}

int	count_commas(char *file)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (file[i])
	{
		if (file[i] == ',')
			count++;
		i++;
	}
	return (count);
}
