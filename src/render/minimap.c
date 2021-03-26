/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 18:29:03 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/26 18:45:33 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#define SCALE	16
#define COLOR	0xEEF0F2
#define PADDING	12

void	draw_position(void)
{
	int	e;
	int	offsetx;
	int	offsety;

	e = 0;
	offsetx = (g_cub.w - g_cub.x * SCALE) / 2;
	offsety = -(SCALE / PADDING);
	while (e < SCALE / 4)
	{
		my_mlx_pixel_put(&g_cub.data, g_cub.plr.posx * SCALE + e + offsetx, \
			g_cub.plr.posy * SCALE + offsety, COLOR);
		my_mlx_pixel_put(&g_cub.data, g_cub.plr.posx * SCALE - e + offsetx, \
			g_cub.plr.posy * SCALE + offsety, COLOR);
		my_mlx_pixel_put(&g_cub.data, g_cub.plr.posx * SCALE + offsetx, \
			g_cub.plr.posy * SCALE - e + offsety, COLOR);
		my_mlx_pixel_put(&g_cub.data, g_cub.plr.posx * SCALE + offsetx, \
			g_cub.plr.posy * SCALE + e + offsety, COLOR);
		e++;
	}
}

void	draw_square(int x, int y)
{
	int	i;
	int	j;
	int	color;
	int	offsetx;
	int	offsety;

	i = SCALE / PADDING;
	j = SCALE / PADDING;
	offsetx = (g_cub.w - g_cub.x * SCALE) / 2;
	offsety = -(SCALE / PADDING);
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
			my_mlx_pixel_put(&g_cub.data, offsetx + x * SCALE + i++, \
				offsety + y * SCALE + j, color);
		j++;
	}
}

void	draw_minimap(void)
{
	int x;
	int y;

	if (g_cub.h < SCALE * g_cub.y || g_cub.w < SCALE * g_cub.x)
		return ;
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
