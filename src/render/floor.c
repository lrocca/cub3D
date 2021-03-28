/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 18:49:23 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/28 22:31:50 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	draw_floor(void)
{
	float rayDirX0;
	float rayDirY0;
	float rayDirX1;
	float rayDirY1;
	int p;
	float posZ;
	float rowDistance;
	float floorStepX;
	float floorStepY;
	float floorX;
	float floorY;

	t_tex *floor;
	floor = &g_cub.floor;
	t_tex *ceiling;
	ceiling = &g_cub.ceiling;

	int y = 0;
	while (y < g_cub.h)
	{
		rayDirX0 = g_cub.plr.dirx - g_cub.plr.planex;
		rayDirY0 = g_cub.plr.diry - g_cub.plr.planey;
		rayDirX1 = g_cub.plr.dirx + g_cub.plr.planex;
		rayDirY1 = g_cub.plr.diry + g_cub.plr.planey;

		p = y - g_cub.h / 2;

		posZ = 0.5 * g_cub.h;

		rowDistance = posZ / p;

		floorStepX = rowDistance * (rayDirX1 - rayDirX0) / g_cub.w;
		floorStepY = rowDistance * (rayDirY1 - rayDirY0) / g_cub.w;

		floorX = g_cub.plr.posx + rowDistance * rayDirX0;
		floorY = g_cub.plr.posy + rowDistance * rayDirY0;

		int cellX;
		int cellY;
		int tx;
		int ty;
		int color;

		int x = 0;
		while (x < g_cub.w)
		{
			cellX = (int)(floorX);
			cellY = (int)(floorY);
			if (g_cub.opt & FLOOR)
			{
				tx = (int)(floor->width * (floorX - cellX)) & (floor->width - 1);
				ty = (int)(floor->height * (floorY - cellY)) & (floor->height - 1);
				color = ((int *)floor->data.addr)[floor->width * ty + tx];
				my_mlx_pixel_put(&g_cub.data, x, y, color);
			}
			if (g_cub.opt & CEILING)
			{
				tx = (int)(ceiling->width * (floorX - cellX)) & (ceiling->width - 1);
				ty = (int)(ceiling->height * (floorY - cellY)) & (ceiling->height - 1);
				color = ((int *)ceiling->data.addr)[ceiling->width * ty + tx];
				my_mlx_pixel_put(&g_cub.data, x, g_cub.h - y - 1, color);
			}
			floorX += floorStepX;
			floorY += floorStepY;
			x++;
		}
		y++;
	}
}
