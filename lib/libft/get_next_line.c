/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:02:42 by mberila           #+#    #+#             */
/*   Updated: 2025/10/10 20:03:51 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*configure_line(char *line)
{
	char	*new_remainder;
	ssize_t	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == 0 || line[1] == 0)
		return (NULL);
	new_remainder = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (*new_remainder == 0)
	{
		gc_free(new_remainder);
		new_remainder = NULL;
	}
	line[i + 1] = 0;
	return (new_remainder);
}

static char	*get_line(int fd, char *remainder, char *buffer)
{
	ssize_t		bytes_read;
	char		*tmp_remainder;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			gc_free(remainder);
			return (NULL);
		}
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = 0;
		if (!remainder)
			remainder = ft_strdup("");
		tmp_remainder = remainder;
		remainder = ft_strjoin(tmp_remainder, buffer);
		gc_free(tmp_remainder);
		tmp_remainder = NULL;
		if (find_new_line(buffer) != -1)
			break ;
	}
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;
	char		*buffer;

	buffer = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		gc_free(remainder);
		gc_free(buffer);
		remainder = NULL;
		buffer = NULL;
		return (NULL);
	}
	buffer = (char *)gc_malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	line = get_line(fd, remainder, buffer);
	gc_free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	remainder = configure_line(line);
	return (line);
}
