/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: berila <berila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:13:59 by mberila           #+#    #+#             */
/*   Updated: 2025/09/23 16:42:19 by berila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strrchr(const char *str, int c)
{
	const char	*last_oc;
	char		last;

	last_oc = NULL;
	last = (char)c;
	while (*str != '\0')
	{
		if (*str == last)
			last_oc = str;
		str++;
	}
	if (last == '\0')
		return ((char *)str);
	return ((char *)last_oc);
}
