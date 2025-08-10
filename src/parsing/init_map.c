#include "cub3d.h"

bool	valid_map()
{
	char	*line;
	int		map_started;

	map_started = 0;
	line = get_next_line(data()->map_fd);
	while (line)
	{
		if (is_map_line(line) && !map_started)
			map_started = 1;
		if (map_started)
		{
			if (!valid_line(parse_line(line)))
				return (false);
			if (data()->width < (int)ft_strlen(line))
				data()->width = ft_strlen(line);
		}
		line = get_next_line(data()->map_fd);
	}
	if (!data()->height || data()->player_count != 1)
		return (false);
	return (true);
}

int	init_map(char *filename)
{	
	data()->map = NULL;
	if (!valid_extension(filename))
		return (0);
	data()->height = 0;
	data()->width = 0;
	if (!valid_map())
		return (0);
	data()->map = gc_malloc(sizeof(char *) * (data()->height + 1));
	return (1);
}

char	*parse_line(char *line)
{
	char	*result;
	int		len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n' && line[0] != '\n')
		line[len - 1] = '\0';
	result = gc_strdup(line);
	return (result);
}

char	*pad_line(char *line)
{
    int		len;
    char	*pad;
    int		i;

    len = ft_strlen(line);
    if (len >= data()->width)
        return (line);
    pad = gc_malloc(data()->width + 1);
    i = 0;
    while (i < len)
    {
        pad[i] = line[i];
        i++;
    }
    while (i < data()->width)
        pad[i++] = ' ';
    pad[i] = '\0';
    return (pad);
}

int	is_config(char *line)
{
	int		i;

	i = 0;
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

int	is_map_line(char *line)
{
	int	i;

	i = 0;
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

int	handle_configs(t_texture **texture, char *line)
{
	int		fd;
	char	**splited;
	char	*parsed_line; 

	parsed_line = parse_line(line);
	if (!is_config(line) && ft_strcmp(line, "\n"))
		return (0);
	if (gc_word_count(parsed_line) > 2)
		return (0);
	if (ft_strcmp(parsed_line, "\n"))
	{
		splited = gc_split(parsed_line);
		fd = open(splited[1], O_RDONLY);
		add_txt(texture, new_txt(splited[0], splited[1], fd));
	}
	return (1);
}

int	read_lines()
{
	int		i;
	char	*line;
	char	*raw_line;
	int		map_started;
	t_texture	*texture;

	i = 0;
	map_started = 0;
	texture = NULL;
	raw_line = get_next_line(data()->map_fd);
	while (raw_line)
	{
		if (is_map_line(raw_line) && !map_started)
			map_started = 1;
		if (!map_started)
		{
			if (!handle_configs(&texture, raw_line))
				return (0);
			free(raw_line);
			raw_line = get_next_line(data()->map_fd);
			continue;
		}
		line = parse_line(raw_line);
		if (!line)
		{
			free(raw_line);
			return (0);
		}
		line = pad_line(line);
		data()->map[i] = line;
		free(raw_line);
		i++;
		raw_line = get_next_line(data()->map_fd);
	}
	data()->map[i] = NULL;
	data()->texture = texture;
	return (1);
}


int	read_map(char *filename)
{
	data()->map_fd = open(filename, O_RDONLY);
	if (data()->map_fd < 0)
		return (0);
	if (!init_map(filename))
		return (0);
	close(data()->map_fd);
	data()->map_fd = open(filename, O_RDONLY);
	if (data()->map_fd < 0)
		return (0);
	if (!read_lines())
	{
		close(data()->map_fd);
		return (0);
	}
	return (close(data()->map_fd), 1);
}
