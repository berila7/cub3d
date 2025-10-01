/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:35:11 by mberila           #+#    #+#             */
/*   Updated: 2025/10/01 15:53:23 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	delet_images(void)
{
	int	i;

	i = 0;
	if (data()->door_tex)
	{
		mlx_delete_texture(data()->door_tex);
		data()->door_tex = NULL;
	}
	while (i < FRAMES)
	{
		if (data()->gun_tex[i])
		{
			mlx_delete_texture(data()->gun_tex[i]);
			data()->gun_tex[i] = NULL;
		}
		i++;
	}
}

void	delet_text(void)
{
	delet_images();
	if (data()->no_tex)
	{
		mlx_delete_texture(data()->no_tex);
		data()->no_tex = NULL;
	}
	if (data()->ea_tex)
	{
		mlx_delete_texture(data()->ea_tex);
		data()->ea_tex = NULL;
	}
	if (data()->so_tex)
	{
		mlx_delete_texture(data()->so_tex);
		data()->so_tex = NULL;
	}
	if (data()->we_tex)
	{
		mlx_delete_texture(data()->we_tex);
		data()->we_tex = NULL;
	}
}

bool	handle_redir(char *line, char *config)
{
	if (!data()->no_path && ft_strncmp(line, "NO ", 3) == 0)
	{
		data()->no_path = config;
		return (true);
	}
	if (!data()->so_path && ft_strncmp(line, "SO ", 3) == 0)
	{
		data()->so_path = config;
		return (true);
	}
	if (!data()->we_path && ft_strncmp(line, "WE ", 3) == 0)
	{
		data()->we_path = config;
		return (true);
	}
	if (!data()->ea_path && ft_strncmp(line, "EA ", 3) == 0)
	{
		data()->ea_path = config;
		return (true);
	}
	return (false);
}

bool	handle_floor(char *line, char *config)
{
	uint32_t	alpha;
	char		**floor;
	int			j;

	alpha = 255;
	if (data()->floor == -1 && ft_strncmp(line, "F ", 2) == 0
		&& word_count(config, ',') == 3)
	{
		floor = gc_split_char(config, ',');
		j = 0;
		while (j < word_count(config, ','))
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
