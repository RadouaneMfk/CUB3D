#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <sys/time.h>
# include "../lib/libft.h"
# include <MLX42/MLX42.h>

#define WIDTH 1080
#define HEIGHT 720
#define TILE_SIZE 64
#define PLAYER_SIZE 20
#define FOV M_PI / 3
#define MINIMAP_SCALE 0.2
#define MINI_H 200
#define MINI_W 200
#define MINIMAP_TILE_SIZE 10

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

typedef struct s_cube
{
	mlx_t *mlx;
	mlx_image_t *img;
	t_player *player;
	char **map;
} t_cube;

typedef struct s_var
{
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
} t_var;

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
void	castRays(t_cube *game);
void	ft_cast_ray(int rayId, double angle, t_cube *game);
#endif
