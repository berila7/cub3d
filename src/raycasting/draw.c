/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anachat <anachat@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:50:24 by anachat           #+#    #+#             */
/*   Updated: 2025/08/05 18:28:27 by anachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		mlx_put_pixel(data()->w_img, roundf(pos->x), roundf(pos->y), color);
		pos->x += step[0];
		pos->y += step[1];
	}
}
