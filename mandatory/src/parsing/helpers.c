#include "cub3d.h"

bool handle_redir(char *line, char *config)
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