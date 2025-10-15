/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:44:55 by haboucha          #+#    #+#             */
/*   Updated: 2025/10/15 15:02:07 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_extension(char *file)
{
    if(strlen(file) < 5 ||  file[strlen(file) - 1] != 'b' || file[strlen(file) - 2] != 'u' ||
        file[strlen(file) - 3] != 'c'|| file[strlen(file) - 4] != '.' )
        return 0;
    return 1; 
}
int number_line(char *file)
{
    int i  = 0;
    int fd = open(file,O_RDONLY);
    file = get_next_line(fd);
    while(file != NULL)
    {
        file = get_next_line(fd);
        i++;
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

void parse_texture_line(char **file)
{
    int i =0;
    int j=0;
    
    char *path_no = NULL;
    char *path_so = NULL;
    char *path_we = NULL;
    char *path_ea = NULL;
    
    while(file[i])
    {
        if(strncmp(file[i],"NO ",3) == 0)
            path_no =strchr(file[i],'.');
        else if(strncmp(file[i],"SO ",3) == 0)
            path_so = strchr(file[i],'.');
        else if(strncmp(file[i],"WE ",3) == 0)
            path_we = strchr(file[i],'.');
        else if(strncmp(file[i],"EA ",3) == 0)
            path_ea = strchr(file[i],'.');
        i++;
    }
    if(!path_no || !path_so || !path_we || !path_ea)
        printf("erreur\n");
}


int main(int ac,char **av)
{
    char **map = NULL;
    int count;
    char *path_no;
    char *path_so;
    char *path_we;
    char *path_ea;
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
        // print_map(map);
        close(fd);
        free(map);
        return 0;
    }
    return 1;
}