/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 09:34:30 by rmouafik          #+#    #+#             */
/*   Updated: 2025/11/02 11:57:16 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void draw_line(t_cube *game)
{
    int center_x = game->player->pos_x * (TILE_SIZE + 1);
    int center_y = game->player->pos_y * (TILE_SIZE + 1);
    int end_x = center_x + cos(game->player->rotate_Angle) * 40;
    int end_y = center_y + sin(game->player->rotate_Angle) * 40;

    for (int i = 0; i < 40; i++)
    {
        int x = center_x + (end_x - center_x) * i / 40;
        int y = center_y + (end_y - center_y) * i / 40;
        mlx_put_pixel(game->img, x, y, 0xFF0000FF);
    }
}

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

void draw_square_player(double x, double y, int size, int color, t_cube *game)
{
    double i = -size / 2;
	double j;

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

void draw_player(t_cube *game)
{
    double pixel_x;
    double pixel_y;

    pixel_x = game->player->pos_x * (TILE_SIZE + 1);
    pixel_y = game->player->pos_y * (TILE_SIZE + 1);

    draw_square_player(pixel_x, pixel_y, PLAYER_SIZE, 0xFF0000FF, game);
}

void draw_map(char **map, t_cube *game)
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
            if (map[i][j] == '1')
                draw_square(screen_x, screen_y, TILE_SIZE, 0x000000FF, game);
            else if (map[i][j] == '0')
                draw_square(screen_x, screen_y, TILE_SIZE, 0xFFFFFFFF, game);
			else if (map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'S' || map[i][j] == 'E')
			{
                draw_square(screen_x, screen_y, TILE_SIZE, 0xFFFFFFFF, game);
			}
            j++;
        }
        i++;
    }
	draw_player(game);
	draw_line(game);
}

void update_player(void *param)
{
    t_cube *game = (t_cube *)param;
    double next_posx = game->player->pos_x;
    double next_posy = game->player->pos_y;
    double move_speed = 0.05;
    double radius = 0.14;
	double walk = 0;

    if (mlx_is_key_down(game->mlx, MLX_KEY_W))
        walk = move_speed;
    if (mlx_is_key_down(game->mlx, MLX_KEY_S))
        walk = -move_speed;
	next_posx = game->player->pos_x +  cos(game->player->rotate_Angle) * walk;
	next_posy = game->player->pos_y + sin(game->player->rotate_Angle) * walk;
    if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
        next_posx += move_speed;
	}
    if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
        next_posx -= move_speed;
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
    draw_map(game->map, game);
}

void init_player(char **map, t_cube *cube)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
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
			j++;
		}
		i++;
	}
}

int main()
{
    t_cube game;

	char *test_map[] =
	{
    	"111111111111",
    	"100000000001",
    	"101111110001",
    	"100100010011",
    	"100100010111",
    	"100000010001",
    	"10110E000001",
    	"111111111111",
    	NULL
	};
	game.map = test_map;
	game.player = malloc(sizeof(t_player));
	if (!game.player)
		return 1;
    game.mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true);
    game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
    mlx_image_to_window(game.mlx , game.img, 0, 0);
	init_player(test_map, &game);
	draw_map(test_map, &game);
	mlx_loop_hook(game.mlx, update_player, &game);
    mlx_loop(game.mlx);
    return 0;
}
