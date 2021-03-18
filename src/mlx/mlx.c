/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 15:34:57 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/18 19:47:08 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_player(void)
{
	if (g_mlx.key[MOVEFWD])
		move_fwd();
	if (g_mlx.key[MOVEBACK])
		move_back();
	if (g_mlx.key[MOVELEFT])
		move_left();
	if (g_mlx.key[MOVERIGHT])
		move_right();
	if (g_mlx.key[ROTLEFT] || g_mlx.key[6] > 0)
	{
		g_mlx.key[6] = 0;
		rotate_left();
	}
	if (g_mlx.key[ROTRIGHT] || g_mlx.key[6] < 0)
	{
		g_mlx.key[6] = 0;
		rotate_right();
	}
}

static void	get_image(void)
{
	g_data.img = mlx_new_image(g_mlx.mlx, g_win.w, g_win.h);
	g_data.addr = mlx_get_data_addr(g_data.img, &g_data.bits_per_pixel,
		&g_data.line_length, &g_data.endian);
	draw_walls();
	draw_minimap();
}

static int	my_hook(void)
{
	update_player();
	get_image();
	mlx_put_image_to_window(g_mlx.mlx, g_win.ptr, g_data.img, 0, 0);
	mlx_destroy_image(g_mlx.mlx, g_data.img);
	return (1);
}

static int	keypress(int key)
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

static int	keyrelease(int key)
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

static int	mousemove(int x, int y)
{
	static int	ex_x;
	static char	flag;

	// mlx_mouse_hide();
	if (y)
		mlx_mouse_move(g_win.ptr, x, 0);
	if (flag && (flag = 0))
		return (0);
	if (ex_x > x)
		g_mlx.key[6] = 1;
	else if (ex_x < x)
		g_mlx.key[6] = -1;
	ex_x = x;
	if (x > g_win.w || x < 0)
	{
		flag = 1;
		mlx_mouse_move(g_win.ptr, g_win.w/2, 0);
	}
	return (0);
}

static void	load_texture(t_tex *tex)
{
	if (!(tex->data.img = mlx_xpm_file_to_image(g_mlx.mlx, tex->path,
		&tex->width, &tex->height)))
		ft_error("Failed to load texture", NULL);
	tex->data.addr = mlx_get_data_addr(tex->data.img, &tex->data.bits_per_pixel,
		&tex->data.line_length, &tex->data.endian);
}

static char	load_textures(void)
{
	load_texture(&g_cub.no);
	load_texture(&g_cub.so);
	load_texture(&g_cub.we);
	load_texture(&g_cub.ea);
	if (g_cub.spr)
		load_texture(&g_cub.s);
	return (1);
}

static void	save_flag(void)
{
	g_data.img = mlx_new_image(g_mlx.mlx, g_win.w, g_win.h);
	g_data.addr = mlx_get_data_addr(g_data.img, &g_data.bits_per_pixel,
		&g_data.line_length, &g_data.endian);
	draw_walls();
	draw_minimap();
	save_image_to_bmp_file(g_win.w, g_win.h);
	mlx_destroy_image(g_mlx.mlx, g_data.img);
	ft_exit(0);
}

void		mlx(void)
{
	g_mlx.key[0] = 0;
	g_mlx.key[1] = 0;
	g_mlx.key[2] = 0;
	g_mlx.key[3] = 0;
	g_mlx.key[4] = 0;
	g_mlx.key[5] = 0;
	g_mlx.key[6] = 0;
	if (!(g_mlx.mlx = mlx_init()))
		ft_error("Connection to graphical system failed", NULL);
	load_textures();
	if (g_cub.save)
		save_flag();
	g_win.ptr = mlx_new_window(g_mlx.mlx, g_win.w, g_win.h, "cub3D");
	mlx_hook(g_win.ptr, 6, 0, &mousemove, NULL);
	mlx_hook(g_win.ptr, KEYPRESS, 1L, &keypress, NULL);
	mlx_hook(g_win.ptr, KEYRELEASE, 2L, &keyrelease, NULL);
	mlx_hook(g_win.ptr, 17, 1L, &ft_exit, NULL);
	mlx_loop_hook(g_mlx.mlx, &my_hook, NULL);
	mlx_loop(g_mlx.mlx);
}
