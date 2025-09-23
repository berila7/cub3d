/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: berila <berila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:02:42 by mberila           #+#    #+#             */
/*   Updated: 2025/09/23 16:43:33 by berila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		new_remainder = NULL;
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
			return (NULL);
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = 0;
		if (!remainder)
			remainder = ft_strdup("");
		tmp_remainder = remainder;
		remainder = ft_strjoin(tmp_remainder, buffer);
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
		return (NULL);
	buffer = gc_malloc((BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	line = get_line(fd, remainder, buffer);
	if (!line)
		return (NULL);
	remainder = configure_line(line);
	return (line);
}
