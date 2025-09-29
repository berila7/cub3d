/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:32:54 by mberila           #+#    #+#             */
/*   Updated: 2025/09/29 12:08:48 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	txt_direction(char *line, char *path)
{
	if (!data()->no_path && ft_strncmp(line, "NO ", 3) == 0)
	{
		data()->no_path = path;
		return (true);
	}
	if (!data()->so_path && ft_strncmp(line, "SO ", 3) == 0)
	{
		data()->so_path = path;
		return (true);
	}
	if (!data()->we_path && ft_strncmp(line, "WE ", 3) == 0)
	{
		data()->we_path = path;
		return (true);
	}
	if (!data()->ea_path && ft_strncmp(line, "EA ", 3) == 0)
	{
		data()->ea_path = path;
		return (true);
	}
	return (false);
}

bool	handle_floor(char *line, char *colors)
{
	uint32_t	alpha;
	char		**floor;
	int			j;

	alpha = 255;
	if (data()->floor == -1 && !ft_strncmp(line, "F ", 2)
		&& word_count(colors, ',') == 3)
	{
		floor = gc_split_char(colors, ',');
		j = 0;
		while (j < word_count(colors, ','))
		{
			if (ft_atoi(floor[j]) > 255 || ft_atoi(floor[j]) < 0)
				return (false);
			j++;
		}
		data()->floor = pack_rgba((uint32_t)ft_atoi(floor[0]),
			(uint32_t)ft_atoi(floor[1]),
			(uint32_t)ft_atoi(floor[2]), alpha);
		return (true);
	}
	return (false);
}
