/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:38:29 by haboucha          #+#    #+#             */
/*   Updated: 2025/10/30 10:30:28 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


char  *texture_no_space(char *path)
{
    int start = 0;
    int end = 0;
    while(ft_isspace(path[start]))
        start++;
    end = ft_strlen(path) - 1;
    while(end >= 0 && path[end])
    {
        if(ft_atoi(&path[end]))
            path[end]='\0';
        end--;
    }
    return(path + start);
}

int check_path_exist()
{
    int fd_no = open("./textures/north.xpm",O_RDONLY);
    if(fd_no == -1)
        return(0);
    int fd_so = open("./textures/south.xpm",O_RDONLY);
    if(fd_so == -1)
        return(0);
    int fd_we = open("./textures/west.xpm",O_RDONLY);
    if(fd_we == -1)
        return(0);
    int fd_ea = open("./textures/east.xpm",O_RDONLY);
    if(fd_ea == -1)
        return(0);
    return (close(fd_no),close(fd_so),close(fd_we),close(fd_ea),1);
}

int initialtion_path(t_game *game)
{
    game->path_no = texture_no_space(game->path_no);
    if(check_extension(game->path_no,".xpm") == 0)
        return(0);
    game->path_so = texture_no_space(game->path_so);
    if(check_extension(game->path_so,".xpm") == 0)
        return(0);
    game->path_we = texture_no_space(game->path_we);
    if(check_extension(game->path_we,".xpm") == 0)
        return(0);
    game->path_ea = texture_no_space(game->path_ea);
    if(check_extension(game->path_ea,".xpm") == 0)
        return(0);
    return 1;
}

int store_path(t_game *game)
{
    int i = 0;
    char **split = NULL;
    char *line;
    while(game->map[i])
    {
        line = skip_spaces(game->map[i]);
        if(ft_strncmp(line,"NO ",3) == 0)
        {

            game->flag_no++;
            line = trim_spaces(line);
            split =  ft_split(line,' ');
            if(count_line(split,0) != 2)
            {
                free_split(split);
                write(2,"invalid path NO",16);
                exit(1);
            }
            game->path_no = ft_strdup(trim_spaces(split[1]));
            free_split(split);
            split = NULL;
        }
        else if(ft_strncmp(line,"SO ",3) == 0)
        {
            game->flag_so++;
            line = trim_spaces(line);
            split =  ft_split(line,' ');
            if(count_line(split,0) != 2)
            {
                free_split(split);
                write(2,"invalid path SO\n",17);
                exit(1);
            }
            game->path_so = ft_strdup(trim_spaces(split[1]));
            free_split(split);
            split = NULL;
        }
        else if(ft_strncmp(line,"EA ",3) == 0)
        {
            game->flag_ea++;
            line = trim_spaces(line);
            split =  ft_split(line,' ');
            if(count_line(split,0) != 2)
            {
                free_split(split);
                write(2,"invalid path EA\n",17);
                exit(1);
            }
            game->path_ea = ft_strdup(trim_spaces(split[1]));
            free_split(split);
            split = NULL;
        }
        else if(ft_strncmp(line,"WE ",3) == 0)
        {
            game->flag_we++;
            line = trim_spaces(line);
            split =  ft_split(line,' ');
            if(count_line(split,0) != 2)
            {
                 free_split(split);
                write(2,"invalid path WE\n",17);
                exit(1);
            }
            game->path_we = ft_strdup(trim_spaces(split[1]));
            free_split(split);
            split = NULL;
        }
        i++;
    }
    return 1;
}

void parse_texture_line(t_game *game)
{
    store_path(game);
    if(!game->path_no  || !game->path_so || !game->path_we || !game->path_ea)
    {
        free(game->path_ea);
        free(game->path_we);
        free(game->path_so);
        free(game->path_no);
        free_split(game->map);
        free(game);
        write(2,"erreur not found path\n",23);
        exit(1);
        
    }
    if(game->flag_no != 1 || game->flag_ea != 1 || game->flag_we != 1 || game->flag_so != 1)
    {
        free(game->path_ea);
        free(game->path_we);
        free(game->path_so);
        free(game->path_no);
        free_split(game->map);
        free(game);
        write(2,"duplicate path erreur!!!\n",26);
        exit(1);
    }
    if(initialtion_path(game) == 0)
    {
        free(game->path_ea);
        free(game->path_we);
        free(game->path_so);
        free(game->path_no);
        free_split(game->map);
        free(game);
        write(2,"path not exist\n",16);
        exit(1);
    }
    if(check_path_exist() == 0)
    {
        free(game->path_ea);
        free(game->path_we);
        free(game->path_so);
        free(game->path_no);
        free_split(game->map);
        free(game);
        write(2,"path not found\n",16);
        exit(1);  
        
    }
}
