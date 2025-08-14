#include "cub3d.h"

bool	allconfig()
{
	if (!data()->no_path || !data()->so_path || data()->floor == -1
		|| !data()->we_path || !data()->ea_path || data()->ceiling == -1)
		return (false);
	return (true);
}

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
		if(!map_started)
		{
			if (!is_config(line))
				return (false);
			line = get_next_line(data()->map_fd);
			continue ;
		}
		if (!valid_line(parse_line(line)))
			return (false);
		if (data()->width < (int)ft_strlen(line))
			data()->width = ft_strlen(line);
		line = get_next_line(data()->map_fd);
	}
	if (!data()->height || data()->player_count != 1 || !allconfig())
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
	data()->floor = -1;
	data()->ceiling = -1;
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
int	get_color(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

bool handle_redir(char *line, char *config)
{

	if (!data()->no_path && ft_strncmp(line, "NO ", 3) == 0)
	{
		data()->no_path = config;
		return (true);
	}
	if (!data()->so_path && ft_strncmp(line, "SO ", 3) == 0)
	{
		data()->so_path = config;
		return (true);
	}
	if (!data()->we_path && ft_strncmp(line, "WE ", 3) == 0)
	{
		data()->we_path = config;
		return (true);
	}
	if (!data()->ea_path && ft_strncmp(line, "EA ", 3) == 0)
	{
		data()->ea_path = config;
		return (true);
	}
	return (false);
}

bool	handle_floor(char *line, char *config)
{
	printf("line: %s\n", line);
	if (data()->floor == -1 && ft_strncmp(line, "F ", 2) == 0)
	{
		char **floor = gc_split_char(config, ',');
		int j = 0;
		while (j < word_count(config, ','))
		{
			if (ft_atoi(floor[j]) > 255 || ft_atoi(floor[j]) < 0)
			{
				printf("FLOOR COLORS: %d\n", ft_atoi(floor[j]));
				return (false);
			}
			j++;
		}
		data()->floor = get_color(ft_atoi(floor[0]), ft_atoi(floor[1]), ft_atoi(floor[2]), 255);
		return (true);
	}
	return (false);
}

bool	handle_ceiling(char *line, char *config)
{
	if (data()->ceiling == -1 && ft_strncmp(line, "C ", 2) == 0)
	{
		char **ceiling = gc_split_char(config, ',');
		int j = 0;
		while (j < word_count(config, ','))
		{
			if (ft_atoi(ceiling[j]) > 255 || ft_atoi(ceiling[j]) < 0)
				return (false);
			j++;
		}
		data()->ceiling = get_color(ft_atoi(ceiling[0]), ft_atoi(ceiling[1]), ft_atoi(ceiling[2]), 255);
		return (true);
	}
	return (false);
}

bool		is_config(char *line)
{
	int		i;
	char	*newline;
	char	**splited;

	i = 0;
	newline = parse_line(line);
	while (newline[i] && (newline[i] == ' ' || newline[i] == '\t'))
		i++;
	if (newline[i] == '\0' || newline[i] == '\n')
		return (true);
	splited = gc_split(newline);
	if (gc_word_count(newline) == 2)
	{
		if (handle_redir(&newline[i], splited[1]))
			return (true);
		else if (handle_floor(&newline[i], splited[1]))
			return (true);
		else if (handle_ceiling(&newline[i], splited[1]))
			return (true);
	}
	return (false);
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

int	read_lines()
{
	int		i;
	char	*line;
	char	*raw_line;

	i = 0;
	raw_line = get_next_line(data()->map_fd);
	while (raw_line)
	{
		if (is_map_line(raw_line) && !data()->map_started)
			data()->map_started = 1;
		if (!data()->map_started)
		{
			raw_line = get_next_line(data()->map_fd);
			continue;
		}
		line = parse_line(raw_line);
		if (!line)
			return (0);
		line = pad_line(line);
		data()->map[i] = line;
		i++;
		raw_line = get_next_line(data()->map_fd);
	}
	data()->map[i] = NULL;
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
