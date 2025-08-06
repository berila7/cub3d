#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>
# include "../src/lib/gnl/get_next_line.h"
# include "../src/lib/MLX42/include/MLX42/MLX42.h"

# define MAX_DOUBLE 1.7976931348623157e+308

# define P_NORTH 'N'
# define P_SOUTH 'S'
# define P_EAST 'E'
# define P_WEST 'W'
# define EMPTY '0'
# define WALL '1'

// # define WINDOW_W 2000
// # define WINDOW_H 1000
// # define TILE_SIZE 100
# define FOV_ANGLE 60 

# define WINDOW_W 1000
# define WINDOW_H 500
# define TILE_SIZE 40
# define M_SPEED 1.8
# define R_SPEED 0.08

typedef struct s_data		t_data;
typedef struct s_texture	t_texture;
typedef struct s_gcnode		t_gcnode;
typedef struct s_player		t_player;
typedef struct s_point		t_point;
typedef struct s_ray		t_ray;

struct s_texture
{
	int			fd;
	char		*direction;
	char		*path;
	t_texture	*next;
};

struct s_gcnode
{
	void		*ptr;
	t_gcnode	*next;
};

struct s_player
{
	int		rotation_inp;
	int		move_inp;
	double	angle;
	double	x;
	double	y;
};

struct s_ray
{
	double	angle;
	double	dist;
	t_point	*hit;
	bool	is_down;
	bool	is_right;
};

struct s_point
{
	double	x;
	double	y;
};

struct s_data
{
	int			height;
	int			width;
	int			map_fd;
	int			player_count;
	int			player_x;
	int			player_y;
	int			num_rays;
	mlx_t		*mlx;
	double		fov_angle;
	t_player	*player;
	mlx_image_t	*w_img;
	t_ray		*rays;
	// char	*no_path;
	// char	*so_path;
	// char	*we_path;
	// char	*ea_path;
	// char	*floor;
	// char	*ceiling;
	t_texture	*texture;
	char		**map;
};

char		*ft_strrchr(const char *str, int c);
int			read_map(t_data *data, char *filename);
int			ft_strcmp(const char *s1, const char *s2);
int			valid_extension(char *filename);
char		*get_next_line(int fd);
bool		valid_line(t_data *data, char *line);
void		free_map(char **map, int height);
bool		valid_map(t_data *data);
size_t		ft_strlen(const char *str);
char		*ft_strdup(const char *src);
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t n);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
void		find_char_pos(t_data *data, int *pos_x, int *pos_y);
int			check_map(t_data *data);
char		**gc_split(char *s);
char		*gc_strdup(char *src);
int			gc_word_count(char *s);
void		handle_quote_char(char c, char *in_quote_char);
int			find_word_end(char *s, int start, char *in_quote_char);
int			skip_word_end(char *s, int start, char *in_quote_char);
char		*gc_substr(const char *s, unsigned int start, size_t len);
void		*gc_malloc(size_t size);
void		add_txt(t_texture **texutre, t_texture *new_texutre);
t_texture	*new_txt(char *direction, char *path, int fd);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			is_map_line(t_data *data, char *line);
int			is_config(t_data *data, char *line);
bool		player_char(char element);
int			valid_char(char element);
void		count_elements(t_data *data, char element);
char		*parse_line(t_data *data, char *line);
void		gc_free_all(void);
int			equal(char *s1, char *s2);
t_data		*data();
void		gc_free(void *ptr);


// Raycasting:
int			game(void);
bool		has_wall_at(double x, double y);
double		to_rad(double deg);
double		normalize_angle(double angle);
double		get_dist(double ax, double ay, double bx, double by);
t_point		*new_point(double x, double y);
void		draw_pixel(int x, int y, int color);
void		draw_line(t_point *p1, t_point *p2, int color);
void		draw_rect(t_point *start, int w, int h, int color);
void		draw_player(void);
void		draw_rays(void);

bool		find_horiz_hit(t_ray *ray);
bool		in_window(double x, double y);

#endif
