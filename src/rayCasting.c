#include "../includes/cub3d.h"

void	ft_cast_ray(int rayId, double angle, t_cube *game)
{
	t_var	v;

	if (rayId < 0 || rayId >= WIDTH)
		return ;
	init_vars(&v, game);
	find_horizontal_hit(&v, angle, game);
	find_vertical_hit(&v, angle, game);
	select_hit(&v);
	compute_projection(&v, rayId, game, angle);
}

void castRays(t_cube *game)
{
	int start_x = game->player->pos_x * (TILE_SIZE + 1);
	int start_y = game->player->pos_y * (TILE_SIZE + 1);
	int num_rays = WIDTH;
	double ray_increment = FOV / num_rays;
	double ray_angle = game->player->rotate_Angle - (FOV / 2);

	int rayId = 0;
	while (rayId < num_rays)
	{
		if (ray_angle < 0)
			ray_angle += 2 * M_PI;
		if (ray_angle > 2 * M_PI)
			ray_angle -= 2 * M_PI;
		ft_cast_ray(rayId, ray_angle, game);
		ray_angle += ray_increment;
		rayId++;
	}
}

int main()
{
    t_cube game;

	char *test_map[] =
	{
    	"11111111111111111",
    	"10000000000000001",
    	"10111111000000001",
    	"10010001001000001",
    	"10010001N11000001",
    	"10000001000000111",
    	"10110000000000001",
    	"10001110110000001",
		"11111111111111111",
    	NULL
	};
	game.map = test_map;
	game.player = malloc(sizeof(t_player));
	if (!game.player)
		return 1;
    game.mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true);
    game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
    mlx_image_to_window(game.mlx , game.img, 0, 0);
	init_player(test_map, &game);
	draw_map(test_map, &game);
	mlx_loop_hook(game.mlx, update_player, &game);
    mlx_loop(game.mlx);
    return 0;
}
