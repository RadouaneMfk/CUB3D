/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 10:39:01 by rmouafik          #+#    #+#             */
/*   Updated: 2025/12/21 13:02:56 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	clean_up(t_game *game)
{
	if (game->path_no)
		free(game->path_no);
	if (game->path_so)
		free(game->path_so);
	if (game->path_ea)
		free(game->path_ea);
	if (game->path_we)
		free(game->path_we);
	if (game->color_ceiling)
		free_split(game->color_ceiling);
	if (game->color_floor)
		free_split(game->color_floor);
	if (game)
		free(game);
}
