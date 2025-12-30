/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 13:10:52 by haboucha          #+#    #+#             */
/*   Updated: 2025/12/21 13:12:56 by haboucha         ###   ########.fr       */
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
