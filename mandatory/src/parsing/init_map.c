/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:32:59 by mberila           #+#    #+#             */
/*   Updated: 2025/10/09 17:01:53 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	allconfig(void)
{
	if (!data()->no_path || !data()->so_path || data()->floor == -1
		|| !data()->we_path || !data()->ea_path || data()->ceiling == -1)
		return (false);
	return (true);
}

bool	valid_map(void)
{
	char	*line;
	int		map_started;

	map_started = 0;
	line = get_next_line(data()->map_fd);
	while (line)
	{
		if (is_map_line(line) && !map_started)
			map_started = 1;
		if (!map_started)
		{
			if (!is_config(line))
				return (false);
			line = get_next_line(data()->map_fd);
			continue ;
		}
		if (!valid_line(parse_line(line)))
			return (false);
		if (data()->width < (int)ft_strlen(line))
			data()->width = ft_strlen(line);
		line = get_next_line(data()->map_fd);
	}
	if (!data()->height || data()->player_count != 1 || !allconfig())
		return (false);
	return (true);
}

int	init_map(char *filename)
{
	data()->map = NULL;
	if (!valid_extension(filename))
		return (0);
	data()->height = 0;
	data()->width = 0;
	data()->floor = -1;
	data()->ceiling = -1;
	if (!valid_map())
		return (0);
	data()->map = gc_malloc(sizeof(char *) * (data()->height + 1));
	return (1);
}

char	*parse_line(char *line)
{
	char	*result;
	int		len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n' && line[0] != '\n')
		line[len - 1] = '\0';
	result = ft_strdup(line);
	return (result);
}

char	*pad_line(char *line)
{
	int		len;
	char	*pad;
	int		i;

	len = ft_strlen(line);
	if (len >= data()->width)
		return (line);
	pad = gc_malloc(data()->width + 1);
	i = 0;
	while (i < len)
	{
		pad[i] = line[i];
		i++;
	}
	while (i < data()->width)
		pad[i++] = ' ';
	pad[i] = '\0';
	return (pad);
}
