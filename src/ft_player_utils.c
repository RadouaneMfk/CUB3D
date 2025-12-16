#include "../includes/cub3d.h"

void	init_player(char **map, t_cube *cube)
{
	int (i), (j);
	cube->player->mouse_lock = false;
	cube->player->prev_mouse_x = cube->win_w / 2;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' 
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (map[i][j] == 'N')
					cube->player->rotate_Angle = M_PI / 2;
				if (map[i][j] == 'S')
					cube->player->rotate_Angle = (3 * M_PI) / 2;
				if (map[i][j] == 'E')
					cube->player->rotate_Angle = 0;
				if (map[i][j] == 'W')
					cube->player->rotate_Angle = M_PI;
				cube->player->pos_x = j + 0.5;
				cube->player->pos_y = i + 0.5;
			}
		}
	}
}
