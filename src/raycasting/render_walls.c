/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anachat <anachat@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 10:47:03 by anachat           #+#    #+#             */
/*   Updated: 2025/08/08 16:19:48 by anachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_wall_strip(t_ray *ray, double line_x)
{
	double	fixed_dist;
	double	line_h;
	double	line_y;
	int		color;

	fixed_dist = ray->dist * cos(normalize_angle(ray->angle - data()->player->angle));
	line_h = (WINDOW_H * TILE_SIZE) / fixed_dist;
	line_y = (WINDOW_H/2) - (line_h/2);
	color = 0xAA0000FF;
	if (ray->was_vert)
		color = 0xFF0000FF;
	draw_rect(new_point(line_x, line_y), RAY_THICKNESS, line_h, color);
}
