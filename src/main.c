#include "cub3d.h"

int	main(int ac, char **av)
{
	(void)ac;
	if (ac == 2)
	{
		if (!valid_extension(av[1]))
			printf("invalid filename");
		else
			printf("valid filename");
	}
	else
		printf("invalid args");
	return (0);
}
