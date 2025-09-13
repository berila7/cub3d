#include "cub3d.h"
#include <stdint.h>

static inline uint32_t pack_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return ((uint32_t)r << 24) | ((uint32_t)g << 16) | ((uint32_t)b << 8) | (uint32_t)a;
}

static mlx_texture_t *load_png_or_die(const char *path)
{
	mlx_texture_t *t = mlx_load_png(path);
	if (!t)
	{
		fprintf(stderr, "Error: Failed to load texture: %s\n", path);
		exit(EXIT_FAILURE);
	}
	return t;
}

int load_textures(void)
{
	t_data *d = data();
	if (!d->no_path || !d->so_path || !d->we_path || !d->ea_path)
	{
		fprintf(stderr, "Error: Missing NO/SO/WE/EA texture paths in .cub file\n");
		return 1;
	}
	d->no_tex = load_png_or_die(d->no_path);
	d->so_tex = load_png_or_die(d->so_path);
	d->we_tex = load_png_or_die(d->we_path);
	d->ea_tex = load_png_or_die(d->ea_path);
	return 0;
}

void unload_textures(void)
{
	t_data *d = data();
	if (d->no_tex) mlx_delete_texture(d->no_tex), d->no_tex = NULL;
	if (d->so_tex) mlx_delete_texture(d->so_tex), d->so_tex = NULL;
	if (d->we_tex) mlx_delete_texture(d->we_tex), d->we_tex = NULL;
	if (d->ea_tex) mlx_delete_texture(d->ea_tex), d->ea_tex = NULL;
}

static inline mlx_texture_t *pick_wall_texture(const t_ray *ray)
{
	t_data *d = data();
	if (ray->was_vert)
		return ray->is_right ? d->ea_tex : d->we_tex;
	else
		return ray->is_down ? d->so_tex : d->no_tex;
}

static inline uint32_t sample_texel_rgba(mlx_texture_t *tex, int x, int y)
{
	const uint8_t *p = tex->pixels + (y * tex->width + x) * tex->bytes_per_pixel;
	return pack_rgba(p[0], p[1], p[2], p[3]); // MLX42 stores RGBA
}

static inline int compute_tex_x(const t_ray *ray, mlx_texture_t *tex)
{
	double offset = ray->was_vert ? fmod(ray->hit.y, (double)TILE_SIZE)
	                              : fmod(ray->hit.x, (double)TILE_SIZE);
	int tx = (int)(offset / (double)TILE_SIZE * (double)tex->width);

	// Flip horizontally to make orientation feel natural.
	if (ray->was_vert && !ray->is_right)
		tx = (int)tex->width - 1 - tx;
	else if (!ray->was_vert && ray->is_down)
		tx = (int)tex->width - 1 - tx;

	if (tx < 0) tx = 0;
	if (tx >= (int)tex->width) tx = (int)tex->width - 1;
	return tx;
}

// Draw one textured vertical column at screen x using the ray result.
void render_textured_column(const t_ray *ray, int screen_x, double line_h)
{
	int y;
	int tx;

	if (screen_x < 0 || screen_x >= WINDOW_W) return;

	mlx_texture_t *tex = pick_wall_texture(ray);
	if (!tex) return;

	// Compute projected wall start/end (float for precision)
	double wall_top_f = (WINDOW_H / 2.0) - (line_h / 2.0);
	double wall_bot_f = wall_top_f + line_h;

	int wall_top = (int)wall_top_f;
	int wall_bottom = (int)wall_bot_f;
	if (wall_top < 0) wall_top = 0;
	if (wall_bottom > WINDOW_H) wall_bottom = WINDOW_H;

	// Ceiling
	y = 0;
	while (y < wall_top)
	{
		draw_pixel(screen_x, y, data()->ceiling);
		y++;
	}

	// Texture x coordinate is constant for this column
	tx = compute_tex_x(ray, tex);

	// Draw wall section
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

	// Floor
	y = wall_bottom;
	while (++y < WINDOW_H)
		draw_pixel(screen_x, y, data()->floor);
}