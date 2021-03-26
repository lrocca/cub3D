/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 17:01:25 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/26 18:45:33 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	rotate_left(void)
{
	double	old_plane_x;
	double	old_dir_x;

	old_plane_x = g_cub.plr.planex;
	old_dir_x = g_cub.plr.dirx;
	g_cub.plr.dirx = g_cub.plr.dirx * cos(-ROTSPEED / 2) -
		g_cub.plr.diry * sin(-ROTSPEED / 2);
	g_cub.plr.diry = old_dir_x * sin(-ROTSPEED / 2) +
		g_cub.plr.diry * cos(-ROTSPEED / 2);
	g_cub.plr.planex = g_cub.plr.planex * cos(-ROTSPEED / 2)
		- g_cub.plr.planey * sin(-ROTSPEED / 2);
	g_cub.plr.planey = old_plane_x * sin(-ROTSPEED / 2) +
		g_cub.plr.planey * cos(-ROTSPEED / 2);
}

void	rotate_right(void)
{
	double	old_plane_y;
	double	old_dir_y;

	old_plane_y = g_cub.plr.planey;
	old_dir_y = g_cub.plr.diry;
	g_cub.plr.diry = g_cub.plr.diry * cos(-ROTSPEED / 2) -
		g_cub.plr.dirx * sin(-ROTSPEED / 2);
	g_cub.plr.dirx = old_dir_y * sin(-ROTSPEED / 2) +
		g_cub.plr.dirx * cos(-ROTSPEED / 2);
	g_cub.plr.planey = g_cub.plr.planey * cos(-ROTSPEED / 2)
		- g_cub.plr.planex * sin(-ROTSPEED / 2);
	g_cub.plr.planex = old_plane_y * sin(-ROTSPEED / 2) +
		g_cub.plr.planex * cos(-ROTSPEED / 2);
}
