/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 10:47:03 by anachat           #+#    #+#             */
/*   Updated: 2025/10/01 12:53:52 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	render_wall_strip(t_ray *ray, double line_x)
{
	double	fixed_dist;
	double	line_h;
	int		screen_x;

	fixed_dist = ray->dist * cos(normalize_angle(ray->angle
				- data()->player->angle));
	if (fixed_dist < 0.0001)
		fixed_dist = 0.0001;
	line_h = (WINDOW_H * TILE_SIZE) / fixed_dist;
	screen_x = (int)line_x;
	if (screen_x < 0)
		screen_x = 0;
	if (screen_x >= WINDOW_W)
		screen_x = WINDOW_W - 1;
	render_textured_column(ray, screen_x, line_h);
}
