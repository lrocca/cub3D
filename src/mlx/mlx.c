/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 15:34:57 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/13 19:40:02 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_player(void)
{
	if (g_mlx.key[MOVEFWD])
		move_fwd();
	if (g_mlx.key[MOVEBACK])
		move_back();
	if (g_mlx.key[MOVELEFT])
		move_left();
	if (g_mlx.key[MOVERIGHT])
		move_right();
	if (g_mlx.key[ROTLEFT])
		rotate_left();
	if (g_mlx.key[ROTRIGHT])
		rotate_right();
}

int		get_image(void)
{
	update_player();
	g_data.img = mlx_new_image(g_mlx.mlx, g_win.w, g_win.h);
	g_data.addr = mlx_get_data_addr(g_data.img, &g_data.bits_per_pixel,
									&g_data.line_length, &g_data.endian);
	ray();
	draw_minimap();
	mlx_put_image_to_window(g_mlx.mlx, g_win.ptr, g_data.img, 0, 0);
	mlx_destroy_image(g_mlx.mlx, g_data.img);
	return (1);
}

int		keypress(int key)
{
	if (key == ESCKEY)
		ft_exit(0);
	if (key == WKEY)
		g_mlx.key[MOVEFWD] = 1;
	if (key == SKEY)
		g_mlx.key[MOVEBACK] = 1;
	if (key == AKEY)
		g_mlx.key[MOVELEFT] = 1;
	if (key == DKEY)
		g_mlx.key[MOVERIGHT] = 1;
	if (key == LEFTARROW)
		g_mlx.key[ROTLEFT] = 1;
	if (key == RIGHTARROW)
		g_mlx.key[ROTRIGHT] = 1;
	return (0);
}

int		keyrelease(int key)
{
	if (key == WKEY)
		g_mlx.key[0] = 0;
	if (key == SKEY)
		g_mlx.key[1] = 0;
	if (key == AKEY)
		g_mlx.key[2] = 0;
	if (key == DKEY)
		g_mlx.key[3] = 0;
	if (key == LEFTARROW)
		g_mlx.key[4] = 0;
	if (key == RIGHTARROW)
		g_mlx.key[5] = 0;
	return (0);
}

static char	load_textures(void)
{
	int		width;
	int		height;
	t_data	d;

	if (!(g_tex.NO = mlx_xpm_file_to_image(g_mlx.mlx, g_cub.NO, &width, &height)))
		ft_error("Failed to load 'NO' texture", NULL);
	d.addr = mlx_get_data_addr(g_tex.NO, &d.bits_per_pixel, &d.line_length, &d.endian);
	g_tex.NO = d.addr;
	if (!(g_tex.SO = mlx_xpm_file_to_image(g_mlx.mlx, g_cub.SO, &width, &height)))
		ft_error("Failed to load 'SO' texture", NULL);
	d.addr = mlx_get_data_addr(g_tex.SO, &d.bits_per_pixel, &d.line_length, &d.endian);
	g_tex.SO = d.addr;
	if (!(g_tex.WE = mlx_xpm_file_to_image(g_mlx.mlx, g_cub.WE, &width, &height)))
		ft_error("Failed to load 'WE' texture", NULL);
	d.addr = mlx_get_data_addr(g_tex.WE, &d.bits_per_pixel, &d.line_length, &d.endian);
	g_tex.WE = d.addr;
	if (!(g_tex.EA = mlx_xpm_file_to_image(g_mlx.mlx, g_cub.EA, &width, &height)))
		ft_error("Failed to load 'EA' texture", NULL);
	d.addr = mlx_get_data_addr(g_tex.EA, &d.bits_per_pixel, &d.line_length, &d.endian);
	g_tex.EA = d.addr;
	if (!(g_tex.S = mlx_xpm_file_to_image(g_mlx.mlx, g_cub.S, &width, &height)))
		ft_error("Failed to load 'S' texture", NULL);
	d.addr = mlx_get_data_addr(g_tex.S, &d.bits_per_pixel, &d.line_length, &d.endian);
	g_tex.S = d.addr;
	return (1);
}

static void	save_flag(void)
{
	g_data.img = mlx_new_image(g_mlx.mlx, g_win.w, g_win.h);
	g_data.addr = mlx_get_data_addr(g_data.img, &g_data.bits_per_pixel,
									&g_data.line_length, &g_data.endian);
	ray();
	draw_minimap();
	save_image_to_bmp_file(g_win.w, g_win.h);
	ft_exit(0);
}

void	mlx(void)
{
	g_mlx.key[0] = 0;
	g_mlx.key[1] = 0;
	g_mlx.key[2] = 0;
	g_mlx.key[3] = 0;
	g_mlx.key[4] = 0;
	g_mlx.key[5] = 0;
	g_mlx.mlx = mlx_init();
	load_textures();
	if (g_cub.save)
		save_flag();
	g_win.ptr = mlx_new_window(g_mlx.mlx, g_win.w, g_win.h, "cub3D");
	mlx_hook(g_win.ptr, KEYPRESS, 1L, &keypress, 0);
	mlx_hook(g_win.ptr, KEYRELEASE, 2L, &keyrelease, 0);
	mlx_hook(g_win.ptr, 17, 1L, &ft_exit, 0);
	mlx_loop_hook(g_mlx.mlx, &get_image, 0);
	mlx_loop(g_mlx.mlx);
}
