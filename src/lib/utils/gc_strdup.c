/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:05:28 by anachat           #+#    #+#             */
/*   Updated: 2025/07/28 14:18:06 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*gc_strdup(char *src)
{
	size_t	len;
	char	*p_src;

	if (!src)
		return (NULL);
	len = ft_strlen(src) + 1;
	p_src = gc_malloc(sizeof(char) * len);
	ft_strlcpy(p_src, src, len);
	return (p_src);
}
