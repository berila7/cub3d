/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anachat <anachat@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:52:11 by anachat           #+#    #+#             */
/*   Updated: 2025/08/11 18:21:13 by anachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point	*create_point(double x, double y)
{
	t_point	*pt;

	pt = gc_malloc(sizeof(t_point));
	pt->x = x;
	pt->y = y;
	return (pt);
}

t_point	new_point(double x, double y)
{
	t_point	pt;

	pt.x = x;
	pt.y = y;
	return (pt);
}
