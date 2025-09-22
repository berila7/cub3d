#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H
#define _GNU_SOURCE
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdint.h>
# include <stdbool.h>
# include <math.h>
# include "../../lib/gnl/get_next_line.h"
# include "../../lib/MLX42/include/MLX42/MLX42.h"

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
# define FRAMES 180

# define MINIMAP_W 160
# define WINDOW_W 1000
# define WINDOW_H 500
# define TILE_SIZE 80
# define M_SPEED 10
# define R_SPEED 0.1
# define RAY_THICKNESS 1
# define ANIMATION_SPEED 2

#define DOOR_CLOSED 'D'
#define DOOR_OPEN   'd'
#define INTERACT_DIST (TILE_SIZE + 20)

typedef struct s_data		t_data;
typedef struct s_texture	t_texture;
typedef struct s_gcnode		t_gcnode;
typedef struct s_player		t_player;
typedef struct s_point		t_point;
typedef struct s_ray		t_ray;
typedef struct s_ray_hit		t_ray_hit;

// struct s_texture
// {
// 	int			fd;
// 	char		*direction;
// 	char		*path;
// 	char		*floor;
// 	char		*celling;
// 	t_texture	*next;
// };

struct s_gcnode
{
	void		*ptr;
	t_gcnode	*next;
};

struct s_ray_hit
{
	double	x;
	double	y;
	double	dist;
};

struct s_player
{
	int		rotation_inp;
	int		move_forward;
	int		move_side;
	double	angle;
	double	x;
	double	y;
};

struct s_point
{
	double	x;
	double	y;
};

struct s_ray
{
	double	angle;
	double	dist;
	t_point	hit;
	bool	was_vert;
	bool	is_down;
	bool	is_right;
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
	int			map_started;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	int			floor;
	int			ceiling;
	char		**map;

	mlx_texture_t *no_tex;
	mlx_texture_t *so_tex;
	mlx_texture_t *we_tex;
	mlx_texture_t *ea_tex;

	mlx_texture_t	*door_tex;
	bool			space_was_dow;

	mlx_texture_t	*gun_tex[FRAMES];
	mlx_image_t		*gun_img[FRAMES];
	int32_t			gun_inst[FRAMES];
	int				current_frame;
	int				animation_timer;

};

char		*ft_strrchr(const char *str, int c);
int			read_map(char *filename);
int			ft_strcmp(const char *s1, const char *s2);
int			valid_extension(char *filename);
char		*get_next_line(int fd);
bool		valid_line(char *line);
void		free_map(char **map, int height);
bool		valid_map();
char		*ft_itoa(int n);
int			ft_atoi(const char *str);
size_t		ft_strlen(const char *str);
char		*ft_strdup(const char *src);
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t n);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
void		find_char_pos(int *pos_x, int *pos_y);
int			check_map();
int			ft_isdigit(int c);
char		**gc_split_char(char *s, char c);
char		**gc_split(char *s);
char		*gc_strdup(char *src);
int			gc_word_count(char *s);
void		handle_quote_char(char c, char *in_quote_char);
int			find_word_end(char *s, int start, char *in_quote_char);
int			skip_word_end(char *s, int start, char *in_quote_char);
char		*gc_substr(const char *s, unsigned int start, size_t len);
void		*gc_malloc(size_t size);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			is_map_line(char *line);
bool		is_config(char *line);
bool		player_char(char element);
int			valid_char(char element);
void		count_elements(char element);
char		*parse_line(char *line);
void		gc_free_all(void);
int			equal(char *s1, char *s2);
t_data		*data();
int			word_count(char *str, char c);
void		*ft_memset(void *b, int c, size_t len);
void		gc_free(void *ptr);

// Raycasting:
int			game(void);
bool		has_wall_at(double x, double y);
double		to_rad(double deg);
double		normalize_angle(double angle);
double		get_dist(double ax, double ay, double bx, double by);
t_point		*create_point(double x, double y);
t_point		new_point(double x, double y);
void		draw_pixel(int x, int y, int color);
void		draw_line(t_point p1, t_point p2, int color);
void		draw_rect(t_point start, int w, int h, int color);
void		draw_player(t_point pos);
void		update_player(void);
void		cast_rays(void);
void		render_minimap();

bool		in_window(double x, double y);
bool		in_map(double x, double y);
bool		can_move(double x, double y);
void		get_pl_pos(char **map);
void		find_hit(t_ray *ray);
void		render_wall_strip(t_ray *ray, double line_x);
void 		render_textured_column(t_ray *ray, int screen_x, double line_h);

int			load_textures(void);
void		load_weapon(void);
void		update_animations(void);
int			load_door_texture(void);

#endif