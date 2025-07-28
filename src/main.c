#include "cub3d.h"

// void	f(void) { system("leaks cub3D"); }

int	main(int ac, char **av)
{
	t_data	*data;
	// t_texture	*current;
	data = NULL;
	data = gc_malloc(sizeof(t_data));
	if (!data)
		return (1);
	data->texture = NULL;
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
		// current = data->texture;
		// while (current)
		// {
		// 	printf("Direction: %s\n", current->direction);
		// 	printf("path: %s\n", current->path);
		// 	printf("fd: %d\n", current->fd);
		// 	current = current->next;
		// }
		if (!check_map(data))
			printf("\nInvalid walls\n");
		else
			printf("\nvalid walls\n");		
	}
	else
		printf("invalid args");
	gc_free_all();
	return (0);
}
