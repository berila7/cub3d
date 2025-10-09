/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 12:54:14 by mberila           #+#    #+#             */
/*   Updated: 2025/10/09 15:55:23 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static char	*create_frame_path(int frame_index)
{
	char	*path;
	char	*tmp;
	char	*frame_str;

	frame_str = ft_itoa(frame_index);
	tmp = ft_strjoin("bonus/anim/frame_", frame_str);
	path = ft_strjoin(tmp, ".png");
	gc_free(frame_str);
	gc_free(tmp);
	return (path);
}

int	load_image(char *path, int i)
{
	mlx_image_t	*tmp;

	data()->gun_tex[i] = mlx_load_png(path);
	if (!data()->gun_tex[i])
	{
		ft_error("Failed to load weapon texture");
		return (0);
	}
	tmp = mlx_texture_to_image(data()->mlx, data()->gun_tex[i]);
	if (!tmp)
	{
		ft_error("Failed to convert weapon texture to image");
		return (0);
	}
	data()->gun_img[i] = tmp;
	return (1);
}

static int	load_single_frame(int i)
{
	char		*gun_path;
	uint32_t	x;
	uint32_t	y;

	gun_path = create_frame_path(i);
	if (!load_image(gun_path, i))
		return (0);
	x = ((WINDOW_W - data()->gun_img[i]->width) / 2);
	y = (WINDOW_H - data()->gun_img[i]->height);
	mlx_image_to_window(data()->mlx,
		data()->gun_img[i], x, y);
	if (i > 0)
		data()->gun_img[i]->enabled = false;
	gc_free(gun_path);
	return (1);
}

int	load_weapon(void)
{
	int	i;

	i = 0;
	while (i < FRAMES)
	{
		if (!load_single_frame(i))
			return (0);
		i++;
	}
	data()->current_frame = 0;
	data()->animation_timer = 0;
	data()->open_door = false;
	data()->close_door = false;
	return (1);
}

void	update_animations(void)
{
	data()->animation_timer++;
	if (data()->animation_timer >= ANIMATION_SPEED)
	{
		data()->gun_img[data()->current_frame]->enabled = false;
		data()->current_frame = (data()->current_frame + 1) % FRAMES;
		data()->gun_img[data()->current_frame]->enabled = true;
		data()->animation_timer = 0;
	}
}
