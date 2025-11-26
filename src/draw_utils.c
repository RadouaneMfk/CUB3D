#include "../includes/cub3d.h"

// void draw_line(t_cube *game)
// {
//     int center_x = game->player->pos_x * (TILE_SIZE + 1);
//     int center_y = game->player->pos_y * (TILE_SIZE + 1);
//     int end_x = center_x + cos(game->player->rotate_Angle) * 40;
//     int end_y = center_y + sin(game->player->rotate_Angle) * 40;

//     for (int i = 0; i < 40; i++)
//     {
//         int x = center_x + (end_x - center_x) * i / 40;
//         int y = center_y + (end_y - center_y) * i / 40;
//         mlx_put_pixel(game->img, MINIMAP_SCALE * x, MINIMAP_SCALE * y, 0xFF0000FF);
//     }
// }

void draw_square(double x, double y, int size, int color, t_cube *game)
{
    int i = 0;
	int j = 0;

	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			mlx_put_pixel(game->img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

// void ft_draw_line(double x0, double y0, double x1, double y1, int color, t_cube *game)
// {
//     double dx = x1 - x0;
//     double dy = y1 - y0;
//     double distance = sqrt(dx * dx + dy * dy);
//     double step_x = dx / distance;
//     double step_y = dy / distance;

//     while (distance > 0)
//     {
//         mlx_put_pixel(game->img, (int)x0, (int)y0, color);
//         x0 += step_x;
//         y0 += step_y;
//         distance -= 1;
//     }
// }

double ft_distance(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
