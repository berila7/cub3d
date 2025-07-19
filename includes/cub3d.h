#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "../src/lib/gnl/get_next_line.h"

typedef struct s_data t_data;

# define P_NORTH 'N'
# define P_SOUTH 'S'
# define P_EAST 'E'
# define P_WEST 'W'
# define EMPTY '0'
# define WALL '1'

struct s_data
{
	int	height;
	int	player_count;
	int	width;
	char	**map;
};

char	*ft_strrchr(const char *str, int c);
int		read_map(t_data *data, char *filename);
int		ft_strcmp(const char *s1, const char *s2);
int		valid_extension(char *filename);
char	*get_next_line(int fd);
int		count_lines(char *filename);
void	free_map(char **map, int height);
int		map_validation(t_data *data);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *src);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	find_char_pos(t_data *data, int *pos_x, int *pos_y);
int		check_map(t_data *data);

#endif
