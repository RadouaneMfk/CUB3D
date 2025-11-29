#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <sys/time.h>
# include "../lib/libft.h"
# include "MLX42/MLX42.h"

#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "../parsing/get_next_line/get_next_line.h"


#define MINIMAP_SCALE 0.2  // 20% de la taille originale
// #define PLAYER_SIZE 4      // taille du point joueur sur la mini-map
#define WIDTH 1080
#define HEIGHT 720
#define TILE_SIZE 64
#define PLAYER_SIZE 20
#define FOV M_PI / 3
#define MINIMAP_TILE_SIZE 10
#define VERTICAL 0
#define HORIZONTAL 1

typedef struct s_player
{
	double pos_x;
	double pos_y;
	double rotate_Angle;
	double move_speed;
	int prev_mouse_x;
	bool mouse_lock;
	int cursor_x;
	int cursor_y;
} t_player;

typedef struct s_textures
{
	mlx_image_t *tex_no_img;
	mlx_image_t *tex_so_img;
	mlx_image_t *tex_we_img;
	mlx_image_t *tex_ea_img;


	mlx_texture_t *tex_no;
	mlx_texture_t *tex_so;
	mlx_texture_t *tex_we;
	mlx_texture_t *tex_ea;
}t_textures;

typedef struct s_cube
{
	mlx_t *mlx;
	mlx_image_t *img;
	t_player *player;
	mlx_texture_t *current_texture;
	t_textures textures;
	int pixel_index;
	double tex_x;
	double tex_y;
	char **map;
} t_cube;





typedef struct s_var
{
	int side_hit;
	double x_intercept;
	double y_intercept;
	double x_step;
	double y_step;
	double nextHorz_x;
	double nextHorz_y;
	double nextVert_x;
	double nextVert_y;
	double HorzWallHit_x;
	double HorzWallHit_y;
	double VertWallHit_x;
	double VertWallHit_y;
	double HorzHitDistance;
	double VertHitDistance;
	double WallHitX;
	double WallHitY;
	double player_px;
	double player_py;
	int HorzWallHit;
	int VertWallHit;
	int map_height;
	int map_width;
	int map_x;
	int map_y;
	double DistanceProjectionPlane;
	double WallStripHeight;
	double top;
	double bottom;
	double rayDistance;
	double ray_angle;
	int ceil_size;
	double hit_offset;
} t_var;




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
	t_textures textures;
}   t_game;

void	castRays(t_cube *game);
void	draw_line(t_cube *game);
void	draw_square(double x, double y, int size, int color, t_cube *game);
void	ft_draw_line(double x0, double y0, double x1, double y1, int color, t_cube *game);
double	ft_distance(double x1, double y1, double x2, double y2);
void	draw_player(t_cube *game);
void	draw_square_player(double x, double y, int size, int color, t_cube *game);
void	update_player(void *param);
void	init_player(char **map, t_cube *cube);
void	draw_map(char **map, t_cube *game);
void	draw_black_cover(char **map, t_cube *game);
void	init_vars(t_var *v, t_cube *game);
void	find_horizontal_hit(t_var *v, double a, t_cube *g);
void	find_vertical_hit(t_var *v, double a, t_cube *g);
void	select_hit(t_var *v);
void	compute_projection(t_var *v, int rayId, t_cube *g, double ray_angle);
void	ft_cast_ray(int rayId, double angle, t_cube *game);

//parsing

int convert_textures_to_img(t_game *game,t_cube *cube);
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
int check_extension(char *file,char *ext);
int number_line(char *line);
void print_map(char **file);
char *skip_spaces(char *str);
void free_split(char **file);
int check_element(t_game *game);
char *trim_spaces(char *str);
int count_line(char **map,int i);
int count_number(char **file);
int count_commas(char *file);
int find_start_of_map(t_game *game);
int element_valid(char **file);
char  check_palyer(char **map);
int check_first_line(char **map);
int check_last_line(char **map);
int valid_walls(char **map);
int check_first_char(char **map);
int check_last_char(char **map);
int empty_line(char **map);
int valid_map(t_game *game);
void initisalitaion(t_game *game);
char **read_map(t_game *game,char *av);



/******textures*/
int upload_textures(t_game *game);
int convert_textures_to_img(t_game *game,t_cube *cube);

#endif
