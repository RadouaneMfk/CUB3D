/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 10:40:36 by rmouafik          #+#    #+#             */
/*   Updated: 2025/12/20 10:40:37 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_texture(t_cube *cube, t_texture *tex)
{
	if (tex->img)
	{
		mlx_delete_image(cube->mlx, tex->img);
		tex->img = NULL;
	}
}

void	free_all_textures(t_cube *cube)
{
	free_texture(cube, &cube->textures.no);
	free_texture(cube, &cube->textures.so);
	free_texture(cube, &cube->textures.we);
	free_texture(cube, &cube->textures.ea);
}
