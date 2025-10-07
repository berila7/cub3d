/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:38:07 by mberila           #+#    #+#             */
/*   Updated: 2025/10/07 18:14:54 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_exit(void)
{
	delet_text();
	mlx_terminate(data()->mlx);
	exit(EXIT_FAILURE);
}

t_data	**get_data(void)
{
	static t_data	*data;

	return (&data);
}

t_data	*data(void)
{
	return (*get_data());
}

int	main(int ac, char **av)
{
	t_data	**game_data;

	game_data = get_data();
	*game_data = gc_malloc(sizeof(t_data));
	if (ac == 2)
	{
		if (!read_map(av[1]))
			return (gc_free_all(), printf("Error\nInvalid map\n"), 1);
		if (!check_map())
			printf("Error\nInvalid walls\n");
		else
		{
			if (!game())
				return (printf("Error\n game failed\n"), 1);
		}
	}
	else
		printf("Error\nInvalid args\n");
	gc_free_all();
	return (0);
}
