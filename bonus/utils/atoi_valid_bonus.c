/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_valid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 10:42:05 by mberila           #+#    #+#             */
/*   Updated: 2025/10/10 21:02:26 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	atoi_valid(const char *str)
{
	long	nb;
	size_t	i;

	if (!str || str[0] == '\0')
		return (-1);
	if (!(*str))
		return (-1);
	i = 0;
	nb = 0;
	while (str[i] == ' ')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		nb = nb * 10 + (str[i++] - '0');
		if (nb > INT_MAX)
			return (-1);
	}
	return (nb);
}
