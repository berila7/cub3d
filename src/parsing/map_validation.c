#include "cub3d.h"

char	**copy_map(t_data *data)
{
	int			i;
	char	**copy;

	copy = malloc(sizeof(char *) * data->height + 1);
	if (!copy)
		return (NULL);
	i = 0;
	while (i < data->height)
	{
		copy[i] = ft_strdup(data->map[i]);
		if (!copy[i])
		{
			free_map(copy, i);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int	player_char(char element)
{
	return ( element == P_NORTH|| element == P_WEST 
	|| element == P_EAST || element == P_SOUTH);
}

void	find_char_pos(t_data *data, int *pos_x, int *pos_y)
{
	int			i;
	size_t		j;

	i = 0;
	while (i < data->height)
	{
		j = 0;
		while (j < ft_strlen(data->map[i]))
		{
			if (player_char(data->map[i][j]))
			{
				*pos_x = j;
				*pos_y = i;
				return ;
			}
			j++;
		}
		i++;
	}
	
}

void	flood_fill(char **map, int x, int y, t_data *data)
{
	if (x < 0 || x >= data->width || y < 0 || y >= data->height
		|| map[y][x] == WALL || map[y][x] == 'F')
		return ;
	map[y][x] = 'F';
	flood_fill(map, x + 1, y, data);
	flood_fill(map, x - 1, y, data);
	flood_fill(map, x, y + 1, data);
	flood_fill(map, x, y - 1, data);
}

int	check_walls(t_data *data, char **map)
{
	int	i;

	i = 0;
	while (i < (int)ft_strlen(map[0]) - 1)
	{
		if (map[0][i] != '1' && map[0][i] != ' ')
		{
			printf("top line: [%c]\n", map[0][i]);
			printf("the problem at top [%d][%d]\nor\n",0, i);
			return (0);
		}
		i++;
	}
	i = 0;
	while (i < (int)ft_strlen(map[data->height - 1]))
	{
		if (map[data->height - 1][i] != '1' && map[data->height - 1][i] != ' ')
		{
			printf("bottom line: [%c]\n", map[data->height - 1][i]);
			printf("the problem at bottom [%d][%d]\nor\n",data->height - 1, i);
			return (0);
		}
		i++;
	}
	i = 0;
	while (i < data->height)
	{
		if (map[i][0] != '1' && map[i][0] != ' ' && map[i][0] != '\0')
		{
			printf("left line: [%c]\n", map[i][0]);
			printf("the problem at left [%d][%d]\n",i, 0);
			return (0);
		}
		else if (map[i][ft_strlen(map[i]) - 1] != '1')
		{
			printf("right line: [%c]\n", map[i][ft_strlen(map[i]) - 1]);
			printf("the problem at right [%d][%lu]\n",i, ft_strlen(map[i]) - 1);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_map(t_data *data)
{
	int		player_x;
	int		player_y;
	char	**temp_map;

	temp_map = copy_map(data);
	if (!temp_map)
		return (0);
	find_char_pos(data, &player_x, &player_y);
	flood_fill(temp_map, player_x, player_y, data);
	int i = 0;
	while (i < data->height)
	{
		printf("tmp map: %s\n", temp_map[i]);
		i++;
	}
	if (!check_walls(data, temp_map))
		return (0);
	return (1);
}