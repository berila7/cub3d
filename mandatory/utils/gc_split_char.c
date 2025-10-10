/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_split_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 10:30:29 by mberila           #+#    #+#             */
/*   Updated: 2025/10/10 21:10:31 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	word_count(char *str, char c)
{
	int		count;
	int		flag_pnt;
	size_t	i;

	count = 0;
	flag_pnt = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c && flag_pnt == 0)
		{
			flag_pnt = 1;
			count++;
		}
		else if (str[i] == c)
			flag_pnt = 0;
		i++;
	}
	return (count);
}

static char	*fill_word(char *str, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = gc_malloc((end - start + 1) * sizeof(char));
	while (start < end)
	{
		word[i] = str[start];
		i++;
		start++;
	}
	return (word);
}

static char	**init_spl(char *s, char c, char **result)
{
	size_t	i;
	int		j;
	int		s_word;

	i = 0;
	j = 0;
	s_word = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && s_word < 0)
			s_word = i;
		else if ((s[i] == c || i == ft_strlen(s)) && s_word >= 0)
		{
			result[j] = fill_word(s, s_word, i);
			s_word = -1;
			j++;
		}
		i++;
	}
	return (result);
}

char	**gc_split_char(char *s, char c)
{
	char	**res;

	if (!s)
		return (NULL);
	res = gc_malloc((word_count(s, c) + 1) * sizeof(char *));
	return (init_spl(s, c, res));
}
