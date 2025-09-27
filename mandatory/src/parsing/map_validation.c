/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 10:08:24 by mberila           #+#    #+#             */
/*   Updated: 2025/09/25 17:29:54 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**copy_map(void)
{
	int		i;
	char	**copy;

	copy = gc_malloc(sizeof(char *) * (data()->height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < data()->height)
	{
		copy[i] = gc_strdup(data()->map[i]);
		if (!copy[i])
			return (NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

bool	player_char(char element)
{
	if (element == P_NORTH || element == P_WEST
		|| element == P_EAST || element == P_SOUTH)
		return (true);
	return (false);
}

void	find_char_pos(int *pos_x, int *pos_y)
{
	int			i;
	size_t		j;

	i = 0;
	while (i < data()->height)
	{
		j = 0;
		while (j < ft_strlen(data()->map[i]))
		{
			if (player_char(data()->map[i][j]))
			{
				*pos_x = j;
				*pos_y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

int	check_holes()
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
	int		player_x;
	int		player_y;

	find_char_pos(&player_x, &player_y);
	if (!check_holes())
		return (0);
	return (1);
}
