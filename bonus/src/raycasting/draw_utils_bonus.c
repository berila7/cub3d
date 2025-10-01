/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:50:24 by anachat           #+#    #+#             */
/*   Updated: 2025/09/30 17:30:20 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_pixel(int x, int y, int color)
{
	if (x < 0 || y < 0 || x > WINDOW_W || y > WINDOW_H)
		return ;
	mlx_put_pixel(data()->w_img, x, y, color);
}

void	draw_rect(t_point start, int width, int height, int color)
{
	int	i;
	int	j;

	i = start.y;
	while ((i - start.y) < height)
	{
		j = start.x;
		while ((j - start.x) < width)
		{
			draw_pixel(j, i, color);
			j++;
		}
		i++;
	}
}

void	draw_line(t_point p1, t_point p2, int color)
{
	float	dx;
	float	dy;
	float	step[2];
	int		max_steps;
	t_point	pos;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	max_steps = fabsf(dy);
	if (fabsf(dx) > fabsf(dy))
		max_steps = fabsf(dx);
	step[0] = dx / max_steps;
	step[1] = dy / max_steps;
	pos.x = p1.x;
	pos.y = p1.y;
	while (max_steps-- >= 0)
	{
		draw_pixel(roundf(pos.x), roundf(pos.y), color);
		pos.x += step[0];
		pos.y += step[1];
	}
}

bool	has_door_at(double x, double y)
{
	int		fx;
	int		fy;
	char	cell;

	if (!data())
		return (false);
	if (!in_map(x, y))
		return (true);
	fy = (int)(y / TILE_SIZE);
	fx = (int)(x / TILE_SIZE);
	if (fy >= data()->height || fx >= data()->width || fy < 0 || fx < 0)
		return (true);
	cell = data()->map[fy][fx];
	if (cell == DOOR_CLOSED || cell == DOOR_OPEN)
		return (true);
	return (false);
}
