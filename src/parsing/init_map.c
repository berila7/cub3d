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
		if (is_map_line(line))
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

char	*parse_line(t_data *data, char *line, int *count)
{
	char	*result;
	int		i;
	int		len;

	i = 0;
	(void)data;
	(*count)++;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	result = ft_strdup(line);
	return (result);
}

int	is_config(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
	{
		return (1);
	}
	return (0);
}

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
		{
			i++;
			if (line[i] == '1')
				return (1);
		}
		else if (line[0] == '1')
			return (1);
		i++;
	}
	return (0);
}

int	read_lines(t_data *data, int fd)
{
	int		i;
	char	*line;
	char	*raw_line;
	int		map_started;
	int 	count;

	i = 0;
	data->width = 0;
	map_started = 0;
	count = 0;
	raw_line = get_next_line(fd);
	while (raw_line)
	{
		line = parse_line(data, raw_line, &count);
		if (!line)
			return (0);
		if (is_map_line(line))
			map_started = 1;
		if (map_started)
		{
			if (data->width < (int)ft_strlen(line))
				data->width = ft_strlen(line);
			data->map[i] = line;
			if (!data->map[i])
			{
				free_map(data->map, i);
				return (0);
			}
			i++;
		}
		raw_line = get_next_line(fd);
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
