/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anachat <anachat@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:58:49 by anachat           #+#    #+#             */
/*   Updated: 2025/07/29 16:36:20 by anachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	game_input(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	data()->player->moveInp = 0;
	data()->player->moveInp = 0;
	data()->player->rotationInp = 0;
	data()->player->rotationInp = 0;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		data()->player->moveInp = -1;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		data()->player->moveInp = 1;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		data()->player->rotationInp = -1;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		data()->player->rotationInp = 1;
}


void	draw_rect(int x, int y, int width, int height, int color)
{
	mlx_image_t *img = mlx_new_image(data()->mlx, width, height);
	int i = 0;
	int j = 0;

	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			mlx_put_pixel(img, j, i, color);
			j++;
		}
		i++;
	}
	mlx_image_to_window(data()->mlx, img, x, y);
}

static void	game_loop(void *param) 
{
	mlx_t	*mlx;

	mlx = (mlx_t *)param;

	int width = 30;
	int height = 70;
	
	data()->player->y += data()->player->moveInp * 10;
	data()->player->x += data()->player->rotationInp * 10;
	
	double x = data()->player->x - (width/2);
	double y = data()->player->y - (height/2);
	draw_rect(x, y, width, height, 0xFF0000FF);
}

int	game()
{
	data()->mlx = mlx_init(WINDOW_W, WINDOW_H, "Test Cub3d", false);
	if (!data()->mlx)
		return (perror("Failed to init mlx"), 1);
	data()->player = gc_malloc(sizeof(t_player));
	mlx_loop_hook(data()->mlx, game_loop, data()->mlx);
	mlx_loop_hook(data()->mlx, game_input, data()->mlx);
	mlx_loop(data()->mlx);
	mlx_terminate(data()->mlx);
	return (0);
}
