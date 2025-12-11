#include "../../includes/cub3d.h"

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	res;
	int					s;

	i = ((res = 0), 0);
	s = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		if (res > LONG_MAX && s == 1)
			return (-1);
		if (res > LONG_MAX && s == -1)
			return (0);
		i++;
	}
	return (res * s);
}
