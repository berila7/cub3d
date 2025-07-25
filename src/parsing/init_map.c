#include "cub3d.h"

int	count_lines(t_data *data, char *filename)
{
	int		fd;
	int		lines;
	char	*line;
	int		map_started;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	lines = 0;
	map_started = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (is_map_line(data, line) && !map_started)
			map_started = 1;
		if (map_started)
			lines++;
		free(line);
		line = get_next_line(fd);
	}
	if (lines == 0)
		return (close(fd), 0);
	close(fd);
	return (lines);
}

int	init_map(t_data *data, char *filename)
{	
	if (!valid_extension(filename))
		return (0);
	data->height = count_lines(data, filename);
	data->width = 0;
	if (data->height == 0)
		return (0);
	data->map = malloc(sizeof(char *) * data->height + 1);
	if (!data->map)
		return (0);
	return (1);
}

char	*parse_line(t_data *data, char *line)
{
	char	*result;
	int		len;

	(void)data;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n' && line[0] != '\n')
		line[len - 1] = '\0';
	result = ft_strdup(line);
	return (result);
}

int	is_config(t_data *data, char *line)
{
	int		i;

	i = 0;
	(void)data;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (0);
	if (ft_strncmp(&line[i], "NO ", 3) == 0 || ft_strncmp(&line[i], "SO ", 3) == 0
		|| ft_strncmp(&line[i], "WE ", 3) == 0 || ft_strncmp(&line[i], "EA ", 3) == 0
		|| ft_strncmp(&line[i], "F ", 2) == 0 || ft_strncmp(&line[i], "C ", 2) == 0)
	{
		return (1);
	}
	return (0);
}

int	is_map_line(t_data *data, char *line)
{
	int	i;

	i = 0;
	(void)data;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (0);
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == '1' || line[i] == '0' || line[i] == 'N' || 
			line[i] == 'S' || line[i] == 'E' || line[i] == 'W' || 
			line[i] == ' ')
		{
			i++;
		}
		else
			return (0);
	}
	return (1);
}

int	handle_configs(t_data *data, t_texture **texture, char *line)
{
	int		fd;
	char	**splited;
	char	*parsed_line; 

	parsed_line = parse_line(data, line);
	if (!is_config(data, line) && ft_strcmp(line, "\n"))
		return (0);
	if (gc_word_count(parsed_line) > 2)
		return (0);
	if (ft_strcmp(parsed_line, "\n"))
	{
		splited = gc_split(&data->gc, parsed_line);
		fd = open(splited[1], O_RDONLY);
		add_txt(texture, new_txt(splited[0], splited[1], fd));
	}
	return (1);
}

int	read_lines(t_data *data, int fd)
{
	int		i;
	char	*line;
	char	*raw_line;
	int		map_started;
	t_texture	*texture;

	i = 0;
	map_started = 0;
	texture = NULL;
	raw_line = get_next_line(fd);
	while (raw_line)
	{
		if (is_map_line(data, raw_line) && !map_started)
			map_started = 1;
		if (!map_started)
		{
			if (!handle_configs(data, &texture, raw_line))
				return (0);
			free(raw_line);
			raw_line = get_next_line(fd);
			continue;
		}
		line = parse_line(data, raw_line);
		if (!line)
		{
			free(raw_line);
			return (0);
		}
		if (data->width < (int)ft_strlen(line))
			data->width = ft_strlen(line);
		data->map[i] = line;
		i++;
		raw_line = get_next_line(fd);
	}
	data->map[i] = NULL;
	data->texture = texture;
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
	// if (!check_configs(data))
	// 	return (0);
	return (close(fd), 1);
}
