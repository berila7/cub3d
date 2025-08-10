/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anachat <anachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:47:47 by anachat           #+#    #+#             */
/*   Updated: 2025/08/10 10:53:17 by anachat          ###   ########.fr       */
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
	return sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay));
}

bool	has_wall_at(double x, double y)
{
	int	fx;
	int	fy;

	if(!data())
		return false;
	if (!in_map(x, y))
		return (true);
	fy = (int)(y / TILE_SIZE);
	fx = (int)(x / TILE_SIZE);
	if (fy >= data()->height || fx >= data()->width || fy < 0 || fx < 0)
		return (true);
	
	printf("fy: %d, fx: %d\n\n", fy, fx);
	printf("Map: %s\n\n", data()->map[0]);
	printf("fy: %d, fx: %d\n\n", fy, fx);
		
	return (data()->map[fy][fx] == '1');
}
