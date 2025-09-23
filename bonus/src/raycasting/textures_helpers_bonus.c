#include "cub3d_bonus.h"

mlx_texture_t	*load_png_or_die(const char *path)
{
	mlx_texture_t	*t;

	t = mlx_load_png(path);
	if (!t)
	{
		perror("Error: Failed to load texture\n");
		exit(EXIT_FAILURE);
	}
	return (t);
}

int	load_textures(void)
{
	t_data	*d;

	d = data();
	if (!d->no_path || !d->so_path || !d->we_path || !d->ea_path)
	{
		perror("Error: Missing NO/SO/WE/EA texture paths in .cub file\n");
		return (1);
	}
	d->no_tex = load_png_or_die(d->no_path);
	d->so_tex = load_png_or_die(d->so_path);
	d->we_tex = load_png_or_die(d->we_path);
	d->ea_tex = load_png_or_die(d->ea_path);
	return (0);
}

int	map_cell_at_point(double x, double y)
{
	int	fx;
	int	fy;

	fy = (int)(y / TILE_SIZE);
	fx = (int)(x / TILE_SIZE);
	if (fy < 0 || fx < 0 || fy >= data()->height || fx >= data()->width)
		return ('1');
	return (data()->map[fy][fx]);
}

mlx_texture_t	*other_textures(t_ray *ray)
{
	if (ray->was_vert)
	{
		if (ray->is_right)
			return (data()->ea_tex);
		else
			return (data()->we_tex);
	}
	else
	{
		if (ray->is_down)
			return (data()->so_tex);
		else
			return (data()->no_tex);
	}
}

mlx_texture_t	*pick_wall_texture(t_ray *ray)
{
	int		offset_x;
	int		offset_y;
	int		cell;

	offset_x = 0;
	offset_y = 0;
	if (ray->was_vert && !ray->is_right)
		offset_x = 1;
	if (!ray->was_vert && !ray->is_down)
		offset_y = 1;
	cell = map_cell_at_point(ray->hit.x - offset_x, ray->hit.y - offset_y);
	if (cell == DOOR_CLOSED || cell == DOOR_OPEN)
	{
		if (data()->door_tex)
			return (data()->door_tex);
		else
			return (data()->we_tex);
	}
	return (other_textures(ray));
}
