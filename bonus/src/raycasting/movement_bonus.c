/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anachat <anachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 17:44:42 by anachat           #+#    #+#             */
/*   Updated: 2025/09/22 18:01:15 by anachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	track_mouse(int *rotation_inp)
{
	int	x;
	int	y;

	mlx_get_mouse_pos(data()->mlx, &x, &y);
	if (x < WINDOW_W / 2)
		*rotation_inp = -1;
	else if (x > WINDOW_W / 2)
		*rotation_inp = 1;
	mlx_set_mouse_pos(data()->mlx, WINDOW_W / 2, WINDOW_H / 2);
}

static void	check_door(void)
{
	bool	space_down;
	t_point	check;
	int		fx;
	int		fy;
	char	*cell;

	space_down = mlx_is_key_down(data()->mlx, MLX_KEY_SPACE);
	if (space_down && !data()->space_was_dow)
	{
		check = new_point(0, 0);
		check.x = data()->player->x + cos(data()->player->angle) * DIST;
		check.y = data()->player->y
			+ sin(data()->player->angle) * DIST;
		fx = (int)(check.x / TILE_SIZE);
		fy = (int)(check.y / TILE_SIZE);
		if (fy >= 0 && fx >= 0 && fy < data()->height && fx < data()->width)
		{
			cell = &data()->map[fy][fx];
			if (*cell == DOOR_CLOSED)
				*cell = DOOR_OPEN;
			else if (*cell == DOOR_OPEN)
				*cell = DOOR_CLOSED;
		}
	}
	data()->space_was_dow = space_down;
}

bool	game_input(mlx_t *mlx)
{
	t_player	*pl;

	pl = data()->player;
	pl->move_side = 0;
	pl->move_forward = 0;
	pl->rotation_inp = 0;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		pl->move_forward = 1;
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		pl->move_forward = -1;
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		pl->move_side = -1;
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		pl->move_side = 1;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		pl->rotation_inp = -1;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		pl->rotation_inp = 1;
	check_door();
	track_mouse(&pl->rotation_inp);
	if (pl->move_forward || pl->move_side || pl->rotation_inp)
		return (true);
	return (false);
}
