/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anachat <anachat@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 10:55:36 by anachat           #+#    #+#             */
/*   Updated: 2025/08/07 20:09:28 by anachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	in_window(double x, double y)
{
	return ((x >= 0 && x <= WINDOW_W) && (y >= 0 && y <= WINDOW_H));
}

bool	in_map(double x, double y)
{
	return ((x >= 0 && x <= (data()->width * TILE_SIZE)) && (y >= 0 && y <= (data()->height * TILE_SIZE)));
}

bool	find_horiz_hit(t_ray *ray)
{
	t_point		interc;
	t_point		step;
	t_player	*pl;
	double		y;

	ray->dist = MAX_DOUBLE;
	pl = data()->player; 
	interc.y = floor(pl->y / TILE_SIZE) * TILE_SIZE;
	if (ray->is_down)
		interc.y += TILE_SIZE;
	interc.x = ((interc.y - pl->y) / tan(ray->angle)) + pl->x;
	step.y = TILE_SIZE;
	if (!ray->is_down)
		step.y *= -1;
	step.x = fabs(TILE_SIZE / tan(ray->angle));
	if (!ray->is_right)
		step.x *= -1;
	while (in_window(interc.x, interc.y))
	{
		y = 0;
		if (!ray->is_down)
			y = 1;
		if (has_wall_at(interc.x, interc.y - y))
		{
			ray->dist = get_dist(pl->x, pl->y, interc.x, interc.y);
			return (ray->hit.x = interc.x, ray->hit.y = interc.y, true);
		}
		(1 && (interc.x += step.x, interc.y += step.y));
	}
	return (false);
}


bool	find_vert_hit(t_ray *ray)
{
	t_point		interc;
	t_point		step;
	t_player	*pl;
	double		x;

	pl = data()->player; 
	interc.y = floor(pl->y / TILE_SIZE) * TILE_SIZE;
	if (ray->is_right)
		interc.x += TILE_SIZE;
	interc.y = ((interc.x - pl->x) / tan(ray->angle)) + pl->y;
	step.x = TILE_SIZE;
	if (!ray->is_right)
		step.x *= -1;
	step.y = fabs(TILE_SIZE / tan(ray->angle));
	if (!ray->is_down)
		step.x *= -1;
	while (in_window(interc.x, interc.y))
	{
		x = 0;
		if (!ray->is_right)
			x = 1;
		if (has_wall_at(interc.x - x, interc.y))
		{
			double dist = get_dist(pl->x, pl->y, interc.x, interc.y);
			if (dist < ray->dist)
			{
				ray->dist = get_dist(pl->x, pl->y, interc.x, interc.y);
				return (ray->hit.x = interc.x, ray->hit.y = interc.y, true);
			}
			break ;
		}
		(1 && (interc.x += step.x, interc.y += step.y));
	}
	return (false);
}
