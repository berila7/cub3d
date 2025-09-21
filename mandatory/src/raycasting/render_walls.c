/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 10:47:03 by anachat           #+#    #+#             */
/*   Updated: 2025/09/21 11:53:29 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_wall_strip(t_ray *ray, double line_x)
{
	double fixed_dist = ray->dist * cos(normalize_angle(ray->angle - data()->player->angle));
	if (fixed_dist < 0.0001)
		fixed_dist = 0.0001;

	double line_h = (WINDOW_H * TILE_SIZE) / fixed_dist;

	int screen_x = (int)line_x;
	if (screen_x < 0)
		screen_x = 0;
	if (screen_x >= WINDOW_W)
		screen_x = WINDOW_W - 1;

	render_textured_column(ray, screen_x, line_h);
}
