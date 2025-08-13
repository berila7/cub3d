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
	if (ac == 2)
	{
		if (!read_map(av[1]))
			return (1);
		int i = 0;
		printf("NO: %s\n", data()->no_path);
		printf("SO: %s\n", data()->so_path);
		printf("WE: %s\n", data()->we_path);
		printf("EA: %s\n", data()->ea_path);
		printf("FLOOR: %d, %d, %d\n", data()->floor[0], data()->floor[1], data()->floor[2]);
		printf("CELLING: %d, %d, %d\n", data()->ceiling[0], data()->ceiling[1], data()->ceiling[2]);
		while (i < data()->height)
		{
			printf("line [%d]: [%s]\n", i, data()->map[i]);
			i++;
		}
		printf("Map Rows: [%d]\n", data()->height);
		printf("Map Cols: [%d]\n", data()->width);
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
