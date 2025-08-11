/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anachat <anachat@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:50:24 by anachat           #+#    #+#             */
/*   Updated: 2025/08/11 16:52:56 by anachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_pixel(int x, int y, int color)
{
	if (x < 0 || y < 0 || x > WINDOW_W || y > WINDOW_H)
		return ;
	mlx_put_pixel(data()->w_img, x, y, color);
}

void	draw_rect(t_point start, int width, int height, int color)
{
	int	i;
	int	j;

	i = start.y;
	while ((i - start.y) < height)
	{
		j = start.x;
		while ((j - start.x) < width)
		{
			draw_pixel(j, i, color);
			j++;
		}
		i++;
	}
}

void	draw_line(t_point p1, t_point p2, int color)
{
	float	dx;
	float	dy;
	float	step[2];
	int		max_steps;
	t_point	pos;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	max_steps = fabsf(dy);
	if (fabsf(dx) > fabsf(dy))
		max_steps = fabsf(dx);
	step[0] = dx / max_steps;
	step[1] = dy / max_steps;
	pos.x = p1.x;
	pos.y = p1.y;
	while (max_steps-- >= 0)
	{
		draw_pixel(roundf(pos.x), roundf(pos.y), color);
		pos.x += step[0];
		pos.y += step[1];
	}
}

bool	can_move(double x, double y)
{
	double	padding;

	padding = 1.0;
	return (
		!has_wall_at(x - padding, y - padding) &&
		!has_wall_at(x + padding, y - padding) &&
		!has_wall_at(x - padding, y + padding) &&
		!has_wall_at(x + padding, y + padding)
	);
}

void	draw_player(void)
{
	t_player	*pl;
	int			size;

	size = 10;
	pl = data()->player;
	draw_rect(new_point(pl->x - (size / 2), pl->y - (size / 2)),
		size, size, 0xFF0000FF);
	draw_line(new_point(pl->x, pl->y), 
		new_point(pl->x + cos(pl->angle) * 50,
		pl->y + sin(pl->angle) * 50), 0xFF0000FF
	);
}

void	update_player(void)
{
	t_point		new_p;
	t_player	*pl;

	pl = data()->player;
	new_p.x = pl->x + cos(pl->angle) * pl->move_inp * M_SPEED;
	new_p.y = pl->y + sin(pl->angle) * pl->move_inp * M_SPEED;
	// if (can_move(new_p.x, new_p.y))
	// {
	// 	pl->x = new_p.x;
	// 	pl->y = new_p.y;
	// }
	if (can_move(new_p.x, pl->y))
		pl->x = new_p.x;
	if (can_move(pl->x, new_p.y))
		pl->y = new_p.y;
	pl->angle = normalize_angle(pl->angle + (pl->rotation_inp * R_SPEED));
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
		//! draw Ray:
		// draw_line(new_point(data()->player->x, data()->player->y), new_point(ray->hit.x, ray->hit.y), 0x0000FFFF);
		//? render ray wall strip:
		render_wall_strip(ray, RAY_THICKNESS * i);
		start_angle += (data()->fov_angle / data()->num_rays);
	}
}
