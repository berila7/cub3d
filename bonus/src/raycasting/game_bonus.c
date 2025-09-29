/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:58:49 by anachat           #+#    #+#             */
/*   Updated: 2025/09/29 14:27:24 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	update_player(void)
{
	t_point		new_p;
	t_player	*pl;

	pl = data()->player;
	new_p.x = pl->x
		+ cos(pl->angle) * pl->move_forward * M_SPEED
		+ cos(pl->angle + M_PI_2) * pl->move_side * M_SPEED;
	new_p.y = pl->y
		+ sin(pl->angle) * pl->move_forward * M_SPEED
		+ sin(pl->angle + M_PI_2) * pl->move_side * M_SPEED;
	if (can_move(new_p.x, pl->y))
		pl->x = new_p.x;
	if (can_move(pl->x, new_p.y))
		pl->y = new_p.y;
	pl->angle = normalize_angle(pl->angle + (pl->rotation_inp * R_SPEED));
}

void	render_game(void)
{
	if (data()->w_img)
		mlx_delete_image(data()->mlx, data()->w_img);
	data()->w_img = mlx_new_image(data()->mlx, WINDOW_W, WINDOW_H);
	mlx_image_to_window(data()->mlx, data()->w_img, 0, 0);
	mlx_set_instance_depth(data()->w_img->instances, 0);
	draw_rect(new_point(0, 0), WINDOW_W, WINDOW_H / 2, data()->ceiling);
	draw_rect(new_point(0, WINDOW_H / 2),
		WINDOW_W, WINDOW_H / 2, data()->floor);
	update_player();
	cast_rays();
	render_minimap();
}

void	game_loop(void *param)
{
	mlx_t	*mlx;
	bool	input_changed;

	mlx = (mlx_t *)param;
	input_changed = game_input(mlx);
	if (input_changed)
		render_game();
	else
		update_animations();
}

int	game(void)
{
	data()->mlx = mlx_init(WINDOW_W, WINDOW_H, "Test Cub3d", false);
	if (!data()->mlx)
		return (perror("Failed to init mlx"), 1);
	if (load_textures() != 0 || load_door_texture() != 0)
	{
		perror("Failed to load textures. Check your .cub paths.\n");
		mlx_terminate(data()->mlx);
		return (0);
	}
	data()->player = gc_malloc(sizeof(t_player));
	data()->num_rays = WINDOW_W / RAY_THICKNESS;
	data()->fov_angle = to_rad(FOV_ANGLE);
	data()->rays = gc_malloc(sizeof(t_ray) * data()->num_rays);
	get_pl_pos(data()->map);
	data()->player->x = data()->player_x * TILE_SIZE + (TILE_SIZE / 2);
	data()->player->y = data()->player_y * TILE_SIZE + (TILE_SIZE / 2);
	render_game();
	if (!load_weapon())
		return (0);
	mlx_loop_hook(data()->mlx, game_loop, data()->mlx);
	mlx_loop(data()->mlx);
	mlx_terminate(data()->mlx);
	return (1);
}
