/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_scenes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 19:23:37 by lrocca            #+#    #+#             */
/*   Updated: 2021/02/28 19:23:48 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void		test_scene()
{
	int height;
	int width;
	mlx_put_image_to_window(g_mlx.mlx, g_win.ptr, mlx_xpm_file_to_image(g_mlx.mlx, g_txt.S, &width, &height), g_win.w/2 - width/2, g_win.h/2 - height/2);
	mlx_string_put(g_mlx.mlx, g_win.ptr, g_win.w/2 - 30, g_win.h/2 + height * 3/4, create_trgb(0, 255, 255, 255), "lrocca");
}

void		walls()
{
	int i = 0;
	int j = 0;
	while (g_map[i])
	{
		j = 0;
		while (g_map[i][j])
		{
			if (g_map[i][j] == '1')
				my_mlx_pixel_put(&g_data, g_win.w/2 + j, g_win.h/2 + i, g_cub.C);
			j++;
		}
		i++;
	}
}
