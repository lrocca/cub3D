/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 19:18:39 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/28 22:15:49 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		keypress(int key)
{
	static char	music = 1;

	if (key == ESCKEY)
		ft_exit(0);
	if (g_cub.audio && key == MKEY && music)
	{
		music = 0;
		pauseAudio();
	}
	else if (g_cub.audio && key == MKEY && !music)
	{
		music = 1;
		unpauseAudio();
	}
	if (key < 128)
		g_cub.keys[key] = 1;
	return (0);
}

int		keyrelease(int key)
{
	if (key < 128)
		g_cub.keys[key] = 0;
	return (0);
}

void	update_mouse(void)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	mlx_mouse_hide();
	mlx_mouse_get_pos(g_cub.win, &x, &y);
	if (x > g_cub.w / 2)
		g_cub.keys[MOUSE] = -1;
	else if (x < g_cub.w / 2)
		g_cub.keys[MOUSE] = 1;
	mlx_mouse_move(g_cub.win, g_cub.w / 2, g_cub.h / 2);
}

void	update_player(void)
{
	update_mouse();
	if (g_cub.keys[WKEY])
		move_fwd();
	if (g_cub.keys[SKEY])
		move_back();
	if (g_cub.keys[AKEY])
		move_left();
	if (g_cub.keys[DKEY])
		move_right();
	if (g_cub.keys[LEFTARROW] || g_cub.keys[MOUSE] > 0)
	{
		g_cub.keys[MOUSE] = 0;
		rotate_left();
	}
	if (g_cub.keys[RIGHTARROW] || g_cub.keys[MOUSE] < 0)
	{
		g_cub.keys[MOUSE] = 0;
		rotate_right();
	}
	g_cub.keys[MOUSE] = 0;
}

void	load_texture(t_tex *tex)
{
	if (!(tex->data.img = mlx_xpm_file_to_image(g_cub.mlx, tex->path,
		&tex->width, &tex->height))
	&& (!(tex->data.img = mlx_png_file_to_image(g_cub.mlx, tex->path,
		&tex->width, &tex->height))))
		ft_error("Failed to load texture", NULL);
	tex->data.addr = mlx_get_data_addr(tex->data.img, &tex->data.bits_per_pixel,
		&tex->data.line_length, &tex->data.endian);
}
