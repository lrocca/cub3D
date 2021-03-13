/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 17:01:25 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/13 19:39:18 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_left(void)
{
	double	old_plane_x;
	double	old_dir_x;

	old_plane_x = g_plr.planeX;
	old_dir_x = g_plr.dirX;
	g_plr.dirX = g_plr.dirX * cos(-ROTSPEED / 2) -
		g_plr.dirY * sin(-ROTSPEED / 2);
	g_plr.dirY = old_dir_x * sin(-ROTSPEED / 2) +
		g_plr.dirY * cos(-ROTSPEED / 2);
	g_plr.planeX = g_plr.planeX * cos(-ROTSPEED / 2)
		- g_plr.planeY * sin(-ROTSPEED / 2);
	g_plr.planeY = old_plane_x * sin(-ROTSPEED / 2) +
		g_plr.planeY * cos(-ROTSPEED / 2);
}

void	rotate_right(void)
{
	double	old_plane_y;
	double	old_dir_y;

	old_plane_y = g_plr.planeY;
	old_dir_y = g_plr.dirY;
	g_plr.dirY = g_plr.dirY * cos(-ROTSPEED / 2) -
		g_plr.dirX * sin(-ROTSPEED / 2);
	g_plr.dirX = old_dir_y * sin(-ROTSPEED / 2) +
		g_plr.dirX * cos(-ROTSPEED / 2);
	g_plr.planeY = g_plr.planeY * cos(-ROTSPEED / 2)
		- g_plr.planeX * sin(-ROTSPEED / 2);
	g_plr.planeX = old_plane_y * sin(-ROTSPEED / 2) +
		g_plr.planeX * cos(-ROTSPEED / 2);
}
