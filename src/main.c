#include "cub3d.h"

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->texture = NULL;
	if (!data)
		return (1);
	if (ac == 2)
	{
		if (!read_map(data, av[1]))
			return (1);
		int i = 0;
		while (i < data->height)
		{
			printf("line [%d]: %s\n", i, data->map[i]);
			i++;
		}
		if (!map_validation(data))
			printf("\nInvalid map\n");
		else
			printf("\nValid map\n");
		
		if (!check_map(data))
			printf("\nInvalid walls\n");
		else
			printf("\nvalid walls\n");
	}
	else
		printf("invalid args");
	return (0);
}
