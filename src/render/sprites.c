/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 18:15:40 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/23 19:58:35 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_list	*find_lowest(t_list *curr, t_list *prev)
{
	double	n;

	if (!curr)
		return (NULL);
	n = ((t_spr*)curr->content)->distance;
	while (curr->next)
	{
		if (((t_spr*)curr->next->content)->distance <= n)
		{
			n = ((t_spr*)curr->next->content)->distance;
			prev = curr;
		}
		curr = curr->next;
	}
	if (prev)
	{
		curr = prev->next;
		prev->next = curr->next;
		return (curr);
	}
	prev = g_cub.spr;
	g_cub.spr = prev->next;
	return (prev);
}

static void		sort_sprites(void)
{
	t_list	*out;
	t_list	*lowest;

	while ((lowest = find_lowest(g_cub.spr, 0)))
	{
		lowest->next = NULL;
		ft_lstadd_front(&out, lowest);
	}
	g_cub.spr = out;
}

static void		draw_sprites(double *zbuffer)
{
	int	y;
	int	stripe;

	stripe = g_cub.ray.drawstartx;
	while (stripe < g_cub.ray.drawendx)
	{
		if (g_cub.ray.transformy > 0 && stripe > 0 && stripe < g_cub.w && \
			g_cub.ray.transformy < zbuffer[stripe])
		{
			y = g_cub.ray.drawstarty;
			while (y < g_cub.ray.drawendy)
			{
				put_texel(y, stripe);
				y++;
			}
		}
		stripe++;
	}
}

static void		before_print(t_spr *spr)
{
	g_cub.ray.spritex = spr->x - g_cub.plr.posx + 0.5;
	g_cub.ray.spritey = spr->y - g_cub.plr.posy + 0.5;
	g_cub.ray.invdet = 1.0 / (g_cub.plr.planex * g_cub.plr.diry \
	- g_cub.plr.dirx * g_cub.plr.planey);
	g_cub.ray.transformx = g_cub.ray.invdet * (g_cub.plr.diry \
	* g_cub.ray.spritex - g_cub.plr.dirx * g_cub.ray.spritey);
	g_cub.ray.transformy = g_cub.ray.invdet * (-g_cub.plr.planey \
	* g_cub.ray.spritex + g_cub.plr.planex * g_cub.ray.spritey);
	g_cub.ray.spritescreenx = (int)((g_cub.w / 2) * \
	(1 + g_cub.ray.transformx / g_cub.ray.transformy));
	g_cub.ray.vmove = (int)(g_cub.s.height * 4 / g_cub.ray.transformy);
	g_cub.ray.spriteheight = abs((int)(g_cub.h \
	/ (g_cub.ray.transformy))) / VDIV;
	g_cub.ray.drawstarty = -g_cub.ray.spriteheight / 2 + g_cub.h \
	/ 2 + g_cub.ray.vmove;
	if (g_cub.ray.drawstarty < 0)
		g_cub.ray.drawstarty = 0;
	g_cub.ray.drawendy = g_cub.ray.spriteheight / 2 + g_cub.h \
	/ 2 + g_cub.ray.vmove;
	if (g_cub.ray.drawendy >= g_cub.h)
		g_cub.ray.drawendy = g_cub.h - 1;
}

void			sprites(double *zbuffer)
{
	t_list	*curr;
	t_spr	*spr;

	spr = NULL;
	curr = g_cub.spr;
	get_sprites_distance(curr, spr);
	sort_sprites();
	while (curr)
	{
		before_print(curr->content);
		g_cub.ray.spritewidth = abs((int)(g_cub.h / \
		(g_cub.ray.transformy))) / UDIV;
		g_cub.ray.drawstartx = -g_cub.ray.spritewidth / 2 \
		+ g_cub.ray.spritescreenx;
		if (g_cub.ray.drawstartx < 0)
			g_cub.ray.drawstartx = 0;
		g_cub.ray.drawendx = g_cub.ray.spritewidth / 2 \
		+ g_cub.ray.spritescreenx;
		if (g_cub.ray.drawendx >= g_cub.w)
			g_cub.ray.drawendx = g_cub.w - 1;
		draw_sprites(zbuffer);
		curr = curr->next;
	}
}
