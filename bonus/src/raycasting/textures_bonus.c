/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:34:57 by mberila           #+#    #+#             */
/*   Updated: 2025/10/01 16:07:10 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

uint32_t	sample_rgba(mlx_texture_t *tex, int x, int y)
{
	uint8_t	*p;

	p = tex->pixels + (y * tex->width + x) * tex->bytes_per_pixel;
	return (pack_rgba(p[0], p[1], p[2], p[3]));
}

static int	compute_tex_x(t_ray *ray, mlx_texture_t *tex)
{
	double	offset;	
	int		tx;

	if (ray->was_vert)
		offset = fmod(ray->hit.y, (double)TILE_SIZE);
	else
		offset = fmod(ray->hit.x, (double)TILE_SIZE);
	tx = (int)((offset / (double)TILE_SIZE) * (double)tex->width);
	if (ray->was_vert && !ray->is_right)
		tx = (int)tex->width - tx;
	else if (!ray->was_vert && ray->is_down)
		tx = (int)tex->width - tx;
	if (tx < 0)
		tx = 0;
	if (tx >= (int)tex->width)
		tx = (int)tex->width - 1;
	return (tx);
}

void	check_boundaries(void)
{
	if (data()->ty < 0)
		data()->ty = 0;
	if (data()->ty >= (int)data()->tex->height)
		data()->ty = (int)data()->tex->height - 1;
}

void	render_textured_column(t_ray *ray, int screen_x, double line_h)
{
	if (screen_x < 0 || screen_x >= WINDOW_W)
		return ;
	data()->tex = pick_wall_texture(ray);
	if (!data()->tex)
		return ;
	data()->wall_top_f = (WINDOW_H / 2.0) - (line_h / 2.0);
	data()->wall_bot_f = data()->wall_top_f + line_h;
	data()->wall_top = (int)data()->wall_top_f;
	data()->wall_bottom = (int)data()->wall_bot_f;
	if (data()->wall_top < 0)
		data()->wall_top = 0;
	if (data()->wall_bottom > WINDOW_H)
		data()->wall_bottom = WINDOW_H;
	data()->tx = compute_tex_x(ray, data()->tex);
	data()->y = data()->wall_top - 1;
	while (++data()->y < data()->wall_bottom)
	{
		data()->dist_from_top = (double)data()->y - data()->wall_top_f;
		data()->wall_yp = data()->dist_from_top / line_h;
		data()->ty = (int)(data()->wall_yp * (double)data()->tex->height);
		check_boundaries();
		data()->color = (int)sample_rgba(data()->tex, data()->tx, data()->ty);
		if ((data()->color & 0xFF) != 0)
			draw_pixel(screen_x, data()->y, data()->color);
	}
}

int	load_door_texture(void)
{
	char	*door_path;

	door_path = "textures/door.png";
	data()->door_tex = mlx_load_png(door_path);
	if (!data()->door_tex)
	{
		perror("Error: Failed to load texture: %s\n");
		return (0);
	}
	return (1);
}
