/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:44:55 by haboucha          #+#    #+#             */
/*   Updated: 2025/10/22 09:49:20 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_extension(char *file)
{
    if(strlen(file) < 5  ||  file[strlen(file) - 1] != 'b' || file[strlen(file) - 2] != 'u' ||
        file[strlen(file) - 3] != 'c'|| file[strlen(file) - 4] != '.' )
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
    // printf("count line= %d\n", i);
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

void free_split(char **file)
{
    int i = 0;
    while(file[i])
    {
        free(file[i]);
        i++;
    }
    free(file);
}

char  *texture_no_space(char *path)
{
    int start = 0;
    int end = 0;
    while(isspace(path[start]))
        start++;
    end = strlen(path) - 1;
    while(path[end] && end >= 0)
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
    // int fd_so = open("./textures/south.xpm",O_RDONLY);
    // if(fd_so == -1)
    //     return(0);
    // int fd_we = open("./textures/west.xpm",O_RDONLY);
    // if(fd_we == -1)
    //     return(0);
    // int fd_ea = open("./textures/eastt.xpm",O_RDONLY);
    // if(fd_ea == -1)
    //     return(0);
    // return (close(fd_no),close(fd_so),close(fd_we),close(fd_ea),1);
    return(close(fd_no),1);
}
void parse_texture_line(char **file)
{
    int i =0;
    int flag_no = 0;
    int flag_so = 0;
    int flag_we = 0;
    int flag_ea = 0;

    char *path_no = NULL;
    char *path_so = NULL;
    char *path_we = NULL;
    char *path_ea = NULL;
    
    while(file[i])
    {
        if(strncmp(file[i],"NO ",3) == 0)
        {
            flag_no++;
            path_no =strchr(file[i],'.');

        }
        else if(strncmp(file[i],"SO ",3) == 0)
        {
            flag_so++;
            path_so = strchr(file[i],'.');
        }
        else if(strncmp(file[i],"WE ",3) == 0)
        {
            flag_we++;
            path_we = strchr(file[i],'.');
        }
        else if(strncmp(file[i],"EA ",3) == 0)
        {
            flag_ea++;
            path_ea = strchr(file[i],'.');
        }
        i++;
    }
    if(flag_no != 1 || flag_so != 1 || flag_we != 1 || flag_ea != 1)
    {
        printf("duplicate erreur!!!\n");
        exit(1);
    }
    if(!path_no  || !path_so || !path_we || !path_ea)
    {
        printf("erreur\n");
        exit(1);
    }
    // printf("avant---->%lu\n",strlen(path_no));
    path_no = texture_no_space(path_no);
    // printf("apres---->%lu\n",strlen(path_no));
    path_so = texture_no_space(path_so);
    path_we = texture_no_space(path_we);
    path_ea = texture_no_space(path_ea);
    if(!check_path_exist())
    {
        printf("--->Textures file not found\n");
        exit(1);
    }
    // printf("---->%s\n",path_no);
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

void parse_color_line(char **file)
{
    int i = 0;
    
    char **F = NULL;
    char **C = NULL;
    
    int C_r = 0;
    int C_g = 0;
    int C_b = 0;

    int F_r = 0;
    int F_g = 0;
    int F_b = 0;

    int C_color = 0;
    int F_color = 0;

    int flag_F = 0;
    int flag_C =0;
    
    while(file[i])
    {
        if(strncmp(file[i],"F ",2) == 0)
        {
            F = ft_split(strchr(file[i],' '),',');
            flag_F++;
        }
        else if(strncmp(file[i],"C ",2) == 0)
        {
            C = ft_split(strchr(file[i],' '),',');
            flag_C++;
        }
        i++;
    }
    if(flag_F != 1|| flag_C != 1)
    {
        printf("Duplicate color definition!!\n");
        exit(1);
    }
    if(count_number(F) != 3 || count_number(C) != 3)
    {
        printf("erreur\n");
        exit(1);
    }
    if(F)
    {
        i = 0;
        int j = 0;
        while(isspace(F[i][j]))
            j++;
        F_r = atoi(F[i++]);
        F_g = atoi(F[i++]);
        F_b = atoi(F[i]);
        if((F_r >= 0 && F_g >= 0 && F_b >=0) && (F_r <= 255 && F_g <= 255 && F_b <= 255)  )    
            F_color = (F_r << 16) + (F_g << 8) + F_b;
        else
        {
            printf("erreur\n");
            free_split(F);
            exit(1);    
        }
    }
    if(C)
    {
        i = 0;
        int j = 0;
        while(isspace(F[i][j]))
            j++;
        C_r = atoi(C[i++]);
        C_g = atoi(C[i++]);
        C_b = atoi(C[i]);
        if((C_r >= 0 && C_g >= 0 && C_b >=0) && (C_r <= 255 && C_g <= 255 && C_b <= 255)  )    
            C_color = (C_r << 16) + (C_g << 8) + C_b;
        else
        {
            printf("erreur\n");
            free_split(C);
            exit(1);    
       }    
    }
    free_split(F);
    free_split(C);
}

int find_start_of_map(char **file)
{
    int i = 0;
    while(file[i])
    {
        int j = 0;
        while(file[i][j] && isspace(file[i][j]))
            j++;
        if(file[i][j] == '\0')
        {
            i++;
            continue;
        }
        if(strncmp(file[i],"NO ",3) == 0 || strncmp(file[i],"SO ",3) == 0 ||
            strncmp(file[i],"WE ",3) == 0 || strncmp(file[i],"EA ",3) == 0 ||  
            strncmp(file[i],"F ",2) == 0 || strncmp(file[i],"C ",2) == 0) 
            {
                i++;
                continue;
            }
        int start = 1;
        j =0;
        while(file[i][j])
        {
            if(file[i][j] != ' ' && file[i][j] != '0'  && file[i][j] != '1' &&
            file[i][j] != 'S' &&  file[i][j] != 'N' && file[i][j] != 'W' && file[i][j] != 'E'  && file[i][j] != '\n'  )
            {
                start = 0;
                break;
            }
        j++;   
        }
        if(start)
            return(i);
        i++;
    }
    return (-1);
}
int count_line(char **map,int i)
{
    int count = 0;
    while(map[i])
    {
        i++;
        count++;
    }
    return(count);
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
            if(map[i][j] == 'W' || map[i][j] == 'A' || map[i][j] == 'S'
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
        while(isspace(map[i][j]))
            j--;
        if(map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
            return 0;
        i++;
    }  
    return 1;
}

int valid_map(char **map)
{
    int i = 0;
    int j;
    while(map[i])
    {
        j= 0;
        while(map[i][j])
        {
            if(map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
                || map[i][j] == 'W')
                {
                    if(j  > 0 && map[i][j-1] == ' ')
                        return 0;
                    if(map[i][j+1] == ' ')
                        return 0;
                    if(map[i+1] != NULL && map[i+1][j] == ' ' )
                        return 0;
                    if( i > 0  && map[i - 1] != NULL && map[i - 1][j] == ' ')
                        return 0;
                }
            j++;
        }
        i++;
    }
    return 1;
}
int main(int ac,char **av)
{
    char **map = NULL;
    char **new_map = NULL;
    int count;
    if(ac == 2)
    {
        if(!check_extension(av[1]))
        {
            write(2,"extension is not correcte!!\n",28);
            exit(1);
        }
        int fd = open(av[1],O_RDONLY);
        count = number_line(av[1]);
        map = malloc(sizeof(char *) * (count + 1));
        int i = 0;
        char *line;
        while((line = get_next_line(fd)) != NULL)
        {
            map[i] = line;
            i++;
        }
        map[i] = NULL;
        parse_texture_line(map);
        parse_color_line(map);
        int start = find_start_of_map(map);
        int count_new_map = count_line(map,start);
        if(start == -1)
        {
            printf("map invalide!!!\n");
            exit(1);
        }
        // else
        // {
        //     // printf("---->%d\n",start);
        // }
        new_map = malloc(sizeof(char *) * (count_new_map + 1));
        int begin = 0;
        while(map[start])
        {
            new_map[begin] = strdup(map[start]);
            start++;
            begin++;
        }
        new_map[begin] = NULL;
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
        if(valid_map(new_map) == 0)
        {
            printf("le map invalid!!\n");
            exit(1);
        }
        print_map(new_map);
        close(fd);
        free(map);
        return 0;
    }
    return 1;
}
