#include "cub3d.h"

int	count_lines(char *filename)
{
	int		fd;
	int		lines;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	lines = 0;
	line = get_next_line(fd);
	while (line)
	{
		lines++;
		free(line);
		line = get_next_line(fd);
	}
	if (lines == 0)
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (lines);
}

int	init_map(t_data *data, char *filename)
{	
	if (!valid_extension(filename))
		return (0);
	data->height = count_lines(filename);
	if (data->height == 0)
		return (0);
	data->map = malloc(sizeof(char *) * data->height + 1);
	if (!data->map)
		return (0);
	return (1);
}

char	*parse_line(char *line)
{
	char *result;
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	result = ft_strdup(line);
	return (result);
}

int	read_lines(t_data *data, int fd)
{
	int		i;
	char	*line;

	i = 0;
	data->width = 0;
	while (i < data->height)
	{
		line = parse_line(get_next_line(fd));
 		data->map[i] = line;
		if (data->width < (int)ft_strlen(line))
			data->width = ft_strlen(data->map[i]);
		if (!data->map[i])
		{
			printf("Here [%s]\n", data->map[i]);

			free_map(data->map, i);
			return (0);
		}
		i++;
	}
	data->map[i] = NULL;
	return (1);
}

int	read_map(t_data *data, char *filename)
{
	int fd;
	if (!init_map(data, filename))
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	if (!read_lines(data, fd))
	{
		close (fd);
		return (0);
	}
	close(fd);
	return (1);
}
