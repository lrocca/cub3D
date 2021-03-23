/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 18:08:39 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/23 15:11:01 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		perform_dda(void)
{
	int	hit;
	int	side;

	hit = 0;
	while (hit == 0)
	{
		if (g_cub.ray.sidedistx < g_cub.ray.sidedisty)
		{
			g_cub.ray.sidedistx += g_cub.ray.deltadistx;
			g_cub.ray.mapx += g_cub.ray.stepx;
			side = 0;
		}
		else
		{
			g_cub.ray.sidedisty += g_cub.ray.deltadisty;
			g_cub.ray.mapy += g_cub.ray.stepy;
			side = 1;
		}
		if (g_cub.map[g_cub.ray.mapy][g_cub.ray.mapx] == '1')
			hit = 1;
	}
	return (side);
}

static void		before_print(int side)
{
	if (side == 0)
		g_cub.ray.dist = (g_cub.ray.mapx - g_cub.plr.posx + (1 - g_cub.ray.stepx) / 2) / g_cub.ray.x;
	else
		g_cub.ray.dist = (g_cub.ray.mapy - g_cub.plr.posy + (1 - g_cub.ray.stepy) / 2) / g_cub.ray.y;
	g_cub.ray.line_height = (int)(g_cub.h / g_cub.ray.dist);
	if (side == 0)
		g_cub.ray.wallx = g_cub.plr.posy + g_cub.ray.dist * g_cub.ray.y;
	else
		g_cub.ray.wallx = g_cub.plr.posx + g_cub.ray.dist * g_cub.ray.x;
	g_cub.ray.wallx -= floor((g_cub.ray.wallx));
	g_cub.ray.texture = select_texture(side);
	g_cub.ray.texx = (int)(g_cub.ray.wallx * (double)g_cub.ray.texture->width);
	if (side == 0 && g_cub.ray.x > 0)
		g_cub.ray.texx = g_cub.ray.texture->width - g_cub.ray.texx - 1;
	if (side == 1 && g_cub.ray.y < 0)
		g_cub.ray.texx = g_cub.ray.texture->width - g_cub.ray.texx - 1;
	g_cub.ray.drawstart = -g_cub.ray.line_height / 2 + g_cub.h / 2;
	if (g_cub.ray.drawstart < 0)
		g_cub.ray.drawstart = 0;
	g_cub.ray.drawend = g_cub.ray.line_height / 2 + g_cub.h / 2;
	if (g_cub.ray.drawend >= g_cub.h)
		g_cub.ray.drawend = g_cub.h - 1;
}

static void		put_column(int x)
{
	int		y;
	double	step;
	double	texPos;
	int		texY;
	int		color;

	y = 0;
	step = 1.0 * g_cub.ray.texture->height / g_cub.ray.line_height;
	texPos = (g_cub.ray.drawstart - g_cub.h / 2 + g_cub.ray.line_height / 2) * step;
	while (y < g_cub.ray.drawstart)
		my_mlx_pixel_put(&g_cub.data, x, y++, g_cub.c);
	y = g_cub.ray.drawstart;
	while (y < g_cub.ray.drawend)
	{
		texY = (int)texPos % g_cub.ray.texture->height;
		texPos += step;
		color = ((int *)(g_cub.ray.texture->data.addr))[g_cub.ray.texture->height * texY + g_cub.ray.texx];
		my_mlx_pixel_put(&g_cub.data, x, y, color);
		y++;
	}
	while (y < g_cub.h)
		my_mlx_pixel_put(&g_cub.data, x, y++, g_cub.f);
}

static void		draw_column(int x)
{
	int side;

	if (g_cub.ray.x < 0 && (g_cub.ray.stepx = -1))
		g_cub.ray.sidedistx = (g_cub.plr.posx - g_cub.ray.mapx) * g_cub.ray.deltadistx;
	else if ((g_cub.ray.stepx = 1))
		g_cub.ray.sidedistx = (g_cub.ray.mapx + 1.0 - g_cub.plr.posx) * g_cub.ray.deltadistx;
	if (g_cub.ray.y < 0 && (g_cub.ray.stepy = -1))
		g_cub.ray.sidedisty = (g_cub.plr.posy - g_cub.ray.mapy) * g_cub.ray.deltadisty;
	else if ((g_cub.ray.stepy = 1))
		g_cub.ray.sidedisty = (g_cub.ray.mapy + 1.0 - g_cub.plr.posy) * g_cub.ray.deltadisty;
	side = perform_dda();
	before_print(side);
	put_column(x);
}

void			draw_walls(void)
{
	int		x;
	double	zBuffer[g_cub.w];
	double	cameraX;

	x = 0;
	while (x < g_cub.w)
	{
		cameraX = 2 * x / (double)g_cub.w - 1;
		g_cub.ray.x = g_cub.plr.dirx + g_cub.plr.planex * cameraX;
		g_cub.ray.y = g_cub.plr.diry + g_cub.plr.planey * cameraX;
		g_cub.ray.sidedistx = 0.0;
		g_cub.ray.sidedisty = 0.0;
		g_cub.ray.deltadistx = 0.0;
		g_cub.ray.deltadisty = 0.0;
		g_cub.ray.deltadistx = fabs(1 / g_cub.ray.x);
		g_cub.ray.deltadisty = fabs(1 / g_cub.ray.y);
		g_cub.ray.mapx = (int)g_cub.plr.posx;
		g_cub.ray.mapy = (int)g_cub.plr.posy;
		draw_column(x);
		zBuffer[x] = g_cub.ray.dist;
		x++;
	}
	if (g_cub.spr)
		sprites(zBuffer);
}
