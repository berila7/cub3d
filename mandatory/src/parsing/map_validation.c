/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 10:08:24 by mberila           #+#    #+#             */
/*   Updated: 2025/10/10 14:54:09 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	player_char(char element)
{
	if (element == P_NORTH || element == P_WEST
		|| element == P_EAST || element == P_SOUTH)
		return (true);
	return (false);
}

int	check_holes(void)
{
	int	h;
	int	w;

	h = 0;
	while (h < data()->height)
	{
		w = -1;
		while (++w < (int)ft_strlen(data()->map[h]))
		{
			if (!player_char(data()->map[h][w])
				&& data()->map[h][w] != '0')
				continue ;
			if (!w || !h || !data()->map[h + 1]
				|| w == ((int)ft_strlen(data()->map[h]) - 1)
				|| data()->map[h][w + 1] == ' ' || data()->map[h][w - 1] == ' '
				|| data()->map[h + 1][w] == ' ' || data()->map[h - 1][w] == ' '
			)
				return (0);
		}
		h++;
	}
	return (1);
}

int	check_map(void)
{
	if (!check_holes())
		return (0);
	return (1);
}
