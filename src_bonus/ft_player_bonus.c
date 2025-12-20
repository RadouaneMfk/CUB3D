/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 10:38:29 by rmouafik          #+#    #+#             */
/*   Updated: 2025/12/20 10:38:30 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_update_vars(t_var *var, t_cube *game)
{
	var->next_posx = game->player->pos_x;
	var->next_posy = game->player->pos_y;
	var->move_speed = 0.05;
	var->radius = 0.14;
	var->walk = 0;
	var->center_x = game->win_w / 2;
	var->center_y = game->win_h / 2;
}

void	ft_keys_down(t_cube *game, t_var *var)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT_CONTROL))
	{
		if (game->player->mouse_lock == false)
		{
			game->player->mouse_lock = true;
			mlx_set_mouse_pos(game->mlx, var->center_x, var->center_y);
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
			game->player->prev_mouse_x = var->center_x;
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
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
}

void	ft_mouse_key(t_cube *game, t_var *var)
{
	if (game->player->mouse_lock)
	{
		mlx_get_mouse_pos
			(game->mlx, &game->player->cursor_x, &game->player->cursor_y);
		mlx_set_mouse_pos(game->mlx, var->center_x, var->center_y);
		var->delta = game->player->cursor_x - game->player->prev_mouse_x;
		game->player->rotate_angle += var->delta * 0.0015;
		game->player->prev_mouse_x = var->center_x;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		var->walk = var->move_speed;
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		var->walk = -var->move_speed;
	var->next_posx = game->player->pos_x + 
		cos(game->player->rotate_angle) * var->walk;
	var->next_posy = game->player->pos_y 
		+ sin(game->player->rotate_angle) * var->walk;
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		var->next_posx += 
			cos(game->player->rotate_angle + M_PI_2) * var->move_speed;
		var->next_posy += 
			sin(game->player->rotate_angle + M_PI_2) * var->move_speed;
	}
}

void	ft_keys_down_2(t_cube *game, t_var *var)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		var->next_posx -= 
			cos(game->player->rotate_angle + M_PI_2) * var->move_speed;
		var->next_posy -= 
			sin(game->player->rotate_angle + M_PI_2) * var->move_speed;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->player->rotate_angle += var->move_speed;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->player->rotate_angle -= var->move_speed;
	if (game->map[(int)(var->next_posy - var->radius)]
			[(int)(var->next_posx - var->radius)] != '1' &&
		game->map[(int)(var->next_posy - var->radius)]
			[(int)(var->next_posx + var->radius)] != '1' &&
		game->map[(int)(var->next_posy + var->radius)]
			[(int)(var->next_posx - var->radius)] != '1' &&
		game->map[(int)(var->next_posy + var->radius)]
			[(int)(var->next_posx + var->radius)] != '1')
	{
		game->player->pos_x = var->next_posx;
		game->player->pos_y = var->next_posy;
	}
}

void	update_player(void *param)
{
	t_cube	*game;
	t_var	var;

	game = (t_cube *)param;
	init_update_vars(&var, game);
	ft_keys_down(game, &var);
	ft_mouse_key(game, &var);
	ft_keys_down_2(game, &var);
	mlx_delete_image(game->mlx, game->img);
	game->img = mlx_new_image(game->mlx, game->win_w, game->win_h);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	cast_rays(game);
	if (game->win_h > 100 && game->win_w > 100)
		draw_map(game->map, game);
}
