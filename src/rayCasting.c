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

int main(int ac, char *av[])
{
    t_cube game;
	t_game *cube;

	// char *test_map[] =
	// {
    // 	"11111111111111111",
    // 	"10000000000000001",
    // 	"10111111000000001",
    // 	"10010001001000001",
    // 	"10010001N110 00001",
    // 	"10 000001000000000111",
    // 	"101100000 00000001",
    // 	"1011000 0000000001",
    // 	"10110000000000001",
    // 	"10001110110000001",
	// 	"11111111111111111",
	// 	NULL,
	// };
	if(ac != 2)
        return 1;
    cube = NULL;
    cube = malloc(sizeof(t_game));
    // atexit(ll);
    if(!cube)
        return 1;
    char **new_map = NULL;
    if (check_extension(av[1],".cub") == 0)
    {
        write(2,"extension is not correcte!!\n",28);
        exit(1);
    }
    initisalitaion(cube);
    cube->map = read_map(cube,av[1]);
    parse_texture_line(cube);
    parse_color_line(cube);

        // printf("SO: %s\n",game->path_so);
        // printf("NO: %s\n",game->path_no);
        // printf("WE: %s\n",game->path_we);
        // printf("EA: %s\n",game->path_ea);
       
        if(check_element(cube) == 0)
        {
            write(2,"element no vlaid in map\n",25);
            exit(1);
        }
        int start = find_start_of_map(cube);
        int count_new_map = count_line(cube->map,start);
        if(start == -1)
        {
            write(2,"map invalide!!!\n",17);
            exit(1);
        }
        new_map = malloc(sizeof(char *) * (count_new_map + 1));
        int begin = 0;
        while(cube->map[start])
        {
            new_map[begin] = ft_strdup1(cube->map[start]);
            start++;
            begin++;
        }
        // printf("-->%p\n",(void *)&new_map[begin]);
        new_map[begin] = NULL;
        free_split(cube->map);
        cube->map = new_map;
        if(element_valid(new_map) == 0)
        {
            write(2,"element no valid in map !!\n",28);
            exit(1);    
        }
        cube->player_dir = check_palyer(new_map);
        if(valid_walls(new_map) == 0)
        {
            write(2,"check valadition map!!\n",24);
            exit(1);
        }
        if(check_first_char(new_map) == 0)
        {
            write(2,"fixe first char\n",17);
            exit(1);
        }
        if(check_last_char(new_map) == 0)
        {
            write(2,"fixe last char\n",16);
            exit(1);
        }
        if(valid_map(cube) == 0)
        {
            write(2,"le map invalid!!\n",18);
            exit(1);
        }

        // free_split(new_map);

        printf("----->test\n");
        free_split(cube->color_ceiling);
        free_split(cube->color_floor);
        free(cube->path_ea);
        free(cube->path_we);
        free(cube->path_so);
        free(cube->path_no);
        free(cube);
	
	game.map = cube->map;
	game.player = malloc(sizeof(t_player));
	if (!game.player)
		return 1;
    game.mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true);
    game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
    mlx_image_to_window(game.mlx , game.img, 0, 0);
	init_player(game.map, &game);
	draw_map(game.map, &game);
	mlx_loop_hook(game.mlx, update_player, &game);
    mlx_loop(game.mlx);
    return 0;
}
