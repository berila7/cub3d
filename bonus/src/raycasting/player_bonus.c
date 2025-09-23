/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: berila <berila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 12:54:14 by mberila           #+#    #+#             */
/*   Updated: 2025/09/23 16:28:26 by berila           ###   ########.fr       */
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
	free(frame_str);
	free(tmp);
	return (path);
}

void	load_image(char *path, int i)
{
	mlx_image_t	*tmp;

	data()->gun_tex[i] = mlx_load_png(path);
	if (!data()->gun_tex[i])
	{
		perror("Failed to load weapon texture\n");
		exit(EXIT_FAILURE);
	}
	tmp = mlx_texture_to_image(data()->mlx, data()->gun_tex[i]);
	if (!tmp)
	{
		mlx_delete_texture(data()->gun_tex[i]);
		data()->gun_tex[i] = NULL;
		perror("Failed to convert weapon texture to image\n");
		exit(EXIT_FAILURE);
	}
	data()->gun_img[i] = tmp;
}

static void	load_single_frame(int i)
{
	char		*gun_path;
	int32_t		tmp;
	uint32_t	x;
	uint32_t	y;

	gun_path = create_frame_path(i);
	load_image(gun_path, i);
	x = ((WINDOW_W - data()->gun_img[i]->width) / 2);
	y = (WINDOW_H - data()->gun_img[i]->height);
	tmp = mlx_image_to_window(data()->mlx,
			data()->gun_img[i], x, y);
	if (tmp < 0)
	{
		perror("Failed to put weapon image to window\n");
		exit(EXIT_FAILURE);
	}
	data()->gun_inst[i] = tmp;
	if (i > 0)
		data()->gun_img[i]->enabled = false;
	free(gun_path);
}

void	load_weapon(void)
{
	int	i;

	i = 0;
	while (i < FRAMES)
	{
		load_single_frame(i);
		i++;
	}
	data()->current_frame = 0;
	data()->animation_timer = 0;
	data()->space_was_dow = false;
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
