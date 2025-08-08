/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anachat <anachat@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 10:47:03 by anachat           #+#    #+#             */
/*   Updated: 2025/08/08 16:09:04 by anachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_walls()
{
	t_player	*pl;
	t_ray		ray;
	int			i;
	double		line_h;
	double		line_x;
	double		fixed_dist;

	pl = data()->player;
	i = -1;
	line_x = 0;
	// draw sky
	draw_rect(new_point(0, 0), WINDOW_W, WINDOW_H/2, 0x6CA0DCFF);
	// draw ground
	draw_rect(new_point(0, WINDOW_H/2), WINDOW_W, WINDOW_H/2, 0x70543CFF);
	while (++i < data()->num_rays)
	{
		ray = data()->rays[i];
		fixed_dist = ray.dist * cos(normalize_angle(ray.angle - pl->angle));
		line_h = (WINDOW_H * TILE_SIZE) / fixed_dist;
		draw_rect(new_point(line_x, (WINDOW_H/2) - (line_h/2)), RAY_THICKNESS, line_h, ray.was_vert ? 0xFF0000FF : 0xAA0000FF);
		line_x += RAY_THICKNESS;
	}
}
