#include "cub3d_bonus.h"

char	**copy_map()
{
	int			i;
	char	**copy;

	copy = gc_malloc(sizeof(char *) * (data()->height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < data()->height)
	{
		copy[i] = gc_strdup(data()->map[i]);
		if (!copy[i])
			return (NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

bool	player_char(char element)
{
	if ( element == P_NORTH|| element == P_WEST 
	|| element == P_EAST || element == P_SOUTH)
		return (true);
	return (false);
}

void	find_char_pos(int *pos_x, int *pos_y)
{
	int			i;
	size_t		j;

	i = 0;
	while (i < data()->height)
	{
		j = 0;
		while (j < ft_strlen(data()->map[i]))
		{
			if (player_char(data()->map[i][j]))
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

int	check_holes(char **filled_map)
{
	int	height;
	int	width;

	height = 0;
	(void)filled_map;
	while (height < data()->height)
	{
		width = -1;
		while (++width < (int)ft_strlen(data()->map[height]))
		{
			if (!player_char(data()->map[height][width]) 
				&& data()->map[height][width] != '0')
				continue ;
			if (!width || !height || !data()->map[height + 1]
				|| width == ((int)ft_strlen(data()->map[height]) - 1)
				|| data()->map[height][width + 1] == ' ' || data()->map[height][width - 1] == ' '
				|| data()->map[height + 1][width] == ' ' || data()->map[height - 1][width] == ' '
			)
				return (0);
		}
		height++;
	}
	return (1);
}

int	check_map()
{
	int		player_x;
	int		player_y;
	char	**temp_map;

	temp_map = copy_map();
	if (!temp_map)
		return (0);
	find_char_pos(&player_x, &player_y);
	if (!check_holes(temp_map))
		return (0);
	return (1);
}
