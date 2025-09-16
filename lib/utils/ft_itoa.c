/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:23:21 by mberila           #+#    #+#             */
/*   Updated: 2025/09/16 14:31:59 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	digits_count(int n)
{
	unsigned int	temp;
	int				len;

	len = 0;
	temp = n;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		temp = -n;
		len++;
	}
	while (temp)
	{
		temp /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*result;
	int				len;
	unsigned int	num;

	len = digits_count(n);
	result = ft_calloc((len + 1), sizeof(char));
	if (!result)
		return (NULL);
	num = n;
	if (n < 0)
		num = -n;
	while (len >= 0 && num != 0)
	{
		len--;
		result[len] = '0' + (num % 10);
		num /= 10;
	}
	if (n < 0)
		result[0] = '-';
	else if (n == 0)
		result[0] = '0';
	return (result);
}
