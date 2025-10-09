/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anachat <anachat@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:44:35 by mberila           #+#    #+#             */
/*   Updated: 2025/10/09 17:57:25 by anachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_exit(void)
{
	delet_text();
	mlx_terminate(data()->mlx);
	gc_free_all();
	exit(EXIT_FAILURE);
}

void	ft_error(char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
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
			return (gc_free_all(), ft_error("Invalid map"), 1);
		if (!check_map())
			return (gc_free_all(), ft_error("Invalid walls"), 1);
		else if (WINDOW_H > 1440 || WINDOW_W > 2560)
			return (gc_free_all(), ft_error("Window size is big"), 1);
		else
			game();
	}
	else
		return (gc_free_all(), ft_error("Invalid args"), 1);
	gc_free_all();
	return (0);
}
