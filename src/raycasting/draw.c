/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anachat <anachat@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:50:24 by anachat           #+#    #+#             */
/*   Updated: 2025/08/11 18:42:14 by anachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(void)
{
	t_player	*pl;
	int			size;

	size = 10;
	pl = data()->player;
	draw_rect(new_point(pl->x - (size / 2), pl->y - (size / 2)),
		size, size, 0xFF0000FF);
	draw_line(new_point(pl->x, pl->y), new_point(pl->x + cos(pl->angle) * 50,
			pl->y + sin(pl->angle) * 50), 0xFF0000FF);
}

void	cast_rays(void)
{
	double	start_angle;
	t_ray	*ray;
	int		i;

	i = -1;
	start_angle = data()->player->angle - (data()->fov_angle / 2.0);
	while (++i < data()->num_rays)
	{
		ray = data()->rays + i;
		ray->hit = new_point(0, 0);
		ray->angle = normalize_angle(start_angle);
		ray->is_down = ray->angle > 0 && ray->angle < M_PI;
		ray->is_right = ray->angle > (M_PI * 1.5) || ray->angle < M_PI / 2;
		find_hit(ray);
		render_wall_strip(ray, RAY_THICKNESS * i);
		start_angle += (data()->fov_angle / data()->num_rays);
	}
}

void	draw_map(void)
{
	char	**map;
	int		ind;
	int		i;
	int		j;

	map = data()->map;
	ind = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == '0')
				draw_rect(new_point(j * TILE_SIZE, i * TILE_SIZE),
					TILE_SIZE, TILE_SIZE, 0xADD8E6FF);
			else if (map[i][j] == '1')
				draw_rect(new_point(j * TILE_SIZE, i * TILE_SIZE),
					TILE_SIZE, TILE_SIZE, 0x111111FF);
			ind++;
			j++;
		}
		i++;
	}
}
