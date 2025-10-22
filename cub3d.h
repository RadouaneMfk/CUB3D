/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:43:57 by haboucha          #+#    #+#             */
/*   Updated: 2025/10/22 12:32:05 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <limits.h>
#include "./get_next_line/get_next_line.h"


typedef struct s_game
{
    
    char **map;
    char *path_no;
    char *path_so;
    char *path_we;
    char *path_ea;
    int floor_color;
    int ceiling_color;
    char player_dir;
    
    
}   t_game;
 

char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
size_t	ft_strlen(const char *s);



#endif