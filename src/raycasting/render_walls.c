/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anachat <anachat@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 10:47:03 by anachat           #+#    #+#             */
/*   Updated: 2025/08/30 10:46:17 by anachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_wall_strip(t_ray *ray, double line_x)
{
	double	fixed_dist;
	double	line_h;
	double	line_y;
	int		color;

	fixed_dist = ray->dist * cos(normalize_angle(ray->angle
				- data()->player->angle));
	line_h = (WINDOW_H * TILE_SIZE) / fixed_dist;
	line_y = (WINDOW_H / 2) - (line_h / 2);
	color = 0xAA0000FF;
	if (ray->was_vert)
		color = WALL_COLOR;
	if (line_y < 0.0)
		line_y = 0;
	if (line_x < 0.0)
		line_x = 0;
	if (line_h > (double)WINDOW_H)
		line_h = WINDOW_H;
	if (line_h < 0.0)
		line_h = 0;
	if (line_y > (double)WINDOW_H)
		line_y = WINDOW_H;
	if (line_x > (double)WINDOW_W)
		line_x = WINDOW_W;
	draw_rect(new_point(line_x, line_y), RAY_THICKNESS, line_h, color);
}
