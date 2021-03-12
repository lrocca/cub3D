/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 18:29:03 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/12 18:29:11 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_position(void)
{
	double	i;
	double	j;
	int		e;

	i = (g_win.w / 3) / g_cub.x;
	j = (g_win.h / 3) / g_cub.y;
	e = 0;
	if (g_win.h > 5 && g_win.w > 5)
	{
		while (e < 5)
		{
			my_mlx_pixel_put(&g_data, ((g_plr.posX * i) + e),
			((g_plr.posY * j)), 0x00000000);
			my_mlx_pixel_put(&g_data, ((g_plr.posX * i) - e),
			((g_plr.posY * j)), 0x00000000);
			my_mlx_pixel_put(&g_data, (g_plr.posX * i),
			(g_plr.posY * j - e), 0x00000000);
			my_mlx_pixel_put(&g_data, (g_plr.posX * i),
			(g_plr.posY * j + e), 0x00000000);
			e++;
		}
	}
}

void	draw_square(int x, int y)
{
	int		color;
	double	i;
	double	j;
	int		a;
	int		b;

	i = (g_win.w / 3) / g_cub.x;
	j = (g_win.h / 3) / g_cub.y;
	a = 0;
	while ((x + a) < (x + i))
	{
		b = 0;
		while ((y + b) < (y + j))
		{
			if (g_map[y][x] == '1')
				color = g_cub.C;
			else if (g_map[y][x] == '0')
				color = g_cub.F;
			else
				color = 0;
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
	draw_position();
}
