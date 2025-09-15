/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 12:54:14 by mberila           #+#    #+#             */
/*   Updated: 2025/09/15 20:14:48 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	make_frame_path(int index, char path[128])
{
    char	*prefix = "animation/frame_";
    char	*suffix = ".png";
    int		p = 0;
    int		k = 0;

    while (prefix[k])
        path[p++] = prefix[k++];

    if (index == 0)
        path[p++] = '0';
    else
    {
        char tmp[16];
        int  t = 0;   
        int  n = index;

        while (n > 0)
        {
            tmp[t++] = (char)('0' + (n % 10));
            n /= 10;
        }
        while (t--)
            path[p++] = tmp[t];
    }
    k = 0;
    while (suffix[k])
        path[p++] = suffix[k++];
    path[p] = '\0';
}

int load_weapon(void)
{
    data()->gun_frame_count = 0;
    data()->gun_current_frame = 0;
    data()->gun_fps = 26.0;
    data()->gun_last_time = mlx_get_time();

    for (int i = 0; i < GUN_MAX_FRAMES; ++i)
    {
        char path[128];
        make_frame_path(i, path);
	
        mlx_texture_t *tex = mlx_load_png(path);
        if (!tex)
        {
            if (i == 0)
                return (fprintf(stderr, "Failed to load weapon texture: %s\n", path), -1);
            break;
        }
        data()->gun_texs[i] = tex;

        mlx_image_t *img = mlx_texture_to_image(data()->mlx, tex);
        if (!img)
        {
            mlx_delete_texture(tex);
            data()->gun_texs[i] = NULL;
            if (i == 0)
                return (fprintf(stderr, "Failed to convert weapon texture to image: %s\n", path), -1);
            break;
        }

        int x = (int)((WINDOW_W - (int)img->width) / 2);
        int y = (int)(WINDOW_H - (int)img->height);
        int32_t inst = mlx_image_to_window(data()->mlx, img, x, y);
        if (inst < 0)
        {
            mlx_delete_image(data()->mlx, img);
            mlx_delete_texture(tex);
            data()->gun_texs[i] = NULL;
            if (i == 0)
                return (fprintf(stderr, "Failed to put weapon image to window: %s\n", path), -1);
            break;
        }

        data()->gun_imgs[i] = img;
        data()->gun_insts[i] = inst;
        mlx_set_instance_depth(&img->instances[inst], 1);
        img->instances[inst].enabled = false;

        data()->gun_frame_count++;
    }

    if (data()->gun_frame_count <= 0)
        return -1;

    int cur = 0;
    data()->gun_current_frame = cur;
    data()->gun_imgs[cur]->instances[data()->gun_insts[cur]].enabled = true;

    data()->gun_tex  = data()->gun_texs[cur];
    data()->gun_img  = data()->gun_imgs[cur];
    data()->gun_inst = data()->gun_insts[cur];

    if (data()->w_img && data()->w_img->count > 0)
        mlx_set_instance_depth(&data()->w_img->instances[0], 0);
    return 0;
}

void update_weapon_animation(void)
{
    if (data()->gun_frame_count <= 1)
        return;

    double now = mlx_get_time();
    static double acc = 0.0;
    acc += (now - data()->gun_last_time);
    data()->gun_last_time = now;

    double frame_dt;
    if (data()->gun_fps > 0) {
        frame_dt = 1.0 / data()->gun_fps;
    } else {
        frame_dt = 1.0 / 12.0;
    }
    while (acc >= frame_dt)
    {
        int prev = data()->gun_current_frame;
        data()->gun_imgs[prev]->instances[data()->gun_insts[prev]].enabled = false;

        data()->gun_current_frame = (data()->gun_current_frame + 1) % data()->gun_frame_count;

        int cur = data()->gun_current_frame;
        data()->gun_imgs[cur]->instances[data()->gun_insts[cur]].enabled = true;

        data()->gun_tex  = data()->gun_texs[cur];
        data()->gun_img  = data()->gun_imgs[cur];
        data()->gun_inst = data()->gun_insts[cur];

        acc -= frame_dt;
    }
}

void render_weapon(void)
{
    if (data()->gun_frame_count <= 0) return;

    int x = (int)((WINDOW_W - (int)data()->gun_imgs[data()->gun_current_frame]->width) / 2);
    int y = (int)(WINDOW_H - (int)data()->gun_imgs[data()->gun_current_frame]->height);

    for (int i = 0; i < data()->gun_frame_count; ++i)
    {
        data()->gun_imgs[i]->instances[data()->gun_insts[i]].x = x;
        data()->gun_imgs[i]->instances[data()->gun_insts[i]].y = y;
        mlx_set_instance_depth(&data()->gun_imgs[i]->instances[data()->gun_insts[i]], 1);
    }
    if (data()->w_img && data()->w_img->count > 0)
        mlx_set_instance_depth(&data()->w_img->instances[0], 0);
}
