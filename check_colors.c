/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:33:13 by haboucha          #+#    #+#             */
/*   Updated: 2025/10/29 17:43:03 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int check_types(char *file)
{
    int i = 0;
    while(ft_isspace(file[i]))
        i++;
    if(file[i] == '\0')
        return 0;
    while (file[i])
    {
        if(!ft_isdigit(file[i]))
            return 0;
        i++;
    }
    return 1;
}

int store_path_color(t_game *game)
{
    int i = 0;
    char *line = NULL;
    while(game->map[i])
    {
        line = skip_spaces(game->map[i]);
        if(ft_strncmp(line,"F ",2) == 0)
        {
            if(count_commas(line) != 2 )
                return (0);    
            game->color_floor = ft_split(ft_strchr(line,' '),',');
            game->flag_F++;
        }
        else if(ft_strncmp(line,"C ",2) == 0)
        {
            if(count_commas(line) != 2)
                return (0);
            game->color_ceiling = ft_split(ft_strchr(line,' '), ',');
            game->flag_C++;
        }
        i++;
    }
    if(game->flag_F != 1|| game->flag_C != 1)
        return(write(2,"Duplicate color definition!!\n",30),0);
    if(count_number(game->color_floor) != 3 || count_number(game->color_ceiling) != 3)
       return(write(2,"you use must three number\n",27),0);
    free(line);
    return 1;
}


int color_floor(t_game * game)
{
    int i;
    i = 0;
    while(game->color_floor[i])
    {
        game->color_floor[i] = trim_spaces(game->color_floor[i]);
        if(check_types(game->color_floor[i])== 0)
            return 0;
        game->F_r = ft_atoi(game->color_floor[i]);
        game->F_g = ft_atoi(game->color_floor[++i]);
        game->F_b = ft_atoi(game->color_floor[++i]);
        i++;
    }
    if((game->F_r >= 0 && game->F_g >= 0 && game->F_b >=0) && (game->F_r <= 255 && game->F_g <= 255 && game->F_b <= 255)  )    
            game->floor_color = (game->F_r << 16) + (game->F_g  << 8) + game->F_b;
    else
        return 0;
    return 1;
}

int color_ceiling(t_game *game)
{
    int i;
    i = 0;
    while(game->color_ceiling[i])
    {
        game->color_ceiling[i] = trim_spaces(game->color_ceiling[i]);
        if(check_types(game->color_ceiling[i]) == 0)
            return 0;
        game->C_r = ft_atoi(game->color_ceiling[i]);
        game->C_g  = ft_atoi(game->color_ceiling[++i]);
        game->C_b  = ft_atoi(game->color_ceiling[++i]);
        i++;
    }
    if((game->C_r >= 0 && game->C_g  >= 0 && game->C_b  >=0) && (game->C_r  <= 255 && game->C_g <= 255 && game->C_b<= 255)  )    
        game->ceiling_color = (game->C_r << 16) + (game->C_g<< 8) + game->C_b;
    else
        return 0;
    return 1;
}


void parse_color_line(t_game *game)
{  
    if(store_path_color(game) == 0)
    {
        write(2,"fixe RGB colors\n",17);
        free(game);
        exit(1);
    }
    if(color_floor(game) == 0)
    {
        write(2,"--fixe color floor\n",18);
        exit(1);
    }
    if(color_ceiling(game) == 0)
    {
        write(2,"fixe color ceiling\n",20);
        exit(1);
    }
}
