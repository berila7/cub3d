#include "cub3d.h"

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (ac == 2)
	{
		if (!read_map(data, av[1]))
			return (1);
		int i = 0;
		while (i < data->height)
		{
			printf("line [%d]: %s", i, data->map[i]);
			i++;
		}
	}
	else
		printf("invalid args");
	return (0);
}
