/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 15:34:57 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/09 01:16:02 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int		get_image(void)
{
	g_data.img = mlx_new_image(g_mlx.mlx, g_win.w, g_win.h);
	g_data.addr = mlx_get_data_addr(g_data.img, &g_data.bits_per_pixel, &g_data.line_length, &g_data.endian);
	ray();
	draw_minimap();
	mlx_put_image_to_window(g_mlx.mlx, g_win.ptr, g_data.img, 0, 0);
	mlx_destroy_image(g_mlx.mlx, g_data.img);
	return (1);
}

int		keypress(int key)
{
	if (key == 53)
		ft_exit(0);
	if (key == 13) // W
	{
		if (g_map[(int)g_plr.posY][(int)(g_plr.posX + g_plr.dirX * MOVESPEED * COLLISION)] == '0')
			g_plr.posX += g_plr.dirX * MOVESPEED;
		if (g_map[(int)(g_plr.posY + g_plr.dirY * MOVESPEED * COLLISION)][(int)g_plr.posX] == '0')
			g_plr.posY += g_plr.dirY * MOVESPEED;
	}
	if (key == 1) // S
	{
		if (g_map[(int)g_plr.posY][(int)(g_plr.posX - g_plr.dirX * MOVESPEED * COLLISION)] == '0')
			g_plr.posX -= g_plr.dirX * MOVESPEED;
		if (g_map[(int)(g_plr.posY - g_plr.dirY * MOVESPEED * COLLISION)][(int)g_plr.posX] == '0')
			g_plr.posY -= g_plr.dirY * MOVESPEED;
	}
	if (key == 0) // A
	{
		g_plr.posX += g_plr.dirY * MOVESPEED;
		g_plr.posY -= g_plr.dirX * MOVESPEED;
	}
	if (key == 2) // D
	{
		g_plr.posX -= g_plr.dirY * MOVESPEED;
		g_plr.posY += g_plr.dirX * MOVESPEED;
	}
	if (key == 123) // <-
	{
		double	oldPlaneX = g_plr.planeX;
		double	oldDirX = g_plr.dirX;
		g_plr.dirX = g_plr.dirX * cos(-ROTSPEED / 2) -
			g_plr.dirY * sin(-ROTSPEED / 2);
		g_plr.dirY = oldDirX * sin(-ROTSPEED / 2) +
			g_plr.dirY * cos(-ROTSPEED / 2);
		g_plr.planeX = g_plr.planeX * cos(-ROTSPEED / 2)
			- g_plr.planeY * sin(-ROTSPEED / 2);
		g_plr.planeY = oldPlaneX * sin(-ROTSPEED / 2) +
			g_plr.planeY * cos(-ROTSPEED / 2);
	}
	if (key == 124) // ->
	{
		double	oldPlaneY = g_plr.planeY;
		double	oldDirY = g_plr.dirY;
		g_plr.dirY = g_plr.dirY * cos(-ROTSPEED / 2) -
			g_plr.dirX * sin(-ROTSPEED / 2);
		g_plr.dirX = oldDirY * sin(-ROTSPEED / 2) +
			g_plr.dirX * cos(-ROTSPEED / 2);
		g_plr.planeY = g_plr.planeY * cos(-ROTSPEED / 2)
			- g_plr.planeX * sin(-ROTSPEED / 2);
		g_plr.planeX = oldPlaneY * sin(-ROTSPEED / 2) +
			g_plr.planeX * cos(-ROTSPEED / 2);
	}
	return (0);
}

static char	load_textures(void)
{
	int	width;
	int	height;
	t_data d;

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
	return (1);
}

void	mlx(void)
{
	g_mlx.mlx = mlx_init();
	g_win.ptr = mlx_new_window(g_mlx.mlx, g_win.w, g_win.h, "cub3D");
	load_textures();
	// test_scene();
	mlx_hook(g_win.ptr, 2, 1L, &keypress, 0);
	mlx_hook(g_win.ptr, 17, 1L, &ft_exit, 0);
	mlx_loop_hook(g_mlx.mlx, &get_image, 0);
	mlx_loop(g_mlx.mlx);
}
