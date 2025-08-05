/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anachat <anachat@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:58:49 by anachat           #+#    #+#             */
/*   Updated: 2025/08/05 18:26:34 by anachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	has_wall_at(double x, double y)
{
	int fx;
	int fy;

	fy = floor(y/TILE_SIZE);
	fx = floor(x/TILE_SIZE);
	return (data()->map[fy][fx] == '1');
}

static void	game_input(mlx_t *mlx)
{
	data()->player->move_inp = 0;
	data()->player->rotation_inp = 0;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		data()->player->move_inp = 1;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		data()->player->move_inp = -1;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		data()->player->rotation_inp = -1;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		data()->player->rotation_inp = 1;
}

void draw_rect(int x, int y, int width, int height, int color)
{	
	int i = y;
	int j;

	while ((i-y) < height)
	{
		j = x;
		while ((j-x) < width)
		{
			mlx_put_pixel(data()->w_img, j, i, color);
			j++;
		}
		i++;
	}
}



 

void draw_player()
{
	int	size;
	double new_x;
	double new_y;

	size = 10;
	new_x = data()->player->x + cos(data()->player->angle) * data()->player->move_inp * M_SPEED;
	new_y = data()->player->y + sin(data()->player->angle) * data()->player->move_inp * M_SPEED;

	if (!has_wall_at(new_x, new_y))
	{
		data()->player->x = new_x;
		data()->player->y = new_y;
	}
	data()->player->angle = normalize_angle(data()->player->angle + (data()->player->rotation_inp * R_SPEED));
	draw_rect(data()->player->x - (size/2), data()->player->y - (size/2), size, size, 0xFF0000FF);
	
	draw_line(new_point(data()->player->x, data()->player->y), 
		new_point(data()->player->x + cos(data()->player->angle) * 50,
		data()->player->y + sin(data()->player->angle) * 50), 0xFF0000FF
	);
}

void	render_map()
{
	char **map;
	int i;
	int j;
	int ind;

	map = data()->map;
	i = 0;
	ind=0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == '0')
			{
				// draw ground
				draw_rect(j*TILE_SIZE, i*TILE_SIZE, TILE_SIZE, TILE_SIZE, 0xADD8E6FF);
			}
			else if (map[i][j] == '1')
			{
				// draw wall
				draw_rect(j*TILE_SIZE, i*TILE_SIZE, TILE_SIZE, TILE_SIZE, 0x111111FF);
			}
			ind++;
			j++;
		}
		i++;
	}
}
void	draw_rays()
{
	double start_angle;
	int i;

	start_angle = data()->player->angle - (data()->fov_angle/2.0);
	i = -1;
	
	// Debug info
	printf("=== DEBUG INFO ===\n");
	printf("player->angle: %.6f\n", data()->player->angle);
	printf("fov_angle: %.6f\n", data()->fov_angle);
	printf("num_rays: %d\n", data()->num_rays);
	printf("increment: %.6f\n", (data()->fov_angle / data()->num_rays));
	printf("initial start_angle: %.6f\n", start_angle);
	printf("==================\n");
	
	while (++i < data()->num_rays)
	{
		printf("[%d] start_angle: %.6f -> ", i, start_angle);
		data()->rays[i].angle = normalize_angle(start_angle);
		printf("normalized: %.6f\n", data()->rays[i].angle);
		
		draw_line(new_point(data()->player->x, data()->player->y),
			new_point(data()->player->x+cos(data()->rays[i].angle)*100,
			data()->player->y+sin(data()->rays[i].angle)*100), 0x0000FFFF);
		start_angle += (data()->fov_angle / data()->num_rays);
	}
}

static void	game_loop(void *param) 
{
	mlx_t	*mlx;

	mlx = (mlx_t *)param;
	game_input(mlx);
	render_map();
	draw_player();
	draw_rays();
}

int	game()
{
	data()->mlx = mlx_init(WINDOW_W, WINDOW_H, "Test Cub3d", false);
	if (!data()->mlx)
		return (perror("Failed to init mlx"), 1);
	data()->player = gc_malloc(sizeof(t_player));

	data()->w_img = mlx_new_image(data()->mlx, WINDOW_W, WINDOW_H);
	mlx_image_to_window(data()->mlx, data()->w_img, 0, 0);
	
	data()->num_rays = WINDOW_W/50;
	data()->fov_angle = to_rad(FOV_ANGLE);
	
	printf("data()->num_rays: %d\n",data()->num_rays);
	
	data()->rays = gc_malloc(sizeof(t_ray) * data()->num_rays);
	
	data()->player_y = 2;
	data()->player_x = 10;	
	data()->player->angle = to_rad(45);
	
	data()->player->x = data()->player_x*TILE_SIZE;
	data()->player->y = data()->player_y*TILE_SIZE;

	mlx_loop_hook(data()->mlx, game_loop, data()->mlx);
	mlx_loop(data()->mlx);
	mlx_terminate(data()->mlx);
	return (0);
}
