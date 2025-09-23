/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: berila <berila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:47:47 by anachat           #+#    #+#             */
/*   Updated: 2025/09/23 16:25:16 by berila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	in_window(double x, double y)
{
	return ((x >= 0 && x <= WINDOW_W) && (y >= 0 && y <= WINDOW_H));
}

void	set_pl_angle(char c)
{
	if (c == 'E')
		data()->player->angle = 0;
	else if (c == 'N')
		data()->player->angle = (M_PI * 1.5);
	else if (c == 'W')
		data()->player->angle = (M_PI);
	else if (c == 'S')
		data()->player->angle = (M_PI * 0.5);
}

void	get_pl_pos(char **map)
{
	bool	found;
	int		i;
	int		j;

	found = false;
	i = -1;
	while (!found && ++i < data()->height)
	{
		j = -1;
		while (++j < data()->width)
		{
			if (player_char(map[i][j]))
			{
				data()->player_y = i;
				data()->player_x = j;
				found = true;
				break ;
			}
		}
	}
	set_pl_angle(map[i][j]);
}

bool	can_move(double x, double y)
{
	double	padding;

	padding = 1.0;
	return (!has_wall_at(x - padding, y - padding)
		&& !has_wall_at(x + padding, y - padding)
		&& !has_wall_at(x - padding, y + padding)
		&& !has_wall_at(x + padding, y + padding));
}

uint32_t	pack_rgba(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}
