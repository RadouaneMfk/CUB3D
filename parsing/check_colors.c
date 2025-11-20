
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

void store_path_color(t_game *game)
{
    int i = 0;
    char *line = NULL;
    char **split_color = NULL;
    while(game->map[i])
    {
        line = skip_spaces(game->map[i]);
        if(ft_strncmp(line,"F ",2) == 0)
        {
            game->flag_F++;
            split_color = ft_split(ft_strchr(line,' '),',');
            if(count_commas(line) != 2 )
            {
                free_split(split_color); 
                exit (1);    
            }
            game->color_floor = split_color;
        }
        else if(ft_strncmp(line,"C ",2) == 0)
        {
            game->flag_C++;
            split_color = ft_split(ft_strchr(line,' '),',');
            if(count_commas(line) != 2)
            {
                free_split(split_color); 
                exit (1);
            }
            game->color_ceiling = split_color;
        }
        i++;
    }
}
int color_floor(t_game * game)
{
    int i;
    i = 0;
    while(game->color_floor[i])
    {
        game->color_floor[i] = trim_spaces(game->color_floor[i]);
        if(!check_types(game->color_floor[i]))
            return 0;
        
        i++;
    }
     i = 0;
    while(game->color_ceiling[i])
    {
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
        if(!check_types(game->color_ceiling[i]))
            return 0;
        i++;
    }
    i = 0;
    while(game->color_ceiling[i])
    {
        game->C_r = ft_atoi(game->color_ceiling[i]);
        game->C_g  = ft_atoi(game->color_ceiling[++i]);
        game->C_b  = ft_atoi(game->color_ceiling[++i]);
        i++;
    }
    if((game->C_r >= 0 && game->C_g  >= 0 && game->C_b  >=0) && (game->C_r  <= 255 && game->C_g <= 255 && game->C_b<= 255))    
        game->ceiling_color = (game->C_r << 16) + (game->C_g<< 8) + game->C_b;
    else
        return 0;
    return 1;
}


void parse_color_line(t_game *game)
{  
    store_path_color(game);
    if(game->flag_F != 1|| game->flag_C != 1)
    {
        write(2,"--fixe RGB colors\n",19);
        free(game->path_ea);
        free(game->path_no);
        free(game->path_so);
        free(game->path_we);
        free_split(game->map);
        free(game);
        exit(0);
    }
    else if(count_number(game->color_floor) != 3 || count_number(game->color_ceiling) != 3)
    {
        write(2,"you use must three number\n",27);
        exit(1);
    }
    else if(color_floor(game) == 0)
    {
        write(2,"--fixe color floor\n",20);
        exit(1);
    }
    else if(color_ceiling(game) == 0)
    {
       
        write(2,"fixe color ceiling\n",20);
        exit(1);
    }
}
