/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 10:39:34 by rmouafik          #+#    #+#             */
/*   Updated: 2025/12/20 10:39:35 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	calcule_hit_ditance(t_var *v)
{
	if (v->horzwallhit == 1)
	{
		v->horzhitdistance = ft_distance(v->player_px, v->player_py,
				v->horzwallhit_x, v->horzwallhit_y);
	}
	else
		v->horzhitdistance = 500000;
	if (v->vertwallhit == 1)
	{
		v->verthitdistance = ft_distance(v->player_px, v->player_py,
				v->vertwallhit_x, v->vertwallhit_y);
	}
	else
		v->verthitdistance = 500000;
}
