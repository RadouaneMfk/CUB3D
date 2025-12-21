/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 10:38:20 by rmouafik          #+#    #+#             */
/*   Updated: 2025/12/21 12:45:56 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	select_hit(t_var *v)
{
	calcule_hit_ditance(v);
	if (v->horzhitdistance < v->verthitdistance)
	{
		v->flag = HORIZONTAL;
		v->wallhitx = v->horzwallhit_x;
		v->wallhity = v->horzwallhit_y;
		v->raydistance = v->horzhitdistance;
	}
	else
	{
		v->flag = VERTICAL;
		v->wallhitx = v->vertwallhit_x;
		v->wallhity = v->vertwallhit_y;
		v->raydistance = v->verthitdistance;
	}
}

void	select_tex(t_var *v, t_cube *g, double ray_angle, t_texture **tex)
{
	if (v->horzhitdistance < v->verthitdistance)
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
		v->hit_offset = fmod(v->wallhity, v->ceil_size);
	else
		v->hit_offset = fmod(v->wallhitx, v->ceil_size);
	(*tex)->texx = (int)((v->hit_offset / TILE_SIZE) * (*tex)->width);
}

void	render_textures(int rayid, t_cube *g, t_var *v, t_texture *tex)
{
	tex->y = v->top;
	while (tex->y < v->bottom)
	{
		tex->texy = (int)tex->texpos;
		tex->texpos += tex->step;
		if (tex->texy < 0) 
			tex->texy = 0;
		if (tex->texy >= tex->height) 
			tex->texy = tex->height - 1;
		if (tex->texx < 0) 
			tex->texx = 0;
		if (tex->texx >= tex->width) 
			tex->texx = tex->width - 1;
		tex->index = (tex->texy * tex->width + tex->texx) * 4;
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
	if (v->horzhitdistance < v->verthitdistance)
	{
		if (sin(ray_angle) > 0)
			tex->texx = tex->width - tex->texx - 1;
	}
	else
	{
		if (cos(ray_angle) < 0)
			tex->texx = tex->width - tex->texx - 1;
	}
	tex->pixels = (uint8_t *)tex->img->pixels;
	tex->step = 1.0 * tex->height / v->wallstripheight;
	tex->texpos = (v->top - g->win_h / 2 + v->wallstripheight / 2) * tex->step;
	render_textures(rayid, g, v, tex);
}

void	compute_projection(t_var *v, int rayid, t_cube *g, double ray_angle)
{
	int	y;

	if (!g->img || g->win_w <= 0 || g->win_h <= 0)
		return ;
	v->distanceprojectionplane = (g->win_w / 2) / tan(FOV / 2);
	v->wallstripheight = (TILE_SIZE / (v->raydistance * cos(ray_angle - 
					g->player->rotate_angle))) * v->distanceprojectionplane;
	v->top = (g->win_h / 2) - (v->wallstripheight / 2);
	v->bottom = (g->win_h / 2) + (v->wallstripheight / 2);
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
