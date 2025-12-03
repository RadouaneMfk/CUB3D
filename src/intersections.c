#include "../includes/cub3d.h"


void	init_vars(t_var *v, t_cube *game)
{
	v->ceil_size = TILE_SIZE;
	v->HorzWallHit = 0;
	v->VertWallHit = 0;
	v->player_px = game->player->pos_x * v->ceil_size;
	v->player_py = game->player->pos_y * v->ceil_size;
	v->map_height = 0;
	while (game->map[v->map_height])
		v->map_height++;
	v->map_width = ft_strlen(game->map[0]);
}

void	find_horizontal_hit(t_var *v, double a, t_cube *g)
{
	v->y_intercept = floor(v->player_py / v->ceil_size) * v->ceil_size;
	if (sin(a) > 0)
		v->y_intercept += v->ceil_size;
	v->x_intercept = v->player_px + ((v->y_intercept - v->player_py) / tan(a));
	v->y_step = v->ceil_size;
	if (sin(a) < 0)
		v->y_step *= -1;
	else
		v->y_step *= 1;
	v->x_step = v->ceil_size / tan(a);
	if ((cos(a) < 0 && v->x_step > 0) || (cos(a) > 0 && v->x_step < 0))
		v->x_step *= -1;
	v->nextHorz_x = v->x_intercept;
	v->nextHorz_y = v->y_intercept;
	while (v->nextHorz_x > 0 && v->nextHorz_x <= v->map_width * TILE_SIZE
		&& v->nextHorz_y > 0 && v->nextHorz_y <= v->map_height * TILE_SIZE)
	{
		v->map_x = (int)(v->nextHorz_x / v->ceil_size);
		v->map_y = (int)(v->nextHorz_y / v->ceil_size);
		if (sin(a) < 0)
			v->map_y = (int)((v->nextHorz_y - 1) / v->ceil_size);
		if (v->map_y < 0 || v->map_y >= v->map_height
			|| v->map_x < 0 || v->map_x >= v->map_width)
			break ;
		if (g->map[v->map_y][v->map_x] == '1')
		{
			v->HorzWallHit = 1;
			v->HorzWallHit_x = v->nextHorz_x;
			v->HorzWallHit_y = v->nextHorz_y;
			break ;
		}
		v->nextHorz_x += v->x_step;
		v->nextHorz_y += v->y_step;
	}
}

void	find_vertical_hit(t_var *v, double a, t_cube *g)
{
	v->x_intercept = floor(v->player_px / v->ceil_size) * v->ceil_size;
	if (cos(a) > 0)
		v->x_intercept += v->ceil_size;
	v->y_intercept = v->player_py + ((v->x_intercept - v->player_px) * tan(a));
	v->x_step = v->ceil_size;
	if (cos(a) < 0)
		v->x_step *= -1;
	else
		v->x_step *= 1;
	v->y_step = v->ceil_size * tan(a);
	if ((sin(a) < 0 && v->y_step > 0) || (sin(a) > 0 && v->y_step < 0))
		v->y_step *= -1;
	v->nextVert_x = v->x_intercept;
	v->nextVert_y = v->y_intercept;
	while (v->nextVert_x > 0 && v->nextVert_x <= v->map_width * TILE_SIZE
		&& v->nextVert_y > 0 && v->nextVert_y <= v->map_height * TILE_SIZE)
	{
		v->map_x = (int)(v->nextVert_x / v->ceil_size);
		v->map_y = (int)(v->nextVert_y / v->ceil_size);
		if (cos(a) < 0)
			v->map_x = (int)((v->nextVert_x - 1) / v->ceil_size);
		if (v->map_y < 0 || v->map_y >= v->map_height
			|| v->map_x < 0 || v->map_x >= v->map_width)
			break ;
		if (g->map[v->map_y][v->map_x] == '1')
		{
			v->VertWallHit = 1;
			v->VertWallHit_x = v->nextVert_x;
			v->VertWallHit_y = v->nextVert_y;
			break ;
		}
		v->nextVert_x += v->x_step;
		v->nextVert_y += v->y_step;
	}
}

void	select_hit(t_var *v)
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
	if (v->HorzHitDistance < v->VertHitDistance)
	{
		v->flag = 1;
		v->WallHitX = v->HorzWallHit_x;
		v->WallHitY = v->HorzWallHit_y;
		v->rayDistance = v->HorzHitDistance;
	}
	else
	{
		v->flag = 0;
		v->WallHitX = v->VertWallHit_x;
		v->WallHitY = v->VertWallHit_y;
		v->rayDistance = v->VertHitDistance;
	}

}
// 
// void draw_textured_wall(int rayId, t_var *v, t_cube *g)
// {
//     t_texture *tex = NULL;

//     // find each textures used in horz or vertical
//    	if (v->HorzHitDistance < v->VertHitDistance)  
// 	{
// 		if (sin(v->ray_angle) > 0)
// 			tex = &g->textures.so;
// 		else                         
// 			tex = &g->textures.no;  
// 	}
// 	else 
// 	{
// 		if (cos(v->ray_angle) > 0)  
// 			tex = &g->textures.ea;  
// 		else                        
// 			tex = &g->textures.we; 
// 	}

