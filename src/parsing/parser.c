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

int	valid_char(char element)
{
	return (element == WALL || element == EMPTY || element == P_NORTH
		|| element == P_WEST || element == P_EAST || element == P_SOUTH
		|| element == ' ');
}

void	count_elements(t_data *data, char element)
{
	if (element == P_NORTH || element == P_WEST
		|| element == P_SOUTH || element == P_EAST)
	{
		data->player_count++;
	}
}

int	map_validation(t_data *data)
{
	int		i;
	size_t	j;

	i = 0;
	data->player_count = 0;
	while (i < data->height)
	{
		j = 0;
		printf("map line: [%s]\n", data->map[i]);
		while (j < ft_strlen(data->map[i]))
		{
			if (!valid_char(data->map[i][j]))
			{
				return (0);
			}
			count_elements(data, data->map[i][j]);
			j++;
		}
		i++;
	}
	if (data->player_count > 1)
		return (0);
	return (1);
}
