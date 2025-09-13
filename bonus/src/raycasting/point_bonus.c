/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:52:11 by anachat           #+#    #+#             */
/*   Updated: 2025/09/13 12:00:27 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
