/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 09:34:23 by rmouafik          #+#    #+#             */
/*   Updated: 2025/11/01 11:30:47 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <sys/time.h>
# include "MLX42/include/MLX42/MLX42.h"
# include "../lib/libft.h"

#define WIDTH 1080
#define HEIGHT 720
#define TILE_SIZE 64
#define PLAYER_SIZE 16

typedef struct s_player
{
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	double rotate_Angle;
	double move_speed;
} t_player;

typedef struct s_cube
{
	mlx_t *mlx;
	mlx_image_t *img;
	t_player *player;
	char **map;
} t_cube;



#endif
