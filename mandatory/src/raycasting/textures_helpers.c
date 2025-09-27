/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 13:51:28 by mberila           #+#    #+#             */
/*   Updated: 2025/09/25 17:33:29 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	pack_rgba(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

mlx_texture_t	*load_png(const char *path)
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
	d->no_tex = load_png(d->no_path);
	d->so_tex = load_png(d->so_path);
	d->we_tex = load_png(d->we_path);
	d->ea_tex = load_png(d->ea_path);
	return (0);
}

mlx_texture_t	*pick_wall_texture(const t_ray *ray)
{
	t_data	*d;

	d = data();
	if (ray->was_vert)
	{
		if (ray->is_right)
			return (d->ea_tex);
		else
			return (d->we_tex);
	}
	else
	{
		if (ray->is_down)
			return (d->so_tex);
		else
			return (d->no_tex);
	}
}

uint32_t	sample_rgba(mlx_texture_t *tex, int x, int y)
{
	uint8_t	*p;

	p = tex->pixels + (y * tex->width + x) * tex->bytes_per_pixel;
	return (pack_rgba(p[0], p[1], p[2], p[3]));
}
