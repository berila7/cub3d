#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include "../src/lib/gnl/get_next_line.h"

typedef struct s_data t_data;
typedef struct s_texture t_texture;
typedef struct s_gcnode	t_gcnode;

# define P_NORTH 'N'
# define P_SOUTH 'S'
# define P_EAST 'E'
# define P_WEST 'W'
# define EMPTY '0'
# define WALL '1'

struct s_texture
{
	int			fd;
	char		*direction;
	char		*path;
	t_texture	*next;
};

struct s_gcnode
{
	void			*ptr;
	t_gcnode		*next;
};

struct s_data
{
	int			height;
	int			width;
	int			map_fd;
	int			player_count;
	int			player_x;
	int			player_y;
	// char	*no_path;
	// char	*so_path;
	// char	*we_path;
	// char	*ea_path;
	// char	*floor;
	// char	*ceiling;
	t_texture	*texture;
	t_gcnode	*gc;
	char		**map;
};

char	*ft_strrchr(const char *str, int c);
int		read_map(t_data *data, char *filename);
int		ft_strcmp(const char *s1, const char *s2);
int		valid_extension(char *filename);
char	*get_next_line(int fd);
bool	valid_line(t_data *data, char *line);
void	free_map(char **map, int height);
bool	valid_map(t_data *data);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *src);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	find_char_pos(t_data *data, int *pos_x, int *pos_y);
int		check_map(t_data *data);
char	**gc_split(t_gcnode **gc, char *s);
char	*gc_strdup(t_gcnode **gc, char *src);
int		gc_word_count(char *s);
void	handle_quote_char(char c, char *in_quote_char);
int		find_word_end(char *s, int start, char *in_quote_char);
int		skip_word_end(char *s, int start, char *in_quote_char);
char	*gc_substr(t_gcnode **gc, const char *s, unsigned int start, size_t len);
void	*gc_malloc(t_gcnode **gc, size_t size);
void	add_txt(t_texture **texutre, t_texture *new_texutre);
t_texture	*new_txt(char *direction, char *path, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		is_map_line(t_data *data, char *line);
int		is_config(t_data *data, char *line);
bool	player_char(char element);
int		valid_char(char element);
void	count_elements(t_data *data, char element);
char	*parse_line(t_data *data, char *line);

#endif
