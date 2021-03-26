/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 15:34:57 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/26 16:53:39 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	my_hook(void)
{
	update_player();
	draw_walls();
	draw_minimap();
	mlx_put_image_to_window(g_cub.mlx, g_cub.win, g_cub.data.img, 0, 0);
	mlx_do_sync(g_cub.mlx);
	return (1);
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

static void	load_textures(void)
{
	load_texture(&g_cub.no);
	load_texture(&g_cub.so);
	load_texture(&g_cub.we);
	load_texture(&g_cub.ea);
	if (g_cub.spr)
		load_texture(&g_cub.s);
}

static void	save_flag(void)
{
	draw_walls();
	draw_minimap();
	save_image_to_bmp_file();
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
	mlx_mouse_hide();
	mlx_mouse_move(g_cub.win, 0, 0);
	mlx_hook(g_cub.win, 6, 0, &mousemove, NULL);
	mlx_hook(g_cub.win, KEYPRESS, 1L, &keypress, NULL);
	mlx_hook(g_cub.win, KEYRELEASE, 2L, &keyrelease, NULL);
	mlx_hook(g_cub.win, 17, 1L, &ft_exit, NULL);
	mlx_loop_hook(g_cub.mlx, &my_hook, NULL);
	mlx_loop(g_cub.mlx);
}
