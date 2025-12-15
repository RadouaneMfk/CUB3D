#include "../includes/cub3d.h"

void	calcule_hit_ditance(t_var *v)
{
	if (v->HorzWallHit == 1)
	{
		v->HorzHitDistance = ft_distance(v->player_px, v->player_py,
				v->HorzWallHit_x, v->HorzWallHit_y);
	}
	else
		v->HorzHitDistance = 500000;
	if (v->VertWallHit == 1)
	{
		v->VertHitDistance = ft_distance(v->player_px, v->player_py,
				v->VertWallHit_x, v->VertWallHit_y);
	}
	else
		v->VertHitDistance = 500000;
}
