/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anachat <anachat@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:50:24 by anachat           #+#    #+#             */
/*   Updated: 2025/08/07 17:14:35 by anachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_pixel(int x, int y, int color)
{
	if (x < 0 || y < 0 || x > WINDOW_W || y > WINDOW_H)
		return ;
	mlx_put_pixel(data()->w_img, x, y, color);
}

void	draw_rect(t_point *start, int width, int height, int color)
{
	int	i;
	int	j;

	i = start->y;
	while ((i - start->y) < height)
	{
		j = start->x;
		while ((j - start->x) < width)
		{
			draw_pixel(j, i, color);
			j++;
		}
		i++;
	}
}

void	draw_line(t_point *p1, t_point *p2, int color)
{
	float	dx;
	float	dy;
	float	step[2];
	int		max_steps;
	t_point	*pos;

	dx = p2->x - p1->x;
	dy = p2->y - p1->y;
	max_steps = fabsf(dy);
	if (fabsf(dx) > fabsf(dy))
		max_steps = fabsf(dx);
	step[0] = dx / max_steps;
	step[1] = dy / max_steps;
	pos = new_point(p1->x, p1->y);
	while (max_steps--)
	{
		draw_pixel(roundf(pos->x), roundf(pos->y), color);
		pos->x += step[0];
		pos->y += step[1];
	}
}

void	draw_player(void)
{
	int			size;
	t_point		*new_p;
	t_player	*pl;

	size = 10;
	pl = data()->player;
	new_p = new_point(pl->x + cos(pl->angle) * pl->move_inp * M_SPEED,
			pl->y + sin(pl->angle) * pl->move_inp * M_SPEED);
	// new_x = pl->x + cos(pl->angle) * pl->move_inp * M_SPEED;
	// new_y = pl->y + sin(pl->angle) * pl->move_inp * M_SPEED;
	if (!has_wall_at(new_p->x, new_p->y))
	{
		pl->x = new_p->x;
		pl->y = new_p->y;
	}
	pl->angle = normalize_angle(pl->angle + (pl->rotation_inp * R_SPEED));
	draw_rect(new_point(pl->x - (size / 2), pl->y - (size / 2)),
		size, size, 0xFF0000FF);
	// draw_line(new_point(pl->x, pl->y), 
	// 	new_point(pl->x + cos(pl->angle) * 50,
	// 	pl->y + sin(pl->angle) * 50), 0xFF0000FF
	// );
}

void	draw_rays(void)
{
	double	start_angle;
	t_point	*start;
	t_ray	ray;
	int		i;

	i = -1;
	start_angle = data()->player->angle - (data()->fov_angle / 2.0);
	while (++i < data()->num_rays)
	{
		ray = data()->rays[i];
		ray.hit = new_point(0, 0);
		ray.angle = normalize_angle(start_angle);
		ray.is_down = start_angle > 0 && start_angle < M_PI;
		ray.is_right = start_angle > (M_PI * 1.5) || start_angle < M_PI / 2;
		find_horiz_hit(&ray);
		find_vert_hit(&ray);
		start = new_point(data()->player->x, data()->player->y);
		draw_line(start, new_point(ray.hit->x, ray.hit->y), 0x0000FFFF);
		start_angle += (data()->fov_angle / data()->num_rays);
	}
}
