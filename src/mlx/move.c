/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 16:49:56 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/17 17:59:30 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_fwd(void)
{
	t_plr	*plr;
	char	**map;

	map = g_cub.map;
	plr = &g_cub.plr;
	if (map[(int)plr->posY][(int)(plr->posX + plr->dirX * MOVESPEED)] == '0')
		plr->posX += plr->dirX * MOVESPEED;
	if (map[(int)(plr->posY + plr->dirY * MOVESPEED)][(int)plr->posX] == '0')
		plr->posY += plr->dirY * MOVESPEED;
}

void	move_back(void)
{
	t_plr	*plr;
	char	**map;

	map = g_cub.map;
	plr = &g_cub.plr;
	if (map[(int)plr->posY][(int)(plr->posX - plr->dirX * MOVESPEED)] == '0')
		plr->posX -= plr->dirX * MOVESPEED;
	if (map[(int)(plr->posY - plr->dirY * MOVESPEED)][(int)plr->posX] == '0')
		plr->posY -= plr->dirY * MOVESPEED;
}

void	move_left(void)
{
	t_plr	*plr;
	char	**map;

	map = g_cub.map;
	plr = &g_cub.plr;
	if (map[(int)plr->posY][(int)(plr->posX + plr->dirY * MOVESPEED)] == '0')
		plr->posX += plr->dirY * MOVESPEED;
	if (map[(int)(plr->posY - plr->dirX * MOVESPEED)][(int)plr->posX] == '0')
		plr->posY -= plr->dirX * MOVESPEED;
}

void	move_right(void)
{
	t_plr	*plr;
	char	**map;

	map = g_cub.map;
	plr = &g_cub.plr;
	if (map[(int)plr->posY][(int)(plr->posX - plr->dirY * MOVESPEED)] == '0')
		plr->posX -= plr->dirY * MOVESPEED;
	if (map[(int)(plr->posY + plr->dirX * MOVESPEED)][(int)plr->posX] == '0')
		plr->posY += plr->dirX * MOVESPEED;
}
