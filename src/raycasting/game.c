/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anachat <anachat@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:58:49 by anachat           #+#    #+#             */
/*   Updated: 2025/08/11 16:53:08 by anachat          ###   ########.fr       */
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
	ind = 0;
	i = 0;
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

void	render_game()
{
	if (data()->w_img)
		mlx_delete_image(data()->mlx, data()->w_img);

	data()->w_img = mlx_new_image(data()->mlx, WINDOW_W, WINDOW_H);
	mlx_image_to_window(data()->mlx, data()->w_img, 0, 0);

	// draw sky
	draw_rect(new_point(0, 0), WINDOW_W, WINDOW_H / 2, 0x6CA0DCFF);
	// draw ground
	draw_rect(new_point(0, WINDOW_H / 2), WINDOW_W, WINDOW_H / 2, 0x70543CFF);

	// render_map();
	// draw_player();
	update_player();
	cast_rays();
	// render_walls();
}

void	game_loop(void *param) 
{
	mlx_t		*mlx;
	bool		input_changed;

	mlx = (mlx_t *)param;
	input_changed = game_input(mlx);
	if (input_changed)
		render_game();
}

void	get_pl_pos(char **map)
{
	bool	found;
	int		i;
	int		j;

	found = false;
	i = -1;
	while (!found && ++i < data()->height)
	{
		j = -1;
		while (++j < data()->width)
		{ 
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != ' ')
			{
				data()->player_y = i;
				data()->player_x = j;
				found = true;
				break ;
			}
		}
	}
	printf("ch: %c\n", map[i][j]);
	if (map[i][j] == 'E')
		data()->player->angle = 0;
	else if (map[i][j] == 'N')
		data()->player->angle = (M_PI * 1.5);
	else if (map[i][j] == 'W')
		data()->player->angle = (M_PI);
	else if (map[i][j] == 'S')
		data()->player->angle = (M_PI * 0.5);
}

int	game(void)
{
	data()->mlx = mlx_init(WINDOW_W, WINDOW_H, "Test Cub3d", false);
	if (!data()->mlx)
		return (perror("Failed to init mlx"), 1);
	data()->player = gc_malloc(sizeof(t_player));
	data()->num_rays = WINDOW_W / RAY_THICKNESS;
	data()->fov_angle = to_rad(FOV_ANGLE);
	data()->rays = gc_malloc(sizeof(t_ray) * data()->num_rays);

	get_pl_pos(data()->map);
	data()->player->x = data()->player_x * TILE_SIZE;
	data()->player->y = data()->player_y * TILE_SIZE;

	render_game();
	
	mlx_loop_hook(data()->mlx, game_loop, data()->mlx);
	
	mlx_loop(data()->mlx);
	mlx_terminate(data()->mlx);
	return (0);
}
