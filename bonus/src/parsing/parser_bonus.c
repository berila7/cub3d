/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 10:02:17 by mberila           #+#    #+#             */
/*   Updated: 2025/09/22 10:02:51 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	valid_extension(char *filename)
{
	char	*extension;

	extension = ft_strrchr(filename, '.');
	if (ft_strcmp(extension, ".cub") != 0)
		return (0);
	return (1);
}

int	valid_char(char element)
{
	return (element == WALL || element == EMPTY
		|| element == DOOR_CLOSED || element == DOOR_OPEN
		|| player_char(element) || element == ' ');
}

void	count_elements(char element)
{
	if (player_char(element))
		data()->player_count++;
}

bool	valid_line(char *line)
{
	int		i;

	i = 0;
	data()->height++;
	while (line[i])
	{
		if (!valid_char(line[i]))
			return (false);
		count_elements(line[i]);
		i++;
	}
	return (true);
}
