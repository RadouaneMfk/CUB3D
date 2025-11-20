
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
    char **color_floor;
    char **color_ceiling;
    int flag_F;
    int flag_C;
    int flag_no;
    int flag_so;
    int flag_we;
    int flag_ea;
    int C_r;
    int C_g;
    int C_b;
    int F_r;
    int F_g;
    int F_b;
}   t_game;
 

char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_isspace(int c);
int	ft_atoi(const char *str);
int	ft_isdigit(int c);
int ft_strcmp(char *s1,char *s2);
char *trim_spaces(char *str);
void parse_color_line(t_game *game);
int count_number(char **file);
int count_commas(char *file);
char *skip_spaces(char *str);
int count_line(char **map,int i);
int check_extension(char *file,char *ext);
void parse_texture_line(t_game *game);
void free_split(char **file);


#endif