/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:13:40 by mberila           #+#    #+#             */
/*   Updated: 2025/07/19 13:13:41 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strdup(const char *src)
{
	size_t	len;
	char	*p_src;

	if (!src)
		return (NULL);
	len = ft_strlen(src) + 1;
	p_src = ft_calloc(sizeof(char), len);
	if (p_src == NULL)
		return (NULL);
	ft_strlcpy(p_src, src, len);
	return (p_src);
}
