/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 03:28:28 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/29 19:45:25 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	get_sprites_distance(t_list *curr)
{
	t_spr	*spr;

	while (curr)
	{
		spr = curr->content;
		spr->distance = ((g_cub.plr.posx - spr->x) * (g_cub.plr.posx - spr->x)
			+ (g_cub.plr.posy - spr->y) * (g_cub.plr.posy - spr->y));
		curr = curr->next;
	}
}

void	put_texel(int y, int stripe, unsigned char t)
{
	int		d;
	int		color;
	int		texx;
	int		texy;
	t_ray	*ray;

	ray = &g_cub.ray;
	texx = (int)(256 * (stripe - (-ray->spritewidth / 2 + ray->spritescreenx)) \
		* g_cub.s[t].width / ray->spritewidth) / 256;
	d = (y - ray->vmove) * 256 - g_cub.h * 128 + ray->spriteheight * 128;
	texy = ((d * g_cub.s[t].height) / ray->spriteheight) / 256;
	color = ((int *)(g_cub.s[t].data.addr))[g_cub.s[t].width * texy + texx];
	if ((color & 0x00FFFFFF) != 0)
		my_mlx_pixel_put(&g_cub.data, stripe, y, color);
}

void	remove_sprite(int x, int y)
{
	t_list	*curr;
	t_list	*tmp;
	t_spr	*spr;

	tmp = NULL;
	curr = g_cub.spr;
	while (curr)
	{
		spr = curr->content;
		if (spr->x == x && spr->y == y)
		{
			if (!tmp)
				g_cub.spr = curr->next;
			else
				tmp->next = curr->next;
			ft_lstdelone(curr, free);
			break ;
		}
		tmp = curr;
		curr = curr->next;
	}
	g_cub.map[y][x] = '0';
}

void	update_z_axis(t_spr *spr)
{
	static char	verse = 0;

	if (spr->type == 0)
		return ;
	if (spr->z < -1)
		verse = 1;
	else if (spr->z > 0)
		verse = 0;
	if (verse)
		spr->z += 0.1;
	else
		spr->z -= 0.1;
}
