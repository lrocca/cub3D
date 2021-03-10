/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 17:01:25 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/10 17:03:41 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	rotate_left(void)
{
	double	oldPlaneX;
	double	oldDirX;

	oldPlaneX = g_plr.planeX;
	oldDirX = g_plr.dirX;
	g_plr.dirX = g_plr.dirX * cos(-ROTSPEED / 2) -
		g_plr.dirY * sin(-ROTSPEED / 2);
	g_plr.dirY = oldDirX * sin(-ROTSPEED / 2) +
		g_plr.dirY * cos(-ROTSPEED / 2);
	g_plr.planeX = g_plr.planeX * cos(-ROTSPEED / 2)
		- g_plr.planeY * sin(-ROTSPEED / 2);
	g_plr.planeY = oldPlaneX * sin(-ROTSPEED / 2) +
		g_plr.planeY * cos(-ROTSPEED / 2);
}

void	rotate_right(void)
{
	double	oldPlaneY;
	double	oldDirY;

	oldPlaneY = g_plr.planeY;
	oldDirY = g_plr.dirY;
	g_plr.dirY = g_plr.dirY * cos(-ROTSPEED / 2) -
		g_plr.dirX * sin(-ROTSPEED / 2);
	g_plr.dirX = oldDirY * sin(-ROTSPEED / 2) +
		g_plr.dirX * cos(-ROTSPEED / 2);
	g_plr.planeY = g_plr.planeY * cos(-ROTSPEED / 2)
		- g_plr.planeX * sin(-ROTSPEED / 2);
	g_plr.planeX = oldPlaneY * sin(-ROTSPEED / 2) +
		g_plr.planeX * cos(-ROTSPEED / 2);
}
