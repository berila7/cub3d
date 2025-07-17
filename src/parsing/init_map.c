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
	return (1);
}
int	read_map(t_data *data, char *filename)
{
	if (!init_map(data, filename))
		return (0);
	return (1);
}
