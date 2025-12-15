#include "../includes/cub3d.h"

void	select_hit(t_var *v)
{
	calcule_hit_ditance(v);
	if (v->HorzHitDistance < v->VertHitDistance)
	{
		v->flag = HORIZONTAL;
		v->WallHitX = v->HorzWallHit_x;
		v->WallHitY = v->HorzWallHit_y;
		v->rayDistance = v->HorzHitDistance;
	}
	else
	{
		v->flag = VERTICAL;
		v->WallHitX = v->VertWallHit_x;
		v->WallHitY = v->VertWallHit_y;
		v->rayDistance = v->VertHitDistance;
	}
}

void	select_tex(t_var *v, t_cube *g, double ray_angle, t_texture **tex)
{
	if (v->HorzHitDistance < v->VertHitDistance)
	{
		if (sin(ray_angle) > 0)
			(*tex) = &g->textures.so;
		else
			(*tex) = &g->textures.no;
	}
	else
	{
		if (cos(ray_angle) > 0)
			(*tex) = &g->textures.ea;
		else
			(*tex) = &g->textures.we;
	}
	if (v->flag == VERTICAL)
		v->hit_offset = fmod(v->WallHitY, v->ceil_size);
	else
		v->hit_offset = fmod(v->WallHitX, v->ceil_size);
	(*tex)->texX = (int)((v->hit_offset / TILE_SIZE) * (*tex)->width);
}

void	render_textures(int rayid, t_cube *g, t_var *v, t_texture *tex)
{
	tex->y = v->top;
	while (tex->y < v->bottom)
	{
		tex->texY = (int)tex->texPos;
		tex->texPos += tex->step;
		if (tex->texY < 0) 
			tex->texY = 0;
		if (tex->texY >= tex->height) 
			tex->texY = tex->height - 1;
		if (tex->texX < 0) 
			tex->texX = 0;
		if (tex->texX >= tex->width) 
			tex->texX = tex->width - 1;
		tex->index = (tex->texY * tex->width + tex->texX) * 4;
		tex->r = tex->pixels[tex->index + 0];
		tex->g_col = tex->pixels[tex->index + 1];
		tex->b = tex->pixels[tex->index + 2];
		tex->a = tex->pixels[tex->index + 3];
		tex->color = 
			(tex->r << 24) | (tex->g_col << 16) | (tex->b << 8) | tex->a;
		mlx_put_pixel(g->img, rayid, tex->y, tex->color);
		tex->y++;
	}
}

void	draw_textured_wall(int rayid, t_var *v, t_cube *g, double ray_angle)
{
	t_texture	*tex;

	tex = NULL;
	select_tex(v, g, ray_angle, &tex);
	if (v->HorzHitDistance < v->VertHitDistance)
	{
		if (sin(ray_angle) > 0)
			tex->texX = tex->width - tex->texX - 1;
	}
	else
	{
		if (cos(ray_angle) < 0)
			tex->texX = tex->width - tex->texX - 1;
	}
	tex->pixels = (uint8_t *)tex->img->pixels;
	tex->step = 1.0 * tex->height / v->WallStripHeight;
	tex->texPos = (v->top - g->win_h / 2 + v->WallStripHeight / 2) * tex->step;
	render_textures(rayid, g, v, tex);
}

void	compute_projection(t_var *v, int rayid, t_cube *g, double ray_angle)
{
	int	y;

	if (!g->img || g->win_w <= 0 || g->win_h <= 0)
		return ;
	v->DistanceProjectionPlane = (g->win_w / 2) / tan(FOV / 2);
	v->WallStripHeight = (TILE_SIZE / (v->rayDistance * cos(ray_angle - 
					g->player->rotate_Angle))) * v->DistanceProjectionPlane;
	v->top = (g->win_h / 2) - (v->WallStripHeight / 2);
	v->bottom = (g->win_h / 2) + (v->WallStripHeight / 2);
	if (v->top < 0)
		v->top = 0;
	if (v->bottom >= g->win_h)
		v->bottom = g->win_h - 1;
	y = -1;
	while (++y < v->top)
		mlx_put_pixel(g->img, rayid, y, g->cube->ceiling_color);
	draw_textured_wall(rayid, v, g, ray_angle);
	y = v->bottom - 1;
	while (++y < g->win_h)
		mlx_put_pixel(g->img, rayid, y, g->cube->floor_color);
}
