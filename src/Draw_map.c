#include "../includes/cub3d.h"

void	init_draw_map(t_var *var, char **map, t_cube *game)
{
	var->i = 0;
	while (map[var->i])
		var->i++;
	var->map_height = var->i;
	if (map[0])
		var->map_width = ft_strlen(map[0]);
	var->visible = 5;
	var->player_x = (int)game->player->pos_x;
	var->player_y = (int)game->player->pos_y;
	var->start_x = var->player_x - var->visible;
	var->start_y = var->player_y - var->visible;
	var->end_x = var->player_x + var->visible;
	var->end_y = var->player_y + var->visible;
	var->y = var->start_y;
}

void	draw_map(char **map, t_cube *game)
{
	t_var	var;

	init_draw_map(&var, map, game);
	while (var.y <= var.end_y)
	{
		var.x = var.start_x;
		while (var.x <= var.end_x)
		{
			if (var.y < 0 || var.y >= var.map_height 
				|| var.x < 0 || var.x >= var.map_width)
			{
				var.x++;
				continue ;
			}
			var.minimap_x = (var.x - var.start_x) * MINIMAP_TILE_SIZE;
			var.minimap_y = (var.y - var.start_y) * MINIMAP_TILE_SIZE;
			if (map[var.y][var.x] == '1')
				draw_square(&var, MINIMAP_TILE_SIZE, 0x6468699B, game);
			var.x++;
		}
		var.y++;
	}
	var.minimap_x = 5 * MINIMAP_TILE_SIZE;
	var.minimap_y = 5 * MINIMAP_TILE_SIZE;
	draw_square(&var, 0.30 * MINIMAP_TILE_SIZE, 0xd3d3d3FF, game);
}

