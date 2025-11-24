#include "../includes/cub3d.h"

void init_player(char **map, t_cube *cube)
{
	int i;
	int j;
	cube->player->mouse_lock = false;
	cube->player->prev_mouse_x = WIDTH / 2;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
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

void update_player(void *param)
{
    t_cube *game = (t_cube *)param;
    double next_posx = game->player->pos_x;
    double next_posy = game->player->pos_y;
    double move_speed = 0.05;
    double radius = 0.14;
	double walk = 0;
	int center_x = WIDTH / 2;
	int center_y = HEIGHT / 2;
	double delta;

	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT_CONTROL))
	{
		if (game->player->mouse_lock == false)
		{
			game->player->mouse_lock = true;
			mlx_set_mouse_pos(game->mlx, center_x, center_y);
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
			game->player->prev_mouse_x = center_x;
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT_SHIFT))
	{
		if (game->player->mouse_lock == true)
		{
			game->player->mouse_lock = false;
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_NORMAL);
		}
	}
	if (game->player->mouse_lock)
	{
		mlx_get_mouse_pos(game->mlx, &game->player->cursor_x, &game->player->cursor_y);
		mlx_set_mouse_pos(game->mlx, center_x, center_y);
		delta = game->player->cursor_x - game->player->prev_mouse_x;
		game->player->rotate_Angle += delta * 0.0015;
		game->player->prev_mouse_x = center_x;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
    if (mlx_is_key_down(game->mlx, MLX_KEY_W))
        walk = move_speed;
    if (mlx_is_key_down(game->mlx, MLX_KEY_S))
        walk = -move_speed;
	next_posx = game->player->pos_x + cos(game->player->rotate_Angle) * walk;
	next_posy = game->player->pos_y + sin(game->player->rotate_Angle) * walk;
    if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		next_posx += cos(game->player->rotate_Angle + M_PI_2) * move_speed;
		next_posy += sin(game->player->rotate_Angle + M_PI_2) * move_speed;
	}
    if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
        next_posx -= cos(game->player->rotate_Angle + M_PI_2) * move_speed;
        next_posy -= sin(game->player->rotate_Angle + M_PI_2) * move_speed;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->player->rotate_Angle += move_speed;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->player->rotate_Angle -= move_speed;
    if (
        game->map[(int)(next_posy - radius)][(int)(next_posx - radius)] != '1' &&
        game->map[(int)(next_posy - radius)][(int)(next_posx + radius)] != '1' &&
        game->map[(int)(next_posy + radius)][(int)(next_posx - radius)] != '1' &&
        game->map[(int)(next_posy + radius)][(int)(next_posx + radius)] != '1'
    )
    {
        game->player->pos_x = next_posx;
        game->player->pos_y = next_posy;
    }
    mlx_delete_image(game->mlx, game->img);
    game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    mlx_image_to_window(game->mlx, game->img, 0, 0);
	castRays(game);
    // draw_black_cover(game->map, game);
    draw_map(game->map, game);
	// draw_player(game);
	// draw_line(game);
}

void draw_square_player(double x, double y, int size, int color, t_cube *game)
{
    double i;
	double j;

	i = -size / 2;
	while (i < size / 2)
	{
		j = -size / 2;
		while (j < size / 2)
		{
			mlx_put_pixel(game->img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

// void draw_player(t_cube *game)
// {
//     double pixel_x;
//     double pixel_y;

//     pixel_x = game->player->pos_x * (TILE_SIZE + 1);
//     pixel_y = game->player->pos_y * (TILE_SIZE + 1);
//     draw_square_player(MINIMAP_SCALE * pixel_x, MINIMAP_SCALE * pixel_y, MINIMAP_SCALE * PLAYER_SIZE, 0xFF0000FF, game);
// }
