/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:44:35 by mberila           #+#    #+#             */
/*   Updated: 2025/09/30 17:26:21 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
			return (printf("Invalid map"), 1);
		if (!check_map())
			printf("\nInvalid walls\n");
		else
		{
			if (!game())
				return (printf("Error in the game\n"), 1);
		}
	}
	else
		printf("Invalid args\n");
	gc_free_all();
	return (0);
}
