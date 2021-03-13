/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 16:49:56 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/13 19:24:48 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_fwd(void)
{
	if (g_map[(int)g_plr.posY][(int)(g_plr.posX + g_plr.dirX * MOVESPEED)] == '0')
		g_plr.posX += g_plr.dirX * MOVESPEED;
	if (g_map[(int)(g_plr.posY + g_plr.dirY * MOVESPEED)][(int)g_plr.posX] == '0')
		g_plr.posY += g_plr.dirY * MOVESPEED;
}

void	move_back(void)
{
	if (g_map[(int)g_plr.posY][(int)(g_plr.posX - g_plr.dirX * MOVESPEED)] == '0')
		g_plr.posX -= g_plr.dirX * MOVESPEED;
	if (g_map[(int)(g_plr.posY - g_plr.dirY * MOVESPEED)][(int)g_plr.posX] == '0')
		g_plr.posY -= g_plr.dirY * MOVESPEED;
}

void	move_left(void)
{
	if (g_map[(int)g_plr.posY][(int)(g_plr.posX + g_plr.dirY * MOVESPEED)] == '0')
		g_plr.posX += g_plr.dirY * MOVESPEED;
	if (g_map[(int)(g_plr.posY - g_plr.dirX * MOVESPEED)][(int)g_plr.posX] == '0')
		g_plr.posY -= g_plr.dirX * MOVESPEED;
}

void	move_right(void)
{
	if (g_map[(int)g_plr.posY][(int)(g_plr.posX - g_plr.dirY * MOVESPEED)] == '0')
		g_plr.posX -= g_plr.dirY * MOVESPEED;
	if (g_map[(int)(g_plr.posY + g_plr.dirX * MOVESPEED)][(int)g_plr.posX] == '0')
		g_plr.posY += g_plr.dirX * MOVESPEED;
}
