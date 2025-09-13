/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anachat <anachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:50:24 by anachat           #+#    #+#             */
/*   Updated: 2025/09/13 17:31:15 by anachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"


void	draw_player(t_point pos)
{
	t_player	*pl;
	int			size;

	size = 10;
	pl = data()->player;
	draw_rect(new_point(pos.x - (size / 2), pos.y - (size / 2)),
		size, size, 0xFF0000FF);
	draw_line(new_point(pos.x, pos.y), new_point(pos.x + cos(pl->angle) * 50,
			pos.y + sin(pl->angle) * 50), 0xFF0000FF);
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

int	get_px_color(double x, double y)
{
	char	**map;
	int		color;
	int		fx;
	int		fy;

	map = data()->map;
	fy = (int)(y / TILE_SIZE);
	fx = (int)(x / TILE_SIZE);
	if (!((fx >= 0 && fx < data()->width
         && fy >= 0 && fy < data()->height)))
		return (0x1ca3ecFF);
	if (map[fy][fx] == '1' || map[fy][fx] == ' ')
		color = 0x000000FF;
	else // 0
		color = data()->floor;
	return (color);
}

void	render_minimap()
{
	int	mapx;
	int	mapy;

	mapx = floor(data()->player->x / TILE_SIZE);
	mapy = floor(data()->player->y / TILE_SIZE);
	int starty = data()->player->y - (MINIMAP_W / 2);
	int startx = data()->player->x - (MINIMAP_W / 2);
	int x = startx;
	int y = starty;
	draw_rect(new_point(WINDOW_W - (MINIMAP_W + 8), 0), (MINIMAP_W + 8), (MINIMAP_W + 8), 0x474747FF);
	while (y < starty + MINIMAP_W)
	{
		x = startx;
		while (x < startx + MINIMAP_W)
		{
			draw_pixel((WINDOW_W - MINIMAP_W) + (x - startx),
				(y - starty), get_px_color(x, y));
			x++;
		}
		y++;
	}
	draw_player(new_point(WINDOW_W - (MINIMAP_W / 2), MINIMAP_W / 2));
}
