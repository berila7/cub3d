/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anachat <anachat@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:47:47 by anachat           #+#    #+#             */
/*   Updated: 2025/08/06 14:09:46 by anachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double to_rad(double deg)
{
	return ((deg * M_PI) / 180);	
}

double	normalize_angle(double angle)
{
	angle = fmod(angle, (M_PI * 2));
	if (angle < 0)
		angle += (M_PI * 2);
	return (angle);
}

double get_dist(double ax, double ay, double bx, double by)
{
	// get distance between 2 points:
	return (sqrt(pow(by - ay, 2) + pow(bx - ax, 2)));
}

bool	has_wall_at(double x, double y)
{
	int	fx;
	int	fy;

	if (!in_window(x, y))
		return (false);
	fy = floor(y/TILE_SIZE);
	fx = floor(x/TILE_SIZE);
	if (fy < 0 || fy > data()->height || fx < 0 || fx > data()->width)
		return (false);
	printf("FX: [%d] (%f)  |  FY: [%d] (%f)\n", fx, x, fy, y);
	return (data()->map[fy][fx] == '1');
}
