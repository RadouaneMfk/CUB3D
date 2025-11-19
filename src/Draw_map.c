#include "../includes/cub3d.h"

void draw_map(char **map, t_cube *game)
{
	int map_height;
	int map_width;
	int i = 0;
	while (map[i])
		i++;
	map_height = i;
	if (map[0])
		map_width = ft_strlen(map[0]);
	int visible = 5;
	int player_x = (int)game->player->pos_x;
	int player_y = (int)game->player->pos_y;
	int start_x = player_x - visible;
	int start_y = player_y - visible;
	int end_x = player_x + visible;
	int end_y = player_y + visible;
    int x;
    int y;

	y = start_y;
    while (y <= end_y)
    {
		x = start_x;
		while (x <= end_x)
		{
			if (y < 0 || y >= map_height || x < 0 || x >= map_width)
			{
				x++;
				continue;
			}
			int minimap_x = (x - start_x) * MINIMAP_TILE_SIZE;
			int minimap_y = (y - start_y) * MINIMAP_TILE_SIZE;
			if (map[y][x] == '1')
				draw_square(minimap_x, minimap_y, MINIMAP_TILE_SIZE, 0x6468699B, game);
			// else
			// 	draw_square(minimap_x, minimap_y, MINIMAP_TILE_SIZE, 0xFFFFFFFF, game);
			x++;
		}
		y++;
	}
	draw_square(5 * MINIMAP_TILE_SIZE, 5 * MINIMAP_TILE_SIZE,
	0.25 * MINIMAP_TILE_SIZE, 0xd3d3d3FF, game);
}

void draw_black_cover(char **map, t_cube *game)
{
    int i;
    int j;
    int screen_x;
    int screen_y;

	i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            screen_x = j * (TILE_SIZE + 1);
            screen_y = i * (TILE_SIZE + 1);
            draw_square(MINIMAP_SCALE * screen_x, MINIMAP_SCALE * screen_y, MINIMAP_SCALE * (TILE_SIZE + 1), 0x000000FF, game);
            j++;
        }
        i++;
    }
}