// 	// sOuth and west look not good
//     // find position hit in wall 
//     if (v->flag == 0)  
//         v->hit_offset = fmod(v->WallHitY, v->ceil_size);
//     else  
//         v->hit_offset = fmod(v->WallHitX, v->ceil_size);

//     //find position in textures and used mlx image 
//     int texX = (int)((v->hit_offset / TILE_SIZE) * tex->width);
//     if (v->flag == 0 || v->flag == 1)
//         texX = tex->width - texX  - 1;

//     uint8_t *pixels = (uint8_t *)tex->img->pixels;
//     double step = 1.0 * tex->height / v->WallStripHeight;
// 	double texPos = (v->top - HEIGHT / 2 + v->WallStripHeight / 2) * step;
//     for (int y = v->top; y < v->bottom; y++)
//     {
//         int texY = (int)texPos;

// 		texPos += step;
// 		// overflow index -----
//         int index = (texY * tex->width + texX) * 4;
//         uint8_t r = pixels[index + 0];
//         uint8_t g_col = pixels[index + 1];
//         uint8_t b = pixels[index + 2];
//         uint8_t a = pixels[index + 3];

//         uint32_t color = (r << 24) | (g_col << 16) | (b << 8) | a;
//         mlx_put_pixel(g->img, rayId, y, color);
//     }
// }
void draw_textured_wall(int rayId, t_var *v, t_cube *g)
{
    t_texture *tex = NULL;

    // اختيار التكستشر حسب الاتجاه
    if (v->HorzHitDistance < v->VertHitDistance)  
    {
        if (sin(v->ray_angle) > 0)
            tex = &g->textures.so;  // جنوب
        else                         
            tex = &g->textures.no;  // شمال
    }
    else  
    {
        if (cos(v->ray_angle) > 0)  
            tex = &g->textures.ea;  // شرق
        else                        
            tex = &g->textures.we;  // غرب
    }

    // حساب الموقع في الحيط
    if (v->flag == VERTICAL)  
        v->hit_offset = fmod(v->WallHitY, v->ceil_size);
    else  
        v->hit_offset = fmod(v->WallHitX, v->ceil_size);

    // حساب إحداثية X في التكستشر
    int texX = (int)((v->hit_offset / TILE_SIZE) * tex->width);
    
    // اقلب حسب الاتجاه
    if (v->HorzHitDistance < v->VertHitDistance)  // Horizontal wall (N/S)
    {
        if (sin(v->ray_angle) > 0)  // South - اقلبو
            texX = tex->width - texX - 1;
        // North - ماتقلبوش (خدام مزيان)
    }
    else  // Vertical wall (E/W)
    {
        if (cos(v->ray_angle) < 0)  // West - اقلبو (بدلنا الشرط!)
            texX = tex->width - texX - 1;
        // East - ماتقلبوش
    }

    uint8_t *pixels = (uint8_t *)tex->img->pixels;
    double step = 1.0 * tex->height / v->WallStripHeight;
    double texPos = (v->top - HEIGHT / 2 + v->WallStripHeight / 2) * step;
    
    for (int y = v->top; y < v->bottom; y++)
    {
        int texY = (int)texPos;
        texPos += step;
        
        // التحقق من الحدود
        if (texY < 0) texY = 0;
        if (texY >= tex->height) texY = tex->height - 1;
        if (texX < 0) texX = 0;
        if (texX >= tex->width) texX = tex->width - 1;
        
        int index = (texY * tex->width + texX) * 4;
        uint8_t r = pixels[index + 0];
        uint8_t g_col = pixels[index + 1];
        uint8_t b = pixels[index + 2];
        uint8_t a = pixels[index + 3];

        uint32_t color = (r << 24) | (g_col << 16) | (b << 8) | a;
        mlx_put_pixel(g->img, rayId, y, color);
    }
}
void compute_projection(t_var *v, int rayId, t_cube *g, double ray_angle)
{
	v->ray_angle = ray_angle;
    v->DistanceProjectionPlane = (WIDTH / 2) / tan(FOV / 2);
    v->WallStripHeight = ((TILE_SIZE + 1) / (v->rayDistance * cos(ray_angle - g->player->rotate_Angle)))
        * v->DistanceProjectionPlane;

    v->top = (HEIGHT / 2) - (v->WallStripHeight / 2);
    v->bottom = (HEIGHT / 2) + (v->WallStripHeight / 2);

    if (v->top < 0)
        v->top = 0;
    if (v->bottom >= HEIGHT)
        v->bottom = HEIGHT - 1;

    // color ceiling
    for (int y = 0; y < v->top; y++)
        mlx_put_pixel(g->img, rayId, y, 0x00CCCCAA);

    // draw textured wall
    draw_textured_wall(rayId, v, g);

    // color floor
    for (int y = v->bottom; y < HEIGHT; y++)
        mlx_put_pixel(g->img, rayId, y, 0x777700FF);
}

