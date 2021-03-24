/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 15:34:57 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/24 19:52:16 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_player(void)
{
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
}

static int	my_hook(void)
{
	update_player();
	draw_walls();
	draw_minimap();
	mlx_put_image_to_window(g_cub.mlx, g_cub.win, g_cub.data.img, 0, 0);
	mlx_do_sync(g_cub.mlx);
	// mlx_destroy_image(g_cub.mlx, g_cub.data.img);
	return (1);
}

static int	keypress(int key)
{
	if (key == ESCKEY)
		ft_exit(0);
	if (key < 128)
		g_cub.keys[key] = 1;
	return (0);
}

static int	keyrelease(int key)
{
	if (key < 128)
		g_cub.keys[key] = 0;
	return (0);
}

static int	mousemove(int x, int y)
{
	static int	ex_x;
	static char	flag;

	mlx_mouse_hide();
	if (y)
		mlx_mouse_move(g_cub.win, x, 0);
	if (flag && (flag = 0))
		return (0);
	if (ex_x > x)
		g_cub.keys[MOUSE] = 1;
	else if (ex_x < x)
		g_cub.keys[MOUSE] = -1;
	ex_x = x;
	if (x > g_cub.w || x < 0)
	{
		flag = 1;
		mlx_mouse_move(g_cub.win, g_cub.w / 2, 0);
	}
	return (0);
}

static void	load_texture(t_tex *tex)
{
	if (!(tex->data.img = mlx_xpm_file_to_image(g_cub.mlx, tex->path,
		&tex->width, &tex->height))
	&& (!(tex->data.img = mlx_png_file_to_image(g_cub.mlx, tex->path,
		&tex->width, &tex->height))))
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
	draw_walls();
	draw_minimap();
	save_image_to_bmp_file(g_cub.w, g_cub.h);
	mlx_destroy_image(g_cub.mlx, g_cub.data.img);
	ft_exit(0);
}

void		mlx(void)
{
	t_data	*data;

	data = &g_cub.data;
	ft_bzero(g_cub.keys, 129);
	if (!(g_cub.mlx = mlx_init()))
		ft_error("Connection to graphical system failed", NULL);
	load_textures();
	data->img = mlx_new_image(g_cub.mlx, g_cub.w, g_cub.h);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, \
		&data->line_length, &data->endian);
	if (g_cub.save)
		save_flag();
	g_cub.win = mlx_new_window(g_cub.mlx, g_cub.w, g_cub.h, "cub3D");
	mlx_hook(g_cub.win, 6, 0, &mousemove, NULL);
	mlx_hook(g_cub.win, KEYPRESS, 1L, &keypress, NULL);
	mlx_hook(g_cub.win, KEYRELEASE, 2L, &keyrelease, NULL);
	mlx_hook(g_cub.win, 17, 1L, &ft_exit, NULL);
	mlx_loop_hook(g_cub.mlx, &my_hook, NULL);
	mlx_loop(g_cub.mlx);
}
