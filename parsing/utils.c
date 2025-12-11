#include "../includes/cub3d.h"

int	check_start_map(char *line)
{
	int	j;

	j = 0;
	while (line[j])
	{
		if (line[j] == ' ' || line[j] == '0' || line[j] == '1' || line[j] == 'S'
			|| line[j] == 'N' || line[j] == 'W' || line[j] == 'E'
			|| line[j] == '\n')
			return (1);
		j++;
	}
	return (0);
}

char	*skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (str + i);
}

void	free_split(char **file)
{
	int	i;

	i = 0;
	while (file[i])
	{
		free(file[i]);
		i++;
	}
	free(file);
}

char	*trim_spaces(char *str)
{
	int	start;
	int	end;
	int	i;

	start = 0;
	end = ft_strlen(str) - 1;
	while (str[start] && ft_isspace(str[start]))
		start++;
	while (end >= start && ft_isspace(str[end]))
		end--;
	i = 0;
	while (start <= end)
	{
		str[i] = str[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}

int	empty_line(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (ft_isspace(map[i][j]))
			j++;
		if (map[i][j] == '\0')
			return (0);
		i++;
	}
	return (1);
}