// #include "cub3d.h"
#include "cub3d.h"


int	valid_extension(char *filename)
{
	char	*extension;

	extension = ft_strrchr(filename, '.');
	if (ft_strcmp(extension, ".cub") != 0)
		return (0);
	return (1);
}

int	vertical_walls(t_data *data)
{
	
}

