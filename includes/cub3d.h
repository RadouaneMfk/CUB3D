/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 10:42:05 by rmouafik          #+#    #+#             */
/*   Updated: 2025/12/20 11:20:46 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft.h"
# include "../parsing/get_next_line/get_next_line.h"
# include "../../MLX42/include/MLX42/MLX42.h"
# include <ctype.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define MINIMAP_SCALE 0.2
# define MIN_W 100
# define MIN_H 100
# define TILE_SIZE 64
# define PLAYER_SIZE 20
# define FOV 1.0471975512
# define MINIMAP_TILE_SIZE 10
# define VERTICAL 0
# define HORIZONTAL 1
# define WIDTH 1080
# define HEIGHT 720

typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	double			rotate_angle;
	double			move_speed;
	int				prev_mouse_x;
	bool			mouse_lock;
	int				cursor_x;
	int				cursor_y;
}					t_player;

typedef struct s_texture
{
	char			*path;
	mlx_texture_t	*tex;
	mlx_image_t		*img;
	int				width;
	int				height;
	uint8_t			r;
	uint8_t			g_col;
	uint8_t			b;
	uint8_t			a;
	uint32_t		color;
	uint8_t			*pixels;
	int				texx;
	int				texy;
	int				index;
	double			step;
	double			texpos;
	int				y;
}					t_texture;

typedef struct s_textures
{
	t_texture		no;
	t_texture		so;
	t_texture		we;
	t_texture		ea;
}					t_textures;

typedef struct s_game
{
	char			**map;
	char			*path_no;
	char			*path_so;
	char			*path_we;
	char			*path_ea;
	int				floor_color;
	int				ceiling_color;
	char			player_dir;
	char			**color_floor;
	char			**color_ceiling;
	int				flag_f;
	int				flag_c;
	int				flag_no;
	int				flag_so;
	int				flag_we;
	int				flag_ea;
	int				c_r;
	int				c_g;
	int				c_b;
	int				f_r;
	int				f_g;
	int				f_b;
	char			**new_map;
}					t_game;

typedef struct s_cube
{
	t_game			*cube;
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_player		*player;
	t_textures		textures;
	char			**map;
	int				win_w;
	int				win_h;
}					t_cube;

typedef struct s_var
{
	int				side_hit;
	double			x_intercept;
	double			y_intercept;
	double			x_step;
	double			y_step;
	double			nexthorz_x;
	double			nexthorz_y;
	double			nextvert_x;
	double			nextvert_y;
	double			horzwallhit_x;
	double			horzwallhit_y;
	double			vertwallhit_x;
	double			vertwallhit_y;
	double			horzhitdistance;
	double			verthitdistance;
	double			wallhitx;
	double			wallhity;
	double			player_px;
	double			player_py;
	int				horzwallhit;
	int				vertwallhit;
	int				map_x;
	int				map_y;
	double			distanceprojectionplane;
	double			wallstripheight;
	double			top;
	double			bottom;
	double			raydistance;
	double			ray_angle;
	int				ceil_size;
	double			hit_offset;
	int				flag;
	int				map_height;
	int				map_width;
	int				i;
	int				x;
	int				y;
	int				visible;
	int				player_x;
	int				player_y;
	int				start_x;
	int				start_y;
	int				end_x;
	int				end_y;
	int				minimap_x;
	int				minimap_y;
	double			next_posx;
	double			next_posy;
	double			move_speed;
	double			radius;
	double			walk;
	int				center_x;
	int				center_y;
	double			delta;
}					t_var;

void				cast_rays(t_cube *game);
void				draw_square(t_var *var, int size, int color, t_cube *game);
double				ft_distance(double x1, double y1, double x2, double y2);
void				update_player(void *param);
void				init_player(char **map, t_cube *cube);
void				draw_map(char **map, t_cube *game);
void				init_vars(t_var *v, t_cube *game);
void				find_horizontal_hit(t_var *v, double a, t_cube *g);
void				find_vertical_hit(t_var *v, double a, t_cube *g);
void				select_hit(t_var *v);
void				compute_projection(t_var *v, int rayid, t_cube *g,
						double ray_angle);
void				ft_cast_ray(int rayid, double angle, t_cube *game);
void				init_vars(t_var *v, t_cube *game);
void				check_horizontal_intercept(t_var *v, double a);
void				find_horizontal_hit(t_var *v, double a, t_cube *g);
void				check_vertical_intercept(t_var *v, double a);
void				find_vertical_hit(t_var *v, double a, t_cube *g);
void				calcule_hit_ditance(t_var *v);
void				init_player(char **map, t_cube *cube);
void				ft_cast_ray(int rayid, double angle, t_cube *game);
void				cast_rays(t_cube *game);
void				ft_resize(int width, int height, void *param);

// parsing

void				parsing_checks(t_cube game, char **str);
void				parsing_checks2(t_cube game, t_game *cube);
char				**ft_split(char const *s, char c);
size_t				ft_strlen(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_isspace(int c);
int					ft_atoi(const char *str);
int					ft_isdigit(int c);
int					ft_strcmp(char *s1, char *s2);
char				*trim_spaces(char *str);
int					parse_color_line(t_game *game);
int					count_number(char **file);
int					count_commas(char *file);
char				*skip_spaces(char *str);
int					count_line(char **map, int i);
int					check_extension(char *file, char *ext);
int					parse_texture_line(t_game *game);
void				free_split(char **file);
int					check_extension(char *file, char *ext);
int					number_line(char *line);
char				*skip_spaces(char *str);
void				free_split(char **file);
int					check_element(t_game *game);
char				*trim_spaces(char *str);
int					count_line(char **map, int i);
int					count_number(char **file);
int					count_commas(char *file);
int					find_start_of_map(t_game *game);
int					element_valid(char **file);
char				check_palyer(char **map);
int					check_first_line(char **map);
int					check_last_line(char **map);
int					valid_walls(char **map);
int					check_first_char(char **map);
int					check_last_char(char **map);
int					empty_line(char **map);
int					valid_map(t_game *game);
void				initisalitaion(t_game *game);
char				**read_map(t_game *game, char *av);
char				*texture_no_space(char *path);
int					store_path_no(t_game *game, char *line);
int					store_path_so(t_game *game, char *line);
int					store_path_ea(t_game *game, char *line);
int					store_path_we(t_game *game, char *line);
int					store_color_floor(t_game *game, char *line);
int					store_color_ceiling(t_game *game, char *line);
int					store_path_color(t_game *game);
int					check_element_valid_in_map(char *line);
int					check_element_start_map(char *line);
void				aide_player(char **map, int *count, char *player);
int					aide_map(t_game *game, int i, int j);
int					valid_map(t_game *game);
int					check_start_map(char *line);
void				free_all_textures(t_cube *cube);
void				free_texture(t_cube *cube, t_texture *tex);
void				clean_up(t_game *game);

/******textures*/
int					init_textures(t_cube *cube, t_game *game);
void				draw_textured_wall(int rayid, t_var *v, t_cube *g,
						double ray_angle);
#endif