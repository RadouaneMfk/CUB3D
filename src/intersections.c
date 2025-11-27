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
		v->HorzHitDistance = ft_distance(v->player_px, v->player_py,
				v->HorzWallHit_x, v->HorzWallHit_y);
	}
	else
		v->HorzHitDistance = 500000;
	if (v->VertWallHit == 1)
	{
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
		v->hit_offset = (int)v->WallHitX % v->ceil_size;
		if (v->hit_offset < 0)
			v->hit_offset += v->ceil_size;
		if (sin(ray_angle) > 0)
			g->texture = g->tex_north;
		else
			g->texture = g->tex_south;
	}
	else if (v->VertWallHit)
	{
		v->side_hit = VERTICAL;
		v->hit_offset = (int)v->WallHitY % v->ceil_size;
		if (v->hit_offset < 0)
			v->hit_offset += v->ceil_size;
		if (cos(ray_angle) > 0)
			g->texture = g->tex_west;
		else
			g->texture = g->tex_east;
	}
	else
		return ;
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
		int color = (g->texture->pixels[g->pixel_index]) + (g->texture->pixels[g->pixel_index + 1]) + (g->texture->pixels[g->pixel_index + 2]) + (g->texture->pixels[g->pixel_index + 3]);
		int color2 = ((g->texture->pixels[g->pixel_index]) << 24) | ((g->texture->pixels[g->pixel_index + 1]) << 16) | ((g->texture->pixels[g->pixel_index + 2]) << 8) | (g->texture->pixels[g->pixel_index + 3]);
		// printf("-->%d\n", color);
		mlx_put_pixel(g->img, rayId, y, color2);
		y++;
	}
	y = v->bottom;
	while (y < HEIGHT)
	{
		mlx_put_pixel(g->img, rayId, y, 0x000000ff);
		y++;
	}
}

// void compute_projection(t_var *v, int rayId, t_cube *g, double ray_angle)
// {
//     int y = 0;

//     /* projection calculations (unchanged logic) */
//     v->DistanceProjectionPlane = (WIDTH / 2) / tan(FOV / 2);
//     /* correct for fish-eye by dividing by cos(ray - player_angle) */
//     v->WallStripHeight = (v->ceil_size / (v->rayDistance * cos(ray_angle - g->player->rotate_Angle)))
//         * v->DistanceProjectionPlane;
//     v->top = (HEIGHT / 2) - (v->WallStripHeight / 2);
//     v->bottom = (HEIGHT / 2) + (v->WallStripHeight / 2);
//     if (v->top < 0)
//         v->top = 0;
//     if (v->bottom >= HEIGHT)
//         v->bottom = HEIGHT - 1;

//     /* choose which texture and compute hit offset (ensure all units are pixels) */
//     /* hit_offset must be distance along the wall in PIXELS [0 .. ceil_size) */
//     if (v->HorzWallHit)
//     {
//         v->side_hit = HORIZONTAL;
//         /* WallHitX and WallHitY are in pixels — offset along wall for horizontal hit is X */
//         v->hit_offset = ((int)v->WallHitX) % v->ceil_size;
//         if (v->hit_offset < 0)
//             v->hit_offset += v->ceil_size;
//         if (sin(ray_angle) > 0)
//             g->texture = g->tex_north;
//         else
//             g->texture = g->tex_south;
//     }
//     else if (v->VertWallHit)
//     {
//         v->side_hit = VERTICAL;
//         /* for vertical hit the varying coord along the wall is Y */
//         v->hit_offset = ((int)v->WallHitY) % v->ceil_size;
//         if (v->hit_offset < 0)
//             v->hit_offset += v->ceil_size;
//         if (cos(ray_angle) > 0)
//             g->texture = g->tex_west;
//         else
//             g->texture = g->tex_east;
//     }
//     else
//     {
//         /* no hit: draw background and return early */
//         ft_draw_line(rayId, 0, rayId, HEIGHT, 0xFF00FF00, g); /* debug color */
//         return;
//     }

//     /* draw ceiling (top) */
//     while (y < v->top)
//     {
//         mlx_put_pixel(g->img, rayId, y, 0x000000ff);
//         y++;
//     }

//     /* prepare texture sampling */
//     mlx_texture_t *tex = g->texture;
//     int tex_w = 0;
//     int tex_h = 0;
//     unsigned char *pixels = NULL;
//     size_t tex_pixels_len = 0;

//     if (tex)
//     {
//         tex_w = tex->width;
//         tex_h = tex->height;
//         pixels = tex->pixels;
//         /* pixels length should be tex_w * tex_h * 4 */
//         tex_pixels_len = (size_t)tex_w * (size_t)tex_h * 4ULL;
//     }

//     /* clamp ceil_size to avoid division by zero or weird math */
//     if (v->ceil_size <= 0)
//         v->ceil_size = TILE_SIZE > 0 ? TILE_SIZE : 64;

//     /* draw wall slice with texture sampling */
//     y = v->top;
//     while (y < v->bottom)
//     {
//         /* map hit_offset in [0, ceil_size) to texture x in [0, tex_w) */
//         int tex_x = 0;
//         int tex_y = 0;

//         if (tex && tex_w > 0)
//         {
//             double fx = ((double)v->hit_offset / (double)v->ceil_size) * (double)tex_w;
//             /* ensure fx in [0, tex_w) and convert to integer coordinate */
//             if (fx < 0.0)
//                 fx = 0.0;
//             if (fx >= (double)tex_w)
//                 fx = (double)tex_w - 1.0;
//             tex_x = (int)fx;
//         }

//         /* map screen y into texture y */
//         if (tex && tex_h > 0)
//         {
//             double column_height = (double)(v->bottom - v->top);
//             if (column_height <= 0.0)
//                 column_height = 1.0;
//             double rel = ((double)(y - v->top) / column_height); /* [0,1) */
//             double fy = rel * (double)tex_h;
//             if (fy < 0.0)
//                 fy = 0.0;
//             if (fy >= (double)tex_h)
//                 fy = (double)tex_h - 1.0;
//             tex_y = (int)fy;
//         }

//         /* sample pixel safely */
//         unsigned int color = 0x00FF00FF; /* fallback magenta debug color */
//         if (pixels && tex_w > 0 && tex_h > 0)
//         {
//             size_t pindex = ((size_t)tex_y * (size_t)tex_w + (size_t)tex_x) * 4ULL;
//             if (pindex + 3 < tex_pixels_len)
//             {
//                 /* pixels layout: R, G, B, A (typical from LodePNG / MLX) */
//                 unsigned int R = (unsigned int)pixels[pindex + 0];
//                 unsigned int G = (unsigned int)pixels[pindex + 1];
//                 unsigned int B = (unsigned int)pixels[pindex + 2];
//                 unsigned int A = (unsigned int)pixels[pindex + 3];

//                 /* MLX expects 0xAARRGGBB */
//                 color = (A << 24) | (R << 16) | (G << 8) | B;
//             }
//             else
//             {
//                 /* out-of-bounds: use debug color */
//                 color = 0xFFFF00FF; /* magenta */
//             }
//         }
//         else
//         {
//             /* no texture: use plain white for walls so you can see them */
//             color = 0xFFFFFFFF;
//         }

//         mlx_put_pixel(g->img, rayId, y, color);
//         y++;
//     }

//     /* draw floor (bottom) */
//     y = v->bottom;
//     while (y < HEIGHT)
//     {
//         mlx_put_pixel(g->img, rayId, y, 0x000000ff);
//         y++;
//     }
// }
