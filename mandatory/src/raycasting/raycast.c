/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 10:55:36 by anachat           #+#    #+#             */
/*   Updated: 2025/09/25 18:20:53 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_horiz_hit(t_point *interc, t_point *step, t_ray *ray)
{
	interc->y = floor(data()->player->y / TILE_SIZE) * TILE_SIZE;
	if (ray->is_down)
		interc->y += TILE_SIZE;
	interc->x = ((interc->y - data()->player->y)
			/ tan(ray->angle)) + data()->player->x;
	step->y = TILE_SIZE;
	if (!ray->is_down)
		step->y *= -1;
	step->x = fabs(TILE_SIZE / tan(ray->angle));
	if (!ray->is_right)
		step->x *= -1;
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
	init_horiz_hit(&interc, &step, ray);
	while (in_map(interc.x, interc.y))
	{
		decr = 0;
		if (!ray->is_down)
			decr = 1;
		if (has_wall_at(interc.x, interc.y - decr))
			return (hit.x = interc.x, hit.y = interc.y,
				hit.dist = get_dist(pl->x, pl->y, hit.x, hit.y), hit);
		interc.x += step.x;
		interc.y += step.y;
	}
	return (hit);
}

void	init_vert_hit(t_point *interc, t_point *step, t_ray *ray)
{
	interc->x = floor(data()->player->x / TILE_SIZE) * TILE_SIZE;
	if (ray->is_right)
		interc->x += TILE_SIZE;
	interc->y = ((interc->x - data()->player->x)
			* tan(ray->angle)) + data()->player->y;
	step->x = TILE_SIZE;
	if (!ray->is_right)
		step->x *= -1;
	step->y = fabs(TILE_SIZE * tan(ray->angle));
	if (!ray->is_down)
		step->y *= -1;
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
	init_vert_hit(&interc, &step, ray);
	while (in_map(interc.x, interc.y))
	{
		decr = 0;
		if (!ray->is_right)
			decr = 1;
		if (has_wall_at(interc.x - decr, interc.y))
			return (hit.x = interc.x, hit.y = interc.y,
				hit.dist = get_dist(pl->x, pl->y, hit.x, hit.y), hit);
		interc.x += step.x;
		interc.y += step.y;
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
