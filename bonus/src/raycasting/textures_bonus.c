#include "cub3d_bonus.h"

static uint32_t pack_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return ((uint32_t)r << 24) | ((uint32_t)g << 16) | ((uint32_t)b << 8) | (uint32_t)a;
}

static mlx_texture_t *load_png(const char *path)
{
	mlx_texture_t *t = mlx_load_png(path);
	if (!t)
	{
		perror("Error: Failed to load texture: %s\n");
		exit(EXIT_FAILURE);
	}
	return t;
}

int load_textures(void)
{
	t_data *d = data();
	if (!d->no_path || !d->so_path || !d->we_path || !d->ea_path)
	{
		perror("Error: Missing NO/SO/WE/EA texture paths in .cub file\n");
		return 1;
	}
	d->no_tex = load_png(d->no_path);
	d->so_tex = load_png(d->so_path);
	d->we_tex = load_png(d->we_path);
	d->ea_tex = load_png(d->ea_path);
	return 0;
}

static int map_cell_at_point(double x, double y)
{
	int fx = (int)(x / TILE_SIZE);
	int fy = (int)(y / TILE_SIZE);
	if (fy < 0 || fx < 0 || fy >= data()->height || fx >= data()->width)
		return '1';
	return data()->map[fy][fx];
}

static mlx_texture_t *pick_wall_texture(const t_ray *ray)
{
	t_data *d = data();
	int offset_x = 0;
	int offset_y = 0;
	
	if (ray->was_vert && !ray->is_right)
		offset_x = 1;
	if (!ray->was_vert && !ray->is_down)
		offset_y = 1;
	
	int cell = map_cell_at_point(ray->hit.x - offset_x, ray->hit.y - offset_y);
	
	if (cell == DOOR_CLOSED || cell == DOOR_OPEN)
	{
		if (d->door_tex)
			return d->door_tex;
		else
			return d->we_tex;
	}

	if (ray->was_vert)
	{
		if (ray->is_right)
			return d->ea_tex;
		else
			return d->we_tex;
	}
	else
	{
		if (ray->is_down)
			return d->so_tex;
		else
			return d->no_tex;
	}
}

static uint32_t sample_texel_rgba(mlx_texture_t *tex, int x, int y)
{
	const uint8_t *p = tex->pixels + (y * tex->width + x) * tex->bytes_per_pixel;
	return pack_rgba(p[0], p[1], p[2], p[3]);
}

static int compute_tex_x(const t_ray *ray, mlx_texture_t *tex)
{
	double offset;

	if (ray->was_vert)
		offset = fmod(ray->hit.y, (double)TILE_SIZE);
	else
		offset = fmod(ray->hit.x, (double)TILE_SIZE);

	int tx = (int)(offset / (double)TILE_SIZE * (double)tex->width);

	if (ray->was_vert && !ray->is_right)
		tx = (int)tex->width - 1 - tx;
	else if (!ray->was_vert && ray->is_down)
		tx = (int)tex->width - 1 - tx;

	if (tx < 0)
		tx = 0;
	if (tx >= (int)tex->width)
		tx = (int)tex->width - 1;

	return tx;
}


void render_textured_column(const t_ray *ray, int screen_x, double line_h)
{
	int y;
	int tx;

	if (screen_x < 0 || screen_x >= WINDOW_W) return;

	mlx_texture_t *tex = pick_wall_texture(ray);
	if (!tex) return;

	double wall_top_f = (WINDOW_H / 2.0) - (line_h / 2.0);
	double wall_bot_f = wall_top_f + line_h;

	int wall_top = (int)wall_top_f;
	int wall_bottom = (int)wall_bot_f;
	if (wall_top < 0) wall_top = 0;
	if (wall_bottom > WINDOW_H) wall_bottom = WINDOW_H;

	y = 0;
	while (y < wall_top)
	{
		draw_pixel(screen_x, y, data()->ceiling);
		y++;
	}
	tx = compute_tex_x(ray, tex);
	y = wall_top;
	while (++y < wall_bottom)
	{
		double dist_from_top = (double)y - wall_top_f;      // 0 .. line_h
		double v = dist_from_top / line_h;                  // 0 .. 1
		int ty = (int)(v * (double)tex->height);
		if (ty < 0) ty = 0;
		if (ty >= (int)tex->height) ty = (int)tex->height - 1;

		int color = (int)sample_texel_rgba(tex, tx, ty);
		draw_pixel(screen_x, y, color);
	}
	y = wall_bottom;
	while (++y < WINDOW_H)
		draw_pixel(screen_x, y, data()->floor);
}

int load_door_texture(void)
{
	char *door_path = "textures/door.png";
	data()->door_tex = mlx_load_png(door_path);
	if (!data()->door_tex)
	{
		perror("Error: Failed to load texture: %s\n");
		return (1);
	}
	return 0;
}