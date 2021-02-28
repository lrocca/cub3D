/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 18:08:39 by lrocca            #+#    #+#             */
/*   Updated: 2021/02/28 19:03:23 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	draw_square(int x, int y)
{
	int		color;
	double	i;
	double	j;
	int		a;
	int		b;

	i = g_win.w / 3 / g_cub.x;
	j = g_win.h / 3 / g_cub.y;
	a = 0;
	while ((x + a) < (x + i))
	{
		b = 0;
		while ((y + b) < (y + j))
		{
			if (g_map[y][x] == '1')
				color = 0x00337C85;
			// // else if (chose_color(x, y) == 1)
			else
				color = g_cub.F;
			// 	color = g_tex.color_sky;
			my_mlx_pixel_put(&g_data, ((x * i) + a), ((y * j) + b), color);
			b++;
		}
		a++;
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
		while (y < g_cub.y)
		{
			draw_square(x, y);
			y++;
		}
		y = 0;
		x++;
	}
	// draw_position();
}
