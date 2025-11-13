/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 09:34:30 by rmouafik          #+#    #+#             */
/*   Updated: 2025/11/13 13:11:04 by rmouafik         ###   ########.fr       */
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

void ft_draw_line(double x0, double y0, double x1, double y1, int color, t_cube *game)
{
    double dx = x1 - x0;
    double dy = y1 - y0;
    double distance = sqrt(dx * dx + dy * dy);
    double step_x = dx / distance;
    double step_y = dy / distance;

    while (distance > 0)
    {
        mlx_put_pixel(game->img, (int)x0, (int)y0, color);
        x0 += step_x;
        y0 += step_y;
        distance -= 1;
    }
}
double ft_distance(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
void ft_cast_ray(int rayId, double ray_angle, t_cube *game)
{
	double x_intercept;
	double y_intercept;
	double x_step;
	double y_step;
	double nextHorz_x;
	double nextHorz_y;
	double nextVert_x;
	double nextVert_y;
	double HorzWallHit_x;
	double HorzWallHit_y;
	double VertWallHit_x;
	double VertWallHit_y;
	double player_px = game->player->pos_x * (TILE_SIZE + 1);
	double player_py = game->player->pos_y * (TILE_SIZE + 1);
	int HorzWallHit = 0;
	int VertWallHit = 0;

	//-----------------------------------
	// HORIZONTAL INTERCEPTS
	//-----------------------------------
	y_intercept = floor(player_py / (TILE_SIZE + 1)) * (TILE_SIZE + 1);
	if (sin(ray_angle) > 0)
		y_intercept += (TILE_SIZE + 1);
	else
		y_intercept += 0;

	x_intercept = player_px + ((y_intercept - player_py) / tan(ray_angle));

	y_step = (TILE_SIZE + 1);
	if (sin(ray_angle) < 0)
		y_step *= -1;
	else
		y_step *= 1;

	x_step = (TILE_SIZE + 1) / tan(ray_angle);
	if ((cos(ray_angle) < 0 && x_step > 0) || (cos(ray_angle) > 0 && x_step < 0))
		x_step *= -1;

	nextHorz_x = x_intercept;
	nextHorz_y = y_intercept;
	// if (sin(ray_angle) < 0)
	// 	nextHorz_y--;
	int map_height = 0;
	while (game->map[map_height])
		map_height++;
	int map_width = ft_strlen(game->map[0]);
	while (nextHorz_x > 0 && nextHorz_x <= WIDTH && nextHorz_y > 0 && nextHorz_y <= HEIGHT)
	{
		int map_x = (int)(nextHorz_x / (TILE_SIZE + 1));
		int map_y = (int)(nextHorz_y / (TILE_SIZE + 1));
		if (sin(ray_angle) < 0)
			map_y = (int)((nextHorz_y - 1) / (TILE_SIZE + 1));
		if (map_y < 0 || map_y >= map_height || map_x < 0 || map_x >= map_width)
			break ;
		if (game->map[map_y][map_x] == '1')
		{
			HorzWallHit = 1;
			HorzWallHit_x = nextHorz_x;
			HorzWallHit_y = nextHorz_y;
			break;
		}
		else
		{
			nextHorz_x += x_step;
			nextHorz_y += y_step;
		}
	}
	//-----------------------------------
	// VERTICAL INTERCEPTS
	//-----------------------------------
	x_intercept = floor(player_px / (TILE_SIZE + 1)) * (TILE_SIZE  + 1);
	if (cos(ray_angle) > 0)
		x_intercept += (TILE_SIZE + 1);
	else
		x_intercept += 0;

	y_intercept = player_py + ((x_intercept - player_px) * tan(ray_angle));

	x_step = (TILE_SIZE + 1);
	if (cos(ray_angle) < 0)
		x_step *= -1;
	else
		x_step *= 1;

	y_step = (TILE_SIZE + 1) * tan(ray_angle);
	if ((sin(ray_angle) < 0 && y_step > 0) || (sin(ray_angle) > 0 && y_step < 0))
		y_step *= -1;

	nextVert_x = x_intercept;
	nextVert_y = y_intercept;
	// if (cos(ray_angle) < 0)
	// 	nextVert_x--;
	while (nextVert_x > 0 && nextVert_x <= WIDTH && nextVert_y > 0 && nextVert_y <= HEIGHT)
	{
		int map_x = (int)(nextVert_x / (TILE_SIZE + 1));
		int map_y = (int)(nextVert_y / (TILE_SIZE + 1));
		if (cos(ray_angle) < 0)
			map_x = (int)((nextVert_x - 1) / (TILE_SIZE + 1));
		if (map_y < 0 || map_y >= map_height || map_x < 0 || map_x >= map_width)
			break ;
		if (game->map[map_y][map_x] == '1')
		{
			VertWallHit = 1;
			VertWallHit_x = nextVert_x;
			VertWallHit_y = nextVert_y;
			break ;
		}
		else
		{
			nextVert_x += x_step;
			nextVert_y += y_step;
		}
	}
	//-----------------------------------
	// DISTANCE CALCULATION
	//-----------------------------------
	double HorzHitDistance;
	double VertHitDistance;
	double WallHitX;
	double WallHitY;

	if (HorzWallHit == 1)
		HorzHitDistance = ft_distance(player_px, player_py, HorzWallHit_x, HorzWallHit_y);
	else
		HorzHitDistance = 500000;

	if (VertWallHit == 1)
		VertHitDistance = ft_distance(player_px, player_py, VertWallHit_x, VertWallHit_y);
	else
		VertHitDistance = 500000;
	if (HorzHitDistance < VertHitDistance)
	{
		WallHitX = HorzWallHit_x;
		WallHitY = HorzWallHit_y;
	}
	else
	{
		WallHitX = VertWallHit_x;
		WallHitY = VertWallHit_y;
	}
	double rayDistance;
	if (HorzHitDistance < VertHitDistance)
		rayDistance = HorzHitDistance;
	else
		rayDistance = VertHitDistance;
	double DistanceProjectionPlane = (WIDTH / 2) / tan(FOV / 2);
	double WallStripHeight = ((TILE_SIZE + 1) / rayDistance) * DistanceProjectionPlane;
	double top = (HEIGHT / 2) - (WallStripHeight / 2);
	double bottom = (HEIGHT / 2) + (WallStripHeight / 2);
	if (rayId < 0 || rayId >= WIDTH)
    	return;
	if (top < 0)
    	top = 0;
	if (bottom >= HEIGHT)
    	bottom = HEIGHT - 1;

	ft_draw_line(rayId, top, rayId, bottom, 0x0000FFFF, game);
	ft_draw_line(MINIMAP_SCALE * player_px, MINIMAP_SCALE * player_py, MINIMAP_SCALE * WallHitX, MINIMAP_SCALE * WallHitY, 0xFF0000FF, game);
}

// void ft_cast_ray(double ray_angle, t_cube *game)
// {
// 	double x_intercept;
// 	double y_intercept;
// 	double x_step;
// 	double y_step;
// 	double nextHorz_x;
// 	double nextHorz_y;
// 	double nextVert_x;
// 	double nextVert_y;
// 	double HorzWallHit_x;
// 	double HorzWallHit_y;
// 	double VertWallHit_x;
// 	double VertWallHit_y;
// 	double player_px = game->player->pos_x * (TILE_SIZE + 1);
// 	double player_py = game->player->pos_y * (TILE_SIZE + 1);
// 	int HorzWallHit = 0;
// 	int VertWallHit = 0;

// 	y_intercept = floor(player_py/ TILE_SIZE) * TILE_SIZE;
// 	if (sin(ray_angle) > 0)
// 		y_intercept += TILE_SIZE;
// 	else
// 		y_intercept += 0;
// 	x_intercept = player_px + ((y_intercept - player_py) / tan(ray_angle));
// 	y_step = TILE_SIZE;
// 	if (sin(ray_angle) < 0)
// 		y_step *= -1;
// 	else
// 		y_step *= 1;
// 	x_step = TILE_SIZE / tan(ray_angle);
// 	if (cos(ray_angle) < 0 && x_step > 0)
// 		x_step *= -1;
// 	else
// 		x_step *= 1;
// 	if (cos(ray_angle) > 0 && x_step < 0)
// 		x_step *= -1;
// 	else
// 		x_step *= 1;
// 	nextHorz_x = x_intercept;
// 	nextHorz_y = y_intercept;
// 	if (sin(ray_angle) < 0)
// 		nextHorz_y--;
// 	while (nextHorz_x > 0 && nextHorz_x <= WIDTH && nextHorz_y > 0 && nextHorz_y <= HEIGHT)
// 	{
// 		if (game->map[(int)nextHorz_y / TILE_SIZE][(int)nextHorz_x / TILE_SIZE] == '1')
// 		{
// 			HorzWallHit = 1;
// 			HorzWallHit_x = nextHorz_x;
// 			HorzWallHit_y = nextHorz_y;
// 			break ;
// 		}
// 		else
// 		{
// 			nextHorz_x += x_step;
// 			nextHorz_y += y_step;
// 		}
// 	}
	
// 	/////////////////////////////
	
// 	x_intercept = floor(player_px / TILE_SIZE) * TILE_SIZE;
// 	if (sin(ray_angle) > 0)
// 		x_intercept += TILE_SIZE;
// 	else
// 		x_intercept += 0;
// 	y_intercept = player_px + ((x_intercept - player_px) * tan(ray_angle));
// 	y_step = TILE_SIZE;
// 	if (sin(ray_angle) < 0)
// 		y_step *= -1;
// 	else
// 		y_step *= 1;
// 	y_step = TILE_SIZE * tan(ray_angle);
// 	if (cos(ray_angle) < 0 && y_step > 0)
// 		y_step *= -1;
// 	else
// 		y_step *= 1;
// 	if (cos(ray_angle) > 0 && y_step < 0)
// 		y_step *= -1;
// 	else
// 		y_step *= 1;
// 	nextVert_x = x_intercept;
// 	nextVert_y = y_intercept;
// 	if (sin(ray_angle) < 0)
// 		nextVert_x--;
// 	while (nextVert_x > 0 && nextVert_x <= WIDTH && nextVert_y > 0 && nextVert_y <= HEIGHT)
// 	{
// 		if (game->map[(int)nextVert_y / TILE_SIZE][(int)nextVert_x / TILE_SIZE] == '1')
// 		{
// 			VertWallHit = 1;
// 			VertWallHit_x = nextVert_x;
// 			VertWallHit_y = nextVert_y;
// 			break ;
// 		}
// 		else
// 		{
// 			nextVert_x += x_step;
// 			nextVert_y += y_step;
// 		}
// 	}
// 	double HorzHitDistance;
// 	double VertHitDistance;
// 	double WallHitX;
// 	double WallHitY;
// 	double distance;
// 	if (HorzWallHit)
// 		HorzHitDistance = ft_distance(player_px, player_py, HorzWallHit_x, HorzHitDistance);
// 	else
// 		HorzHitDistance = 1000;
// 	if (VertWallHit)
// 		VertHitDistance = ft_distance(player_px, player_py, VertWallHit_x, VertWallHit_y);
// 	else
// 		VertHitDistance = 1000;
// 	if (HorzHitDistance < VertHitDistance)
// 	{
// 		WallHitX = HorzWallHit_x;
// 		distance = HorzHitDistance;
// 	}
// 	else
// 	{
// 		WallHitX = VertWallHit_x;
// 		distance = VertHitDistance;
// 	}
// 	if (HorzHitDistance < VertHitDistance)
// 		WallHitY = HorzWallHit_y;
// 	else
// 		WallHitY = VertWallHit_y;
// 	ft_draw_line(player_px, player_py, WallHitX, WallHitY, 0xFF0000FF, game);
// }

void castRays(t_cube *game)
{
	int start_x = game->player->pos_x * (TILE_SIZE + 1);
	int start_y = game->player->pos_y * (TILE_SIZE + 1);
	int num_rays = WIDTH;
	double ray_increment = FOV / num_rays;
	double ray_angle = game->player->rotate_Angle - (FOV / 2);

	int rayId = 0;
	while (rayId < num_rays)
	{
		if (ray_angle < 0)
			ray_angle += 2 * M_PI;
		if (ray_angle > 2 * M_PI)
			ray_angle -= 2 * M_PI;
		// double ray_dirx = cos(ray_angle);
		// double ray_diry = sin(ray_angle);
		// int ray_length = 60;
        // int end_x = start_x + ray_dirx * ray_length;
        // int end_y = start_y + ray_diry * ray_length;
		ft_cast_ray(rayId, ray_angle, game);
		// ft_draw_line(start_x, start_y, end_x, end_y, 0xFF0000FF, game);
		ray_angle += ray_increment;
		rayId++;
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
    draw_square_player(MINIMAP_SCALE * pixel_x, MINIMAP_SCALE * pixel_y, MINIMAP_SCALE * PLAYER_SIZE, 0xFF0000FF, game);
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
                draw_square(MINIMAP_SCALE * screen_x, MINIMAP_SCALE * screen_y, MINIMAP_SCALE * TILE_SIZE, 0x000000FF, game);
            else if (map[i][j] == '0')
                draw_square(MINIMAP_SCALE * screen_x, MINIMAP_SCALE * screen_y, MINIMAP_SCALE * TILE_SIZE, 0xFFFFFFFF, game);
			else if (map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'S' || map[i][j] == 'E')
			{
                draw_square(MINIMAP_SCALE * screen_x, MINIMAP_SCALE * screen_y, MINIMAP_SCALE * TILE_SIZE, 0xFFFFFFFF, game);
			}
            j++;
        }
        i++;
    }
	// draw_line(game);
	castRays(game);
	draw_player(game);
}

void update_player(void *param)
{
    t_cube *game = (t_cube *)param;
    double next_posx = game->player->pos_x;
    double next_posy = game->player->pos_y;
    double move_speed = 0.05;
    double radius = 0.14;
	double walk = 0;

	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		exit(0);
    if (mlx_is_key_down(game->mlx, MLX_KEY_W))
        walk = move_speed;
    if (mlx_is_key_down(game->mlx, MLX_KEY_S))
        walk = -move_speed;
	next_posx = game->player->pos_x +  cos(game->player->rotate_Angle) * walk;
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
    	"10000W010001",
    	"101100000001",
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
