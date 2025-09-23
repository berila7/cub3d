#include "cub3d_bonus.h"

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
	if (data()->floor == -1 && ft_strncmp(line, "F ", 2) == 0)
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
