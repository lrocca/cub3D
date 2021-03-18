/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 17:01:25 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/17 16:57:20 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_left(void)
{
	double	old_plane_x;
	double	old_dir_x;

	old_plane_x = g_cub.plr.planeX;
	old_dir_x = g_cub.plr.dirX;
	g_cub.plr.dirX = g_cub.plr.dirX * cos(-ROTSPEED / 2) -
		g_cub.plr.dirY * sin(-ROTSPEED / 2);
	g_cub.plr.dirY = old_dir_x * sin(-ROTSPEED / 2) +
		g_cub.plr.dirY * cos(-ROTSPEED / 2);
	g_cub.plr.planeX = g_cub.plr.planeX * cos(-ROTSPEED / 2)
		- g_cub.plr.planeY * sin(-ROTSPEED / 2);
	g_cub.plr.planeY = old_plane_x * sin(-ROTSPEED / 2) +
		g_cub.plr.planeY * cos(-ROTSPEED / 2);
}

void	rotate_right(void)
{
	double	old_plane_y;
	double	old_dir_y;

	old_plane_y = g_cub.plr.planeY;
	old_dir_y = g_cub.plr.dirY;
	g_cub.plr.dirY = g_cub.plr.dirY * cos(-ROTSPEED / 2) -
		g_cub.plr.dirX * sin(-ROTSPEED / 2);
	g_cub.plr.dirX = old_dir_y * sin(-ROTSPEED / 2) +
		g_cub.plr.dirX * cos(-ROTSPEED / 2);
	g_cub.plr.planeY = g_cub.plr.planeY * cos(-ROTSPEED / 2)
		- g_cub.plr.planeX * sin(-ROTSPEED / 2);
	g_cub.plr.planeX = old_plane_y * sin(-ROTSPEED / 2) +
		g_cub.plr.planeX * cos(-ROTSPEED / 2);
}
