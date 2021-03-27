/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 18:49:23 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/27 19:30:18 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#define texWidth 64
#define texHeight 64

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

	t_tex *texture;
	texture = &g_cub.floor;

	for (int y = 0; y < g_cub.h; y++)
	{
		// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		rayDirX0 = g_cub.plr.dirx - g_cub.plr.planex;
		rayDirY0 = g_cub.plr.diry - g_cub.plr.planey;
		rayDirX1 = g_cub.plr.dirx + g_cub.plr.planex;
		rayDirY1 = g_cub.plr.diry + g_cub.plr.planey;

		// Current y position compared to the center of the screen (the horizon)
		p = y - g_cub.h / 2;

		// Vertical position of the camera.
		posZ = 0.5 * g_cub.h;

		// Horizontal distance from the camera to the floor for the current row.
		// 0.5 is the z position exactly in the middle between floor and ceiling.
		rowDistance = posZ / p;

		// calculate the real world step vector we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		floorStepX = rowDistance * (rayDirX1 - rayDirX0) / g_cub.w;
		floorStepY = rowDistance * (rayDirY1 - rayDirY0) / g_cub.w;

		// real world coordinates of the leftmost column. This will be updated as we step to the right.
		floorX = g_cub.plr.posx + rowDistance * rayDirX0;
		floorY = g_cub.plr.posy + rowDistance * rayDirY0;

		int cellX;
		int cellY;
		int tx;
		int ty;
		int color;


		for (int x = 0; x < g_cub.w; ++x)
		{
			// the cell coord is simply got from the integer parts of floorX and floorY
			cellX = (int)(floorX);
			cellY = (int)(floorY);

			// get the texture coordinate from the fractional part
			tx = (int)(texture->width * (floorX - cellX)) & (texture->width - 1);
			ty = (int)(texture->height * (floorY - cellY)) & (texture->height - 1);

			floorX += floorStepX;
			floorY += floorStepY;

			// choose texture and draw the pixel

			// floor
			color = ((int *)texture->data.addr)[texture->width * ty + tx];
			// color = (color >> 1) & 8355711; // make a bit darker
			my_mlx_pixel_put(&g_cub.data, x, y, color);

			// //ceiling (symmetrical, at g_cub.h - y - 1 instead of y)
			// color = ((int *)g_cub.no.data.addr)[texture->width * ty + tx];
			// // color = (color >> 1) & 8355711; // make a bit darker
			// my_mlx_pixel_put(&g_cub.data, x, g_cub.h - y - 1, color);
		}
	}
}
