/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 18:56:40 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/29 03:29:01 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
