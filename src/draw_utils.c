#include "../includes/cub3d.h"

void draw_square(t_var *var, int size, int color, t_cube *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			mlx_put_pixel(game->img, var->minimap_x + j, 
				var->minimap_y + i, color);
			j++;
		}
		i++;
	}
}

double ft_distance(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
