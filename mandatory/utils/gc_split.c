/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:07:55 by anachat           #+#    #+#             */
/*   Updated: 2025/10/10 18:25:56 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
# include "../../lib/libft/libft.h"

int	gc_word_count(char *s)
{
	int		count;
	int		i;
	char	in_quote_char;

	count = 0;
	i = 0;
	in_quote_char = 0;
	while (s && s[i])
	{
		while (s[i] && (s[i] == ' ' || s[i] == '\t') && !in_quote_char)
			i++;
		if (s[i])
		{
			count++;
			i = skip_word_end(s, i, &in_quote_char);
		}
	}
	return (count);
}

static char	**gc_init_split_quoted(char *s, char **result_array)
{
	int		i;
	int		j;
	int		word_start;
	char	in_quote_char;

	i = 0;
	j = 0;
	while (s && s[i])
	{
		in_quote_char = 0;
		while (s[i] && (s[i] == ' ' || s[i] == '\t'))
			i++;
		if (s[i])
		{
			word_start = i;
			i = find_word_end(s, word_start, &in_quote_char);
			result_array[j++] = ft_substr(s, word_start, i - word_start);
		}
	}
	return (result_array);
}

char	**gc_split(char *s)
{
	char	**res;
	int		num_words;

	if (!s)
		return (NULL);
	num_words = gc_word_count(s);
	res = gc_malloc((num_words + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	return (gc_init_split_quoted(s, res));
}
