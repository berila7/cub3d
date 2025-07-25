#include "cub3d.h"

int	main(int ac, char **av)
{
	t_data	*data;
	t_gcnode	*gc;
	t_texture	*current;

	data = malloc(sizeof(t_data));
	data->texture = NULL;
	gc = NULL;
	data->gc = gc;
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
		current = data->texture;
		while (current)
		{
			printf("Direction: %s\n", current->direction);
			printf("path: %s\n", current->path);
			printf("fd: %d\n", current->fd);
			current = current->next;
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
