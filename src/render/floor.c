/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 18:49:23 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/29 20:24:10 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	put_row(t_ray *ray, int x, int y)
{
	int		tx;
	int		ty;
	int		color;
	t_tex	*f;
	t_tex	*c;

	f = &g_cub.floor;
	c = &g_cub.ceiling;
	if (g_cub.opt & FLOOR)
	{
		tx = (int)(f->width * (ray->floorx - ray->cellx)) & (f->width - 1);
		ty = (int)(f->height * (ray->floory - ray->celly)) & (f->height - 1);
		color = ((int *)f->data.addr)[f->width * ty + tx];
		my_mlx_pixel_put(&g_cub.data, x, y, color);
	}
	if (g_cub.opt & CEILING)
	{
		tx = (int)(c->width * (ray->floorx - ray->cellx)) & (c->width - 1);
		ty = (int)(c->height * (ray->floory - ray->celly)) & (c->height - 1);
		color = ((int *)c->data.addr)[c->width * ty + tx];
		my_mlx_pixel_put(&g_cub.data, x, g_cub.h - y - 1, color);
	}
}

static void	calculus(t_ray *ray, t_plr *plr)
{
	ray->raydirx0 = plr->dirx - plr->planex;
	ray->raydiry0 = plr->diry - plr->planey;
	ray->raydirx1 = plr->dirx + plr->planex;
	ray->raydiry1 = plr->diry + plr->planey;
	ray->p = ray->y - g_cub.h / 2;
	ray->z = 0.5 * g_cub.h;
	ray->dist = ray->z / ray->p;
	ray->floorstepx = ray->dist * (ray->raydirx1 - ray->raydirx0) / g_cub.w;
	ray->floorstepy = ray->dist * (ray->raydiry1 - ray->raydiry0) / g_cub.w;
	ray->floorx = plr->posx + ray->dist * ray->raydirx0;
	ray->floory = plr->posy + ray->dist * ray->raydiry0;
}

void		draw_floor(void)
{
	g_cub.ray.y = 0;
	while (g_cub.ray.y < g_cub.h)
	{
		calculus(&g_cub.ray, &g_cub.plr);
		g_cub.ray.x = 0;
		while (g_cub.ray.x < g_cub.w)
		{
			g_cub.ray.cellx = (int)(g_cub.ray.floorx);
			g_cub.ray.celly = (int)(g_cub.ray.floory);
			put_row(&g_cub.ray, g_cub.ray.x, g_cub.ray.y);
			g_cub.ray.floorx += g_cub.ray.floorstepx;
			g_cub.ray.floory += g_cub.ray.floorstepy;
			g_cub.ray.x++;
		}
		g_cub.ray.y++;
	}
}
