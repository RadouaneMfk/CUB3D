

#include "../includes/cub3d.h"

int check_extension(char *file,char *ext)
{
    int position = ft_strlen(file) - ft_strlen(ext);
    if(ft_strlen(file) < ft_strlen(ext))
        return 0;
    if(ft_strcmp(file + position,ext) != 0)
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
    while(str[i] && ft_isspace(str[i]))
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

int check_element(t_game *game)
{
    int i = 0;
    int count = 0;
    while (game->map[i])
    {
        char *line = skip_spaces(game->map[i]);
        if (*line == '\0') { i++; continue; }

        if ((ft_strncmp(line, "NO ", 3) == 0) ||
            (ft_strncmp(line, "SO ", 3) == 0) ||
            (ft_strncmp(line, "EA ", 3) == 0) ||
            (ft_strncmp(line, "WE ", 3) == 0) ||
            (ft_strncmp(line, "F ", 2)  == 0) ||
            (ft_strncmp(line, "C ", 2)  == 0))
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


char *trim_spaces(char *str)
{
    int start = 0;
    int end = ft_strlen(str) - 1;
    while(str [start] && ft_isspace(str[start]))
        start++;
    while(end >= start && ft_isspace(str[end]))
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

int find_start_of_map(t_game *game)
{
    int i = 0;
    while (game->map[i])
    {
        char *line = skip_spaces(game->map[i]);
        if (*line == '\0') { i++; continue; }

        if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 ||
            ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0 ||
            ft_strncmp(line, "F ", 2) == 0  || ft_strncmp(line, "C ", 2) == 0)
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
        write(2,"multiple player in the map!!\n",30);
        exit(1);        
    }
    else if(count_player == 0)
    {
        write(2,"player not found!!\n",20);
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
        j = ft_strlen(map[i]) - 2;
        while( j > 0 && ft_isspace(map[i][j]))
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
        while(ft_isspace (map[i][j]))
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


// int main(int ac,char **av)
// {

// }
