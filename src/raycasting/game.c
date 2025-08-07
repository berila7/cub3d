/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anachat <anachat@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:58:49 by anachat           #+#    #+#             */
/*   Updated: 2025/08/07 18:28:21 by anachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_map(void)
{
	char **map;
	int ind;
	int i;
	int j;

	map = data()->map;
	i = 0;
	ind=0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == '0')
				draw_rect(new_point(j * TILE_SIZE, i * TILE_SIZE), TILE_SIZE, TILE_SIZE, 0xADD8E6FF);
			else if (map[i][j] == '1')
				draw_rect(new_point(j * TILE_SIZE, i * TILE_SIZE), TILE_SIZE, TILE_SIZE, 0x111111FF);
			ind++;
			j++;
		}
		i++;
	}
}


static bool	game_input(mlx_t *mlx)
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
	if (data()->player->move_inp || data()->player->rotation_inp)
		return (true);
	return (false);
}

static void	game_loop(void *param) 
{
	mlx_t		*mlx;
	bool		input_changed;
	static bool	has_started;

	mlx = (mlx_t *)param;
	input_changed = game_input(mlx);
	if (input_changed || !has_started)
	{
		has_started = true;
		
	ft_bzero(data()->w_img->pixels, 
			data()->w_img->width * data()->w_img->height * sizeof(uint32_t));
		render_map();
		draw_player();
		draw_rays();
	}
}

int	game(void)
{
	data()->mlx = mlx_init(WINDOW_W, WINDOW_H, "Test Cub3d", false);
	if (!data()->mlx)
		return (perror("Failed to init mlx"), 1);
	data()->player = gc_malloc(sizeof(t_player));
	data()->num_rays = WINDOW_W / 50;
	data()->fov_angle = to_rad(FOV_ANGLE);
	data()->rays = gc_malloc(sizeof(t_ray) * data()->num_rays);
	data()->player_y = 2;
	data()->player_x = 10;
	data()->player->angle = to_rad(45);
	data()->player->x = data()->player_x * TILE_SIZE;
	data()->player->y = data()->player_y * TILE_SIZE;
	
	data()->w_img = mlx_new_image(data()->mlx, WINDOW_W, WINDOW_H);
	mlx_image_to_window(data()->mlx, data()->w_img, 0, 0);
	
	mlx_loop_hook(data()->mlx, game_loop, data()->mlx);
	
	mlx_loop(data()->mlx);
	mlx_terminate(data()->mlx);
	return (0);
}
