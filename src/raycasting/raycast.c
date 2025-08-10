/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anachat <anachat@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 10:55:36 by anachat           #+#    #+#             */
/*   Updated: 2025/08/08 15:45:32 by anachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	in_window(double x, double y)
{
	return ((x >= 0 && x <= WINDOW_W) && (y >= 0 && y <= WINDOW_H));
}

bool	in_map(double x, double y)
{
	return ((x >= 0 && x < (data()->width * TILE_SIZE))
		&& (y >= 0 && y < (data()->height * TILE_SIZE)));
}

t_ray_hit	find_horiz_hit(t_ray *ray, t_player *pl)
{
	t_point		interc;
	t_point		step;
	t_ray_hit	hit;
	double		decr;

	hit.x = 0;
	hit.y = 0;
	hit.dist = MAX_DOUBLE;
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
	while (in_map(interc.x, interc.y))
	{
		decr = 0;
		if (!ray->is_down)
			decr = 1;
		if (has_wall_at(interc.x, interc.y - decr))
			return (hit.x = interc.x, hit.y = interc.y, hit.dist = get_dist(pl->x, pl->y, hit.x, hit.y), hit);
		(1 && (interc.x += step.x, interc.y += step.y));
	}
	return (hit);
}


t_ray_hit	find_vert_hit(t_ray *ray, t_player *pl)
{
	t_point		interc;
	t_point		step;
	t_ray_hit	hit;
	double		decr;

	hit.x = 0;
	hit.y = 0;
	hit.dist = MAX_DOUBLE;
	interc.x = floor(pl->x / TILE_SIZE) * TILE_SIZE;
	if (ray->is_right)
		interc.x += TILE_SIZE;
	interc.y = ((interc.x - pl->x) * tan(ray->angle)) + pl->y;
	step.x = TILE_SIZE;
	if (!ray->is_right)
		step.x *= -1;
	step.y = fabs(TILE_SIZE * tan(ray->angle));
	if (!ray->is_down)
		step.y *= -1;
	while (in_map(interc.x, interc.y))
	{
		decr = 0;
		if (!ray->is_right)
			decr = 1;
		if (has_wall_at(interc.x - decr, interc.y))
		{
			return (hit.x = interc.x, hit.y = interc.y, hit.dist = get_dist(pl->x, pl->y, hit.x, hit.y), hit);
			printf("HIT at x=%.2f, y=%.2f\n", interc.x - decr, interc.y);	
		}
		(1 && (interc.x += step.x, interc.y += step.y));
	}
	return (hit);
}


void	find_hit(t_ray *ray)
{
	t_ray_hit	horiz_hit;
	t_ray_hit	vert_hit;

	horiz_hit = find_horiz_hit(ray, data()->player);
	vert_hit = find_vert_hit(ray, data()->player);
	if (horiz_hit.dist < vert_hit.dist)
	{
		ray->dist = horiz_hit.dist;
		ray->hit.x = horiz_hit.x;
		ray->hit.y = horiz_hit.y;
		ray->was_vert = false;
	}
	else
	{
		ray->dist = vert_hit.dist;
		ray->hit.x = vert_hit.x;
		ray->hit.y = vert_hit.y;
		ray->was_vert = true;
	}
}
