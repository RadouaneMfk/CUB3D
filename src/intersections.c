#include "../includes/cub3d.h"

void	init_vars(t_var *v, t_cube *game)
{
	v->ceil_size = TILE_SIZE;
	v->HorzWallHit = 0;
	v->VertWallHit = 0;
	v->player_px = game->player->pos_x * v->ceil_size;
	v->player_py = game->player->pos_y * v->ceil_size;
	v->map_height = 0;
	while (game->map[v->map_height])
		v->map_height++;
	v->map_width = ft_strlen(game->map[0]);
	// printf("%d\n", v->side_hit);
}

void	find_horizontal_hit(t_var *v, double a, t_cube *g)
{
	v->y_intercept = floor(v->player_py / v->ceil_size) * v->ceil_size;
	if (sin(a) > 0)
		v->y_intercept += v->ceil_size;
	v->x_intercept = v->player_px + ((v->y_intercept - v->player_py) / tan(a));
	v->y_step = v->ceil_size;
	if (sin(a) < 0)
		v->y_step *= -1;
	else
		v->y_step *= 1;
	v->x_step = v->ceil_size / tan(a);
	if ((cos(a) < 0 && v->x_step > 0) || (cos(a) > 0 && v->x_step < 0))
		v->x_step *= -1;
	v->nextHorz_x = v->x_intercept;
	v->nextHorz_y = v->y_intercept;
	while (v->nextHorz_x > 0 && v->nextHorz_x <= v->map_width * TILE_SIZE
		&& v->nextHorz_y > 0 && v->nextHorz_y <= v->map_height * TILE_SIZE)
	{
		v->map_x = (int)(v->nextHorz_x / v->ceil_size);
		v->map_y = (int)(v->nextHorz_y / v->ceil_size);
		if (sin(a) < 0)
			v->map_y = (int)((v->nextHorz_y - 1) / v->ceil_size);
		if (v->map_y < 0 || v->map_y >= v->map_height
			|| v->map_x < 0 || v->map_x >= v->map_width)
			break ;
		if (g->map[v->map_y][v->map_x] == '1')
		{
			v->HorzWallHit = 1;
			v->HorzWallHit_x = v->nextHorz_x;
			v->HorzWallHit_y = v->nextHorz_y;
			break ;
		}
		v->nextHorz_x += v->x_step;
		v->nextHorz_y += v->y_step;
	}
}

void	find_vertical_hit(t_var *v, double a, t_cube *g)
{
	v->x_intercept = floor(v->player_px / v->ceil_size) * v->ceil_size;
	if (cos(a) > 0)
		v->x_intercept += v->ceil_size;
	v->y_intercept = v->player_py + ((v->x_intercept - v->player_px) * tan(a));
	v->x_step = v->ceil_size;
	if (cos(a) < 0)
		v->x_step *= -1;
	else
		v->x_step *= 1;
	v->y_step = v->ceil_size * tan(a);
	if ((sin(a) < 0 && v->y_step > 0) || (sin(a) > 0 && v->y_step < 0))
		v->y_step *= -1;
	v->nextVert_x = v->x_intercept;
	v->nextVert_y = v->y_intercept;
	while (v->nextVert_x > 0 && v->nextVert_x <= v->map_width * TILE_SIZE
		&& v->nextVert_y > 0 && v->nextVert_y <= v->map_height * TILE_SIZE)
	{
		v->map_x = (int)(v->nextVert_x / v->ceil_size);
		v->map_y = (int)(v->nextVert_y / v->ceil_size);
		if (cos(a) < 0)
			v->map_x = (int)((v->nextVert_x - 1) / v->ceil_size);
		if (v->map_y < 0 || v->map_y >= v->map_height
			|| v->map_x < 0 || v->map_x >= v->map_width)
			break ;
		if (g->map[v->map_y][v->map_x] == '1')
		{
			v->VertWallHit = 1;
			v->VertWallHit_x = v->nextVert_x;
			v->VertWallHit_y = v->nextVert_y;
			break ;
		}
		v->nextVert_x += v->x_step;
		v->nextVert_y += v->y_step;
	}
}

void	select_hit(t_var *v)
{
	if (v->HorzWallHit == 1)
	{
		// v->side_hit = HORIZONTAL;
		v->HorzHitDistance = ft_distance(v->player_px, v->player_py,
				v->HorzWallHit_x, v->HorzWallHit_y);
	}
	else
		v->HorzHitDistance = 500000;
	if (v->VertWallHit == 1)
	{
		// v->hit_offset = (int)v->WallHitY % TILE_SIZE;
		// v->side_hit = VERTICAL;
		v->VertHitDistance = ft_distance(v->player_px, v->player_py,
				v->VertWallHit_x, v->VertWallHit_y);
	}
	else
		v->VertHitDistance = 500000;
	if (v->HorzHitDistance < v->VertHitDistance)
	{
		v->WallHitX = v->HorzWallHit_x;
		v->WallHitY = v->HorzWallHit_y;
		v->rayDistance = v->HorzHitDistance;
	}
	else
	{
		v->WallHitX = v->VertWallHit_x;
		v->WallHitY = v->VertWallHit_y;
		v->rayDistance = v->VertHitDistance;
	}
}

void	compute_projection(t_var *v, int rayId, t_cube *g, double ray_angle)
{
	int y = 0;
	v->DistanceProjectionPlane = (WIDTH / 2) / tan(FOV / 2);
	v->WallStripHeight = (v->ceil_size / (v->rayDistance * cos(ray_angle - g->player->rotate_Angle)))
		* v->DistanceProjectionPlane;
	v->top = (HEIGHT / 2) - (v->WallStripHeight / 2);
	v->bottom = (HEIGHT / 2) + (v->WallStripHeight / 2);
	if (v->top < 0)
		v->top = 0;
	if (v->bottom >= HEIGHT)
		v->bottom = HEIGHT - 1;
	if (v->HorzWallHit)
	{
		v->side_hit = HORIZONTAL;
		v->hit_offset = (int)v->WallHitX % TILE_SIZE;
		if (sin(ray_angle) > 0)
			g->texture = g->tex_north;
		else
			g->texture = g->tex_south;
	}
	else if (v->VertWallHit)
	{
		v->side_hit = VERTICAL;
		v->hit_offset = (int)v->WallHitX % TILE_SIZE;
		if (cos(ray_angle) > 0)
			g->texture = g->tex_west;
		else
			g->texture = g->tex_east;
	}
	while (y < v->top)
	{
		mlx_put_pixel(g->img, rayId, y, 0x000000ff);
		y++;
	}
	y = v->top;
	while (y < v->bottom)
	{
		g->tex_x = v->hit_offset * g->texture->width / TILE_SIZE;
		g->tex_y = ((y - v->top) / v->WallStripHeight) * g->texture->height;
		g->pixel_index = (g->tex_y * g->texture->width + g->tex_x) * 4;
		int color = ((g->pixel_index) << 24) | ((g->pixel_index + 1) << 16) | ((g->pixel_index + 2) << 8) | (g->pixel_index + 3);
		mlx_put_pixel(g->img, rayId, y, color);
		y++;
	}
	y = v->bottom;
	while (y < HEIGHT)
	{
		mlx_put_pixel(g->img, rayId, y, 0x000000ff);
		y++;
	}
}
