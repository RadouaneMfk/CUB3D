#include "../includes/cub3d.h"

void init_player(char **map, t_cube *cube)
{
	int	i;
	int	j;

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
	t_var var;

    game = (t_cube *)param;
    var.next_posx = game->player->pos_x;
    var.next_posy = game->player->pos_y;
    var.move_speed = 0.05;
    var.radius = 0.14;
	var.walk = 0;
	var.center_x = WIDTH / 2;
	var.center_y = HEIGHT / 2;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT_CONTROL))
	{
		if (game->player->mouse_lock == false)
		{
			game->player->mouse_lock = true;
			mlx_set_mouse_pos(game->mlx, var.center_x, var.center_y);
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
			game->player->prev_mouse_x = var.center_x;
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
		mlx_set_mouse_pos(game->mlx, var.center_x, var.center_y);
		var.delta = game->player->cursor_x - game->player->prev_mouse_x;
		game->player->rotate_Angle += var.delta * 0.0015;
		game->player->prev_mouse_x = var.center_x;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
    if (mlx_is_key_down(game->mlx, MLX_KEY_W))
        var.walk = var.move_speed;
    if (mlx_is_key_down(game->mlx, MLX_KEY_S))
        var.walk = -var.move_speed;
	var.next_posx = game->player->pos_x + cos(game->player->rotate_Angle) * var.walk;
	var.next_posy = game->player->pos_y + sin(game->player->rotate_Angle) * var.walk;
    if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		var.next_posx += cos(game->player->rotate_Angle + M_PI_2) * var.move_speed;
		var.next_posy += sin(game->player->rotate_Angle + M_PI_2) * var.move_speed;
	}
    if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
        var.next_posx -= cos(game->player->rotate_Angle + M_PI_2) * var.move_speed;
        var.next_posy -= sin(game->player->rotate_Angle + M_PI_2) * var.move_speed;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->player->rotate_Angle += var.move_speed;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->player->rotate_Angle -= var.move_speed;
    if (
        game->map[(int)(var.next_posy - var.radius)][(int)(var.next_posx - var.radius)] != '1' &&
        game->map[(int)(var.next_posy - var.radius)][(int)(var.next_posx + var.radius)] != '1' &&
        game->map[(int)(var.next_posy + var.radius)][(int)(var.next_posx - var.radius)] != '1' &&
        game->map[(int)(var.next_posy + var.radius)][(int)(var.next_posx + var.radius)] != '1'
    )
    {
        game->player->pos_x = var.next_posx;
        game->player->pos_y = var.next_posy;
    }
    mlx_delete_image(game->mlx, game->img);
    game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    mlx_image_to_window(game->mlx, game->img, 0, 0);
	castRays(game);
    draw_map(game->map, game);
}
