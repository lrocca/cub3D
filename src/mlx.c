/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 15:34:57 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/04 18:32:11 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"
#define ROTSPEED 0.2
#define MOVESPEED 0.5

// <- 123
// -> 124

void	get_image(void)
{
	if (g_data.img)
		mlx_destroy_image(g_mlx.mlx, g_data.img);
	g_data.img = mlx_new_image(g_mlx.mlx, g_win.w, g_win.h);
	g_data.addr = mlx_get_data_addr(g_data.img, &g_data.bits_per_pixel, &g_data.line_length, &g_data.endian);
	ray();
	draw_minimap();
	mlx_put_image_to_window(g_mlx.mlx, g_win.ptr, g_data.img, 0, 0);
}

int		keypress(int key)
{
	if (key == 53)
		ft_exit(0);
	else if (key == 13) // W
	{
		// printf("%f\n", g_plr.posY);
		// if (g_map[(int)(g_plr.posY) - 1][(int)g_plr.posX] != '1')
		// 	g_plr.posY -= 1;
		g_plr.posX += g_plr.dirX * MOVESPEED;
		g_plr.posY += g_plr.dirY * MOVESPEED;
	}
	else if (key == 1) // S
	{
		if (g_map[(int)(g_plr.posY) + 1][(int)g_plr.posX] != '1')
			g_plr.posY += 1;
	}
	else if (key == 0) // A
	{
		if (g_map[(int)g_plr.posY][(int)(g_plr.posX) - 1] != '1')
			g_plr.posX -= 1;
	}
	else if (key == 2) // D
	{
		if (g_map[(int)g_plr.posY][(int)(g_plr.posX) + 1] != '1')
			g_plr.posX += 1;
	}
	else if (key == 123) // <-
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
	else if (key == 124) // ->
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
	get_image();
	return (0);
}

void	mlx(void)
{
	g_mlx.mlx = mlx_init();
	g_win.ptr = mlx_new_window(g_mlx.mlx, g_win.w, g_win.h, "cub3D");
	// test_scene();
	// g_plr.dirX = -1, g_plr.dirY = 0; //initial direction vector
	g_plr.planeX = 0.66, g_plr.planeY = 0;
	get_image();
	mlx_hook(g_win.ptr, 2, 1L, &keypress, 0);
	mlx_hook(g_win.ptr, 17, 1L, &ft_exit, 0);
	mlx_loop(g_mlx.mlx);
}
