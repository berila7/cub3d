/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: berila <berila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 12:54:14 by mberila           #+#    #+#             */
/*   Updated: 2025/09/17 15:52:11 by berila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	load_weapon(void)
{
	int		x;
	int		y;
	char	*gun_path[FRAMES];
	int		i = 0;
	char	*path = "anim/frame_";
	char	*type = ".png";
	char	*tmp;

	while (i < FRAMES)
	{
		tmp = ft_strjoin(path, ft_itoa(i));
		gun_path[i] = ft_strjoin(tmp, type);
		data()->gun_tex[i] = mlx_load_png(gun_path[i]);
		if (!data()->gun_tex[i])
		{
			perror("Failed to load weapon texture\n");
			exit(EXIT_FAILURE);
		}
		data()->gun_img[i] = mlx_texture_to_image(data()->mlx, data()->gun_tex[i]);
		if (!data()->gun_img[i])
		{
			mlx_delete_texture(data()->gun_tex[i]);
			data()->gun_tex[i] = NULL;
			perror("Failed to convert weapon texture to image\n");
			exit(EXIT_FAILURE);
		}
		x = (int)((WINDOW_W - (int)data()->gun_img[i]->width) / 2);
		y = (int)(WINDOW_H - (int)data()->gun_img[i]->height);
		data()->gun_inst[i] = mlx_image_to_window(data()->mlx, data()->gun_img[i], x, y);
		if (data()->gun_inst[i] < 0)
		{
			perror("Failed to put weapon image to window\n");
			exit(EXIT_FAILURE);
		}
		if (i > 0)
			data()->gun_img[i]->enabled = false;
		i++;
	}
	data()->current_frame = 0;
	data()->animation_timer = 0;
	data()->space_was_dow = false;
}

void	update_animations()
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