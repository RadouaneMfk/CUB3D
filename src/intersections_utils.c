/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 10:39:31 by rmouafik          #+#    #+#             */
/*   Updated: 2025/12/21 12:09:20 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_vars(t_var *v, t_cube *game)
{
	v->ceil_size = TILE_SIZE;
	v->horzwallhit = 0;
	v->vertwallhit = 0;
	v->player_px = game->player->pos_x * v->ceil_size;
	v->player_py = game->player->pos_y * v->ceil_size;
	v->map_height = 0;
	while (game->map[v->map_height])
		v->map_height++;
	v->map_width = ft_strlen(game->map[0]);
}

void	check_horizontal_intercept(t_var *v, double a)
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
	v->nexthorz_x = v->x_intercept;
	v->nexthorz_y = v->y_intercept;
}

void	find_horizontal_hit(t_var *v, double a, t_cube *g)
{
	check_horizontal_intercept(v, a);
	while (v->nexthorz_x > 0 && v->nexthorz_x <= v->map_width * TILE_SIZE
		&& v->nexthorz_y > 0 && v->nexthorz_y <= v->map_height * TILE_SIZE)
	{
		v->map_x = (int)(v->nexthorz_x / v->ceil_size);
		v->map_y = (int)(v->nexthorz_y / v->ceil_size);
		if (sin(a) < 0)
			v->map_y = (int)((v->nexthorz_y - 1) / v->ceil_size);
		if (v->map_y < 0 || v->map_y >= v->map_height
			|| v->map_x < 0 || v->map_x >= v->map_width)
			break ;
		if (g->map[v->map_y][v->map_x] == '1')
		{
			v->horzwallhit = 1;
			v->horzwallhit_x = v->nexthorz_x;
			v->horzwallhit_y = v->nexthorz_y;
			break ;
		}
		v->nexthorz_x += v->x_step;
		v->nexthorz_y += v->y_step;
	}
}

void	check_vertical_intercept(t_var *v, double a)
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
	v->nextvert_x = v->x_intercept;
	v->nextvert_y = v->y_intercept;
}

void	find_vertical_hit(t_var *v, double a, t_cube *g)
{
	check_vertical_intercept(v, a);
	while (v->nextvert_x > 0 && v->nextvert_x <= v->map_width * TILE_SIZE
		&& v->nextvert_y > 0 && v->nextvert_y <= v->map_height * TILE_SIZE)
	{
		v->map_x = (int)(v->nextvert_x / v->ceil_size);
		v->map_y = (int)(v->nextvert_y / v->ceil_size);
		if (cos(a) < 0)
			v->map_x = (int)((v->nextvert_x - 1) / v->ceil_size);
		if (v->map_y < 0 || v->map_y >= v->map_height
			|| v->map_x < 0 || v->map_x >= v->map_width)
			break ;
		if (g->map[v->map_y][v->map_x] == '1')
		{
			v->vertwallhit = 1;
			v->vertwallhit_x = v->nextvert_x;
			v->vertwallhit_y = v->nextvert_y;
			break ;
		}
		v->nextvert_x += v->x_step;
		v->nextvert_y += v->y_step;
	}
}
