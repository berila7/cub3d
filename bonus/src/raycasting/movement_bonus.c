/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 17:44:42 by anachat           #+#    #+#             */
/*   Updated: 2025/09/30 11:49:21 by mberila          ###   ########.fr       */
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

static void	close_door(void)
{
	bool	c_key_down;
	int		i;
	int		j;
	char	*closed;

	c_key_down = mlx_is_key_down(data()->mlx, MLX_KEY_C);
	if (c_key_down && !data()->open_door)
	{
		i = 0;
		while (i < data()->height)
		{
			j = 0;
			while (j < data()->width)
			{
				closed = &data()->map[i][j];
				if (*closed == DOOR_OPEN
					&& !has_door_at(data()->player->x, data()->player->y))
					*closed = DOOR_CLOSED;
				j++;
			}
			i++;
		}
	}
	data()->close_door = c_key_down;
}

static void	open_door(void)
{
	bool	o_key_down;
	int		i;
	int		j;
	char	*closed;

	o_key_down = mlx_is_key_down(data()->mlx, MLX_KEY_O);
	if (o_key_down && !data()->open_door)
	{
		i = 0;
		while (i < data()->height)
		{
			j = 0;
			while (j < data()->width)
			{
				closed = &data()->map[i][j];
				if (*closed == DOOR_CLOSED)
					*closed = DOOR_OPEN;
				j++;
			}
			i++;
		}
	}
	data()->open_door = o_key_down;
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
	open_door();
	close_door();
	track_mouse(&pl->rotation_inp);
	if (pl->move_forward || pl->move_side || pl->rotation_inp)
		return (true);
	return (false);
}
