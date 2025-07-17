#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "../src/lib/gnl/get_next_line.h"

typedef struct s_data t_data;

struct s_data
{
	int	height;
	int	width;
	char	**map;
};


char	*ft_strrchr(const char *str, int c);
int	ft_strcmp(const char *s1, const char *s2);
int	valid_extension(char *filename);
char	*get_next_line(int fd);
int	count_lines(char *filename);

#endif
