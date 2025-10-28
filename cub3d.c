/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:44:55 by haboucha          #+#    #+#             */
/*   Updated: 2025/10/28 18:38:00 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_extension(char *file)
{
    if(strlen(file) < 4 || file[strlen(file) - 1] != 'b' || file[strlen(file) - 2] != 'u' ||
        file[strlen(file) - 3] != 'c'|| file[strlen(file) - 4] != '.')
        return 0;
    return 1; 
}

int check_extension1(char *file,char *ext)
{
    int position = strlen(file) - strlen(ext);
    if(strlen(file) < strlen(ext))
        return 0;
    if(strcmp(file + position,ext) != 0)
        return 0;
    return 1; 
}
int number_line(char *line)
{
    int i  = 0;
    int fd = open(line,O_RDONLY);
    if(fd == -1)
        exit(1);
    line = get_next_line(fd);
    while(line != NULL)
    {
        i++;
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return i;
}

void print_map(char **file)
{
    int i = 0;
    while(file[i])
    {
        printf("%s",file[i]);
        i++;
    }
}

char *skip_spaces(char *str)
{
    int i = 0;
    while(str[i] && isspace(str[i]))
        i++;
    return str + i;
}
void free_split(char **file)
{
    int i = 0;
    while( file[i])
    {
        free(file[i]);
        i++;
    }
    free(file);
}
// int check_element(t_game *game)
// {
//     int i = 0;
//     int count  = 0;
//     int j;
//     while(game->map[i])
//     {
//         j = 0;
//         while(game->map[i][j] && isspace(game->map[i][j]))
//             j++;
//         if(game->map[i][j] == '\0')
//         {
//             i++;
//             continue;
//         }
//         if ((strncmp(game->map[i], "NO ", 3) == 0) ||
//             (strncmp(game->map[i], "SO ", 3) == 0) ||
//             (strncmp(game->map[i], "EA ", 3) == 0) ||
//             (strncmp(game->map[i], "WE ", 3) == 0) ||
//             (strncmp(game->map[i], "F ", 2)  == 0) ||
//             (strncmp(game->map[i], "C ", 2)  == 0))
//         {
//             count++;     
//         }
//         else if(game->map[i][j] == '0' || game->map[i][j] == '1' || 
//                 game->map[i][j] == 'N' || game->map[i][j] == 'S' || game->map[i][j] == 'E' ||
//                 game->map[i][j] == 'W')
//             break;
//         else
//             return 0;
//         i++;
//     }
//     if(count == 6)
//         return 1;
//     return 0;
// }
int check_element(t_game *game)
{
    int i = 0;
    int count = 0;
    while (game->map[i])
    {
        char *line = skip_spaces(game->map[i]);
        if (*line == '\0') { i++; continue; }

        if ((strncmp(line, "NO ", 3) == 0) ||
            (strncmp(line, "SO ", 3) == 0) ||
            (strncmp(line, "EA ", 3) == 0) ||
            (strncmp(line, "WE ", 3) == 0) ||
            (strncmp(line, "F ", 2)  == 0) ||
            (strncmp(line, "C ", 2)  == 0))
        {
            count++;
        }
        else if (line[0] == '0' || line[0] == '1' ||
                 line[0] == 'N' || line[0] == 'S' ||
                 line[0] == 'E' || line[0] == 'W')
        {
            break;
        }
        else
            return 0;
        i++;
    }
    if(count == 6)
        return 1;
    return 0;
}

char  *texture_no_space(char *path)
{
    int start = 0;
    int end = 0;
    while(isspace(path[start]))
        start++;
    end = strlen(path) - 1;
    while(end >= 0 && path[end])
    {
        if(isspace(path[end]))
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
    if(check_extension1(game->path_no,".xpm") == 0)
        return(0);
    game->path_so = texture_no_space(game->path_so);
    if(check_extension1(game->path_so,".xpm") == 0)
        return(0);
    game->path_we = texture_no_space(game->path_we);
    if(check_extension1(game->path_we,".xpm") == 0)
        return(0);
    game->path_ea = texture_no_space(game->path_ea);
    if(check_extension1(game->path_ea,".xpm") == 0)
        return(0);
    return 1;
}

char *trim_spaces(char *str)
{
    int start = 0;
    int end = strlen(str) - 1;
    while(str [start] && isspace(str[start]))
        start++;
    while(end >= start && isspace(str[end]))
        end--;
    int i = 0;
    while(start <= end)
    {
        str[i] = str[start];
        i++;
        start++;
    }
    str[i] = '\0';
    return str;
}
int count_line(char **map,int i)
{
    int count = 0;
    while(map[i])
    {
        count++;
        i++;
    }
    return(count);
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
            // free_split(split);
            // split = NULL;
        }
        else if(ft_strncmp(line,"SO ",3) == 0)
        {
            game->flag_so++;
            line = trim_spaces(line);
            split =  ft_split(line,' ');
            // printf("--->count: %d\n",count_line(split,0));
            // printf("path_so---> %s\n",split[1]);
            if(count_line(split,0) != 2)
            {
                free_split(split);
                write(2,"invalid path SO\n",17);
                exit(1);
            }
            game->path_so = ft_strdup(trim_spaces(split[1]));
            // free_split(split);
            // split = NULL;
        }
        else if(ft_strncmp(line,"EA ",3) == 0)
        {
            game->flag_ea++;
            line = trim_spaces(line);
            split =  ft_split(line,' ');
            if(count_line(split,0) != 2)
            {
                write(2,"invalid path EA\n",17);
                exit(1);
            }
            game->path_ea = ft_strdup(trim_spaces(split[1]));
            // free_split(split);
            // split = NULL;
        }
        else if(ft_strncmp(line,"WE ",3) == 0)
        {
            game->flag_we++;
            line = trim_spaces(line);
            split =  ft_split(line,' ');
            if(count_line(split,0) != 2)
            {
                write(2,"invalid path WE\n",17);
                exit(1);
            }
            game->path_we = ft_strdup(trim_spaces(split[1]));
            // free_split(split);
            // split = NULL;
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
        return(free(game),write(2,"erreur not found path\n",23),exit(1));
    }
    if(game->flag_no != 1 || game->flag_ea != 1 || game->flag_we != 1 || game->flag_so != 1)
    {
        free(game);
        write(2,"duplicate path erreur!!!\n",26);
        exit(1);
    }
    if(initialtion_path(game) == 0)
        return(free(game),write(2,"path not exist\n",16),exit(1));
    if(check_path_exist() == 0)
        return(free(game),write(2,"path not found\n",16),exit(1));
        
}
int count_number(char **file)
{
    int i = 0;
    int count = 0;
    while(file[i])
    {
        count++;
        i++;
    }
    return count;
}
int count_commas(char *file)
{
    int i = 0;
    int count = 0;
    while(file[i])
    {
        if(file[i] == ',')
            count++;
        i++;
    }
    return(count);
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
    return 1;
}
int check_types(char *file)
{
    int i = 0;
    while(isspace(file[i]))
        i++;
    if(file[i] == '\0')
        return 0;
    while (file[i])
    {
        if(!isdigit(file[i]))
            return 0;
        i++;
    }
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
        game->F_g = ft_atoi(game->color_floor[i]);
        game->F_b = ft_atoi(game->color_floor[i]);
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
        game->C_g  = ft_atoi(game->color_ceiling[i]);
        game->C_b  = ft_atoi(game->color_ceiling[i]);
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

int find_start_of_map(t_game *game)
{
    int i = 0;
    while (game->map[i])
    {
        char *line = skip_spaces(game->map[i]);
        if (*line == '\0') { i++; continue; }

        if (strncmp(line, "NO ", 3) == 0 || strncmp(line, "SO ", 3) == 0 ||
            strncmp(line, "WE ", 3) == 0 || strncmp(line, "EA ", 3) == 0 ||
            strncmp(line, "F ", 2) == 0  || strncmp(line, "C ", 2) == 0)
        {
            i++;
            continue;
        }
        int j = 0;
        int find = 1;
        while (line[j])
        {
            if (line[j] != ' ' && line[j] != '0' && line[j] != '1' &&
                line[j] != 'S' && line[j] != 'N' && line[j] != 'W' &&
                line[j] != 'E' && line[j] != '\n')
            {
                find = 0;
                break;
            }
            j++;
        }
        if (find)
             return i;
        i++;
    }
    return -1;
}

int element_valid(char **file)
{
    int i = 0;
    int j;
    while(file[i])
    {
        j = 0;
        while(file[i][j])
        {
            if(file[i][j] != '0'  && file[i][j] != '\n' && file[i][j] != '1' && file[i][j] != ' ' && file[i][j] != 'N' && file[i][j] !='S' && file[i][j] != 'E' && file[i][j] != 'W')
            {
                return 0;
            }
            j++;
        }
        i++;
    }
    return 1;
    
}
char  check_palyer(char **map)
{
    int count_player = 0;
    char player_dir;
    int i =0;
    int j;
    while(map[i])
    {
        j = 0;
        while(map[i][j])
        {
            if(map[i][j] == 'W' || map[i][j] == 'N' || map[i][j] == 'S'
                || map[i][j] == 'E')
                {
                    count_player++;
                    player_dir = map[i][j];
                }
            j++;
        }
        i++;
    }
    if(count_player > 1)
    {
        printf("multiple player in the map!!\n");
        exit(1);        
    }
    else if(count_player == 0)
    {
        printf("player not found!!\n");
        exit(1);
    }
    return(player_dir);    
}

int check_first_line(char **map)
{
    int i = 0;
    while(map[0][i])
    {
        if(map[0][i] == '0' || map[0][i] == 'N' || map[0][i] == 'S' || map[0][i] == 'W' || map[0][i] == 'E')
            return 0;
        i++;
    }
    return 1;
}
int check_last_line(char **map)
{
    int last_line = count_line(map,0);
    last_line = last_line - 1;
    int i = 0;
    while(map[last_line][i])
    {
        if(map[last_line][i] == '0' || map[last_line][i] == 'N' || map[last_line][i] == 'S' 
            || map[last_line][i] == 'W' || map[last_line][i] == 'E')
            return 0;
        i++;
    }
    return 1;
    
}

int valid_walls(char **map)
{
    if(check_first_line(map) ==  0)
        return 0;
    else if(check_last_line(map) == 0)
       return 0;
    return 1;
}
int check_first_char(char **map)
{
    int i = 1;
    int j;
    while(map[i])
    {
        j = 0;
        while(isspace(map[i][j]))
            j++;
        if(map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
            return 0;
        i++;
    }
    return 1;
}
int check_last_char(char **map)
{
    int i = 1;
    int j = 0;
    while(map[i])
    {
        j = strlen(map[i]) - 2;
        while( j > 0 && isspace(map[i][j]))
            j--;
        if(j > 0  && (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W'))
            return 0;
        i++;
    }  
    return 1;
}
int empty_line(char **map)
{
    int i = 0;
    int j;
    while(map[i])
    {
        j = 0;
        while(isspace (map[i][j]))
            j++;
        if(map[i][j] == '\0')
            return 0;  
        i++;
    }
    return 1;
}
int valid_map(t_game *game)
{
    int i = 0;
    int j;
    if(empty_line(game->map) == 0 )
        return 0;
    while(game->map[i])
    {
        j= 0;
        while(game->map[i][j])
        {
            if(game->map[i][j] == '0' || game->map[i][j] == 'N' || game->map[i][j] == 'S' || game->map[i][j] == 'E'
                || game->map[i][j] == 'W')
                {
                    if(j > 0 && game->map[i][j-1] == ' ')
                        return 0;
                    if(game->map[i][j+1] == ' ')
                        return 0;
                    if(game->map[i+1] != NULL && game->map[i+1][j] == ' ' )
                        return 0;
                    if( i > 0  && game->map[i - 1] != NULL && game->map[i - 1][j] == ' ')
                        return 0;
                }
            j++;
        }
        i++;
    }
    return 1;
}
void initisalitaion(t_game *game)
{
    game->map = NULL;
    game->ceiling_color = 0;
    game->floor_color = 0;
    game->path_ea = NULL;
    game->path_no =NULL;
    game->path_we= NULL;
    game->path_so = NULL;
    game->flag_no = 0;
    game->flag_so = 0;
    game->flag_we = 0;
    game->flag_ea = 0;
    game->color_floor = NULL;
    game->color_ceiling = NULL;
    game->flag_C = 0;
    game->flag_F = 0;
}
char **read_map(t_game *game,char *av)
{
    int count = number_line(av);
    int fd = open(av,O_RDONLY);
    game->map = malloc(sizeof(char *) * (count + 1));
    if(!game->map)
        return(free(game),NULL);
    int i = 0;
    char *line;
    while((line = get_next_line(fd)) != NULL)
    {
        game->map[i] = line;
        i++;
    }
    game->map[i] = NULL;
    close(fd);
    return game->map; 
}
int main(int ac,char **av)
{
    t_game *game = NULL;
    game = malloc(sizeof(t_game));
    if(!game)
        return 1;
    char **new_map = NULL;
    if(ac == 2)
    {
        if(check_extension(av[1]) == 0)
        {
            write(2,"extension is not correcte!!\n",28);
            exit(1);
        }
        initisalitaion(game);
        game->map = read_map(game,av[1]);
        parse_texture_line(game);
        parse_color_line(game);
        if(check_element(game) == 0)
        {
            printf("element no vlaid in map\n");
            exit(1);
        }
        int start = find_start_of_map(game);
        int count_new_map = count_line(game->map,start);
        if(start == -1)
        {
            printf("map invalide!!!\n");
            exit(1);
        }
        new_map = malloc(sizeof(char *) * (count_new_map + 1));
        int begin = 0;
        while(game->map[start])
        {
            new_map[begin] = strdup(game->map[start]);
            start++;
            begin++;
        }
        new_map[begin] = NULL;
        game->map = new_map;
        if(element_valid(new_map) == 0)
        {
            printf("element no valid in map !!\n");
            exit(1);    
        }
        char player_dir = check_palyer(new_map);
        printf("--->pos_plyer: %c\n",player_dir);
        if(valid_walls(new_map) == 0)
        {
            printf("check valadition map!!\n");
            exit(1);
        }
        if(check_first_char(new_map) == 0)
        {
            printf("fixe first char\n");
            exit(1);
        }
        if(check_last_char(new_map) == 0)
        {
            printf("fixe last char\n");
            exit(1);
        }
        if(valid_map(game) == 0)
        {
            printf("le map invalid!!\n");
            exit(1);
        }
        print_map(new_map);
        free(game->map);
        return 0;
    }
    return 1;
}
