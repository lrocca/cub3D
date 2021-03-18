/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 18:29:03 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/18 18:54:40 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define SCALE	16
#define COLOR	0xEEF0F2
#define PADDING	12

void	draw_position(void)
{
	int	offsetX = (g_win.w - g_cub.x * SCALE) / 2;
	int	offsetY = -(SCALE / PADDING);
	int e = 0;

	while (e < SCALE / 4)
	{
		my_mlx_pixel_put(&g_data, g_cub.plr.posX * SCALE + e + offsetX, g_cub.plr.posY * SCALE + offsetY, COLOR);
		my_mlx_pixel_put(&g_data, g_cub.plr.posX * SCALE - e + offsetX, g_cub.plr.posY * SCALE + offsetY, COLOR);
		my_mlx_pixel_put(&g_data, g_cub.plr.posX * SCALE + offsetX, g_cub.plr.posY * SCALE - e + offsetY, COLOR);
		my_mlx_pixel_put(&g_data, g_cub.plr.posX * SCALE + offsetX, g_cub.plr.posY * SCALE + e + offsetY, COLOR);
		e++;
	}
}

void	draw_square(int x, int y)
{
	int	color;
	int	i;
	int	j;
	int	offsetX = (g_win.w - g_cub.x * SCALE) / 2;
	int	offsetY = -(SCALE / PADDING);

	i = SCALE / PADDING;
	j = SCALE / PADDING;
	if (g_cub.map[y][x] == '0')
		color = 0x0D21A1;
	else if (g_cub.map[y][x] == '1')
		color = 0x011638;
	else if (g_cub.map[y][x] == '2')
		color = 0xF77F00;
	while (j < SCALE)
	{
		i = SCALE / PADDING;
		while (i < SCALE)
			my_mlx_pixel_put(&g_data, offsetX + x * SCALE + i++, offsetY + y * SCALE + j, color);
		j++;
	}
}

void	draw_minimap(void)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < g_cub.x)
	{
		y = 0;
		while (y < g_cub.y)
		{
			if (g_cub.map[y][x] != ' ')
				draw_square(x, y);
			y++;
		}
		x++;
	}
	draw_position();
}
