#include "../includes/cub3d.h"

void	ft_cast_ray(int rayid, double angle, t_cube *game)
{
	t_var	v;

	if (rayid < 0 || rayid >= game->win_w)
		return ;
	init_vars(&v, game);
	find_horizontal_hit(&v, angle, game);
	find_vertical_hit(&v, angle, game);
	select_hit(&v);
	compute_projection(&v, rayid, game, angle);
}

void	cast_rays(t_cube *game)
{
	int		num_rays;
	double	ray_increment;
	double	ray_angle;
	int		rayid;

	num_rays = game->win_w;
	ray_increment = FOV / num_rays;
	ray_angle = game->player->rotate_angle - (FOV / 2);
	rayid = 0;
	while (rayid < num_rays)
	{
		if (ray_angle < 0)
			ray_angle += 2 * M_PI;
		if (ray_angle > 2 * M_PI)
			ray_angle -= 2 * M_PI;
		ft_cast_ray(rayid, ray_angle, game);
		ray_angle += ray_increment;
		rayid++;
	}
}
