/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 18:56:40 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/23 19:58:54 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_tex	*select_texture(int side)
{
	if (side == 1)
	{
		if (g_cub.ray.y > 0)
			g_cub.ray.texture = &g_cub.so;
		else
			g_cub.ray.texture = &g_cub.no;
	}
	else
	{
		if (g_cub.ray.x > 0)
			g_cub.ray.texture = &g_cub.ea;
		else
			g_cub.ray.texture = &g_cub.we;
	}
	return (g_cub.ray.texture);
}

void	get_sprites_distance(t_list *curr, t_spr *spr)
{
	while (curr)
	{
		spr = curr->content;
		spr->distance = ((g_cub.plr.posx - spr->x) * (g_cub.plr.posx - spr->x)
			+ (g_cub.plr.posy - spr->y) * (g_cub.plr.posy - spr->y));
		curr = curr->next;
	}
}

void	put_texel(int y, int stripe)
{
	int		d;
	int		color;
	int		texx;
	int		texy;
	t_ray	*ray;

	ray = &g_cub.ray;
	texx = (int)(256 * (stripe - (-ray->spritewidth / 2 + ray->spritescreenx)) \
		* g_cub.s.width / ray->spritewidth) / 256;
	d = (y - ray->vmove) * 256 - g_cub.h * 128 + ray->spriteheight * 128;
	texy = ((d * g_cub.s.height) / ray->spriteheight) / 256;
	color = ((unsigned int *)(g_cub.s.data.addr))[g_cub.s.width * texy + texx];
	if ((color & 0x00FFFFFF) != 0)
		my_mlx_pixel_put(&g_cub.data, stripe, y, color);
}
