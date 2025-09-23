#include "cub3d_bonus.h"

bool	handle_ceiling(char *line, char *config)
{
	uint32_t	alpha;
	char		**ceiling;
	int			j;

	alpha = 255;
	if (data()->ceiling == -1 && ft_strncmp(line, "C ", 2) == 0)
	{
		ceiling = gc_split_char(config, ',');
		j = 0;
		while (j < word_count(config, ','))
		{
			if (ft_atoi(ceiling[j]) > 255 || ft_atoi(ceiling[j]) < 0)
				return (false);
			j++;
		}
		data()->ceiling = pack_rgba((uint32_t)ft_atoi(ceiling[0]),
			(uint32_t)ft_atoi(ceiling[1]),
			(uint32_t)ft_atoi(ceiling[2]), alpha);
		return (true);
	}
	return (false);
}

bool	is_config(char *line)
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
		if (line[i] == '1' || line[i] == '0' || line[i] == 'N'
			|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W'
			|| line[i] == ' ')
		{
			i++;
		}
		else
			return (0);
	}
	return (1);
}

int	read_lines(void)
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
			continue ;
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
