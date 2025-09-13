/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:13:59 by mberila           #+#    #+#             */
/*   Updated: 2025/07/19 13:14:01 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char *ft_strrchr(const char *str, int c) {
  const char *last_oc;
  char last;

  last_oc = NULL;
  last = (char)c;
  while (*str != '\0') {
    if (*str == last)
      last_oc = str;
    str++;
  }
  if (last == '\0')
    return ((char *)str);
  return ((char *)last_oc);
}
