#include "cub3d.h"

int	main(int ac, char **av)
{
	(void)ac;
	if (ac == 2)
	{
		printf("%d", count_lines(av[1]));
	}
	else
		printf("invalid args");
	return (0);
}
