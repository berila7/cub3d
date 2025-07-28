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
	return (element == WALL || element == EMPTY 
		|| player_char(element)	|| element == ' ');
}

void	count_elements(t_data *data, char element)
{
	if (player_char(element))
		data->player_count++;
}

bool	valid_line(t_data *data, char *line)
{
	int		i;

	i = 0;
	data->height++;
	while (line[i])
	{
		if (!valid_char(line[i]))
			return (false);
		count_elements(data, line[i]);
		i++;
	}
	return (true);
}
