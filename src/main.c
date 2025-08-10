#include "cub3d.h"

t_data	**get_data()
{
	static t_data	*data;
	return (&data);
}

t_data	*data()
{
	return (*get_data());
}

// void	f(void) { system("leaks cub3D"); }

int	main(int ac, char **av)
{
	t_data	**game_data;

	game_data = get_data();
	*game_data = gc_malloc(sizeof(t_data));
	data()->texture = NULL;
	if (ac == 2)
	{
		if (!read_map(av[1]))
			return (1);
		int i = 0;
		while (i < data()->height)
		{
			printf("line [%d]: [%s]\n", i, data()->map[i]);
			i++;
		}
		printf("Map Rows: [%d]\n", data()->height);
		printf("Map Cols: [%d]\n", data()->width);
		// current = data->texture;
		// while (current)
		// {
		// 	printf("Direction: %s\n", current->direction);
		// 	printf("path: %s\n", current->path);
		// 	printf("fd: %d\n", current->fd);
		// 	current = current->next;
		// }
		if (!check_map(data()))
			printf("\nInvalid walls\n");
		else
		{
			printf("\nValid walls\n");
			if (game())
				return (printf("Error in the game\n"), 1);
		}
	}
	else
		printf("Invalid args\n");
	gc_free_all();
	return (0);
}
