/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 16:49:56 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/26 18:45:33 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	move_fwd(void)
{
	t_plr	*plr;
	char	**map;

	map = g_cub.map;
	plr = &g_cub.plr;
	if (map[(int)plr->posy][(int)(plr->posx + plr->dirx * MOVESPEED)] == '0')
		plr->posx += plr->dirx * MOVESPEED;
	if (map[(int)(plr->posy + plr->diry * MOVESPEED)][(int)plr->posx] == '0')
		plr->posy += plr->diry * MOVESPEED;
}

void	move_back(void)
{
	t_plr	*plr;
	char	**map;

	map = g_cub.map;
	plr = &g_cub.plr;
	if (map[(int)plr->posy][(int)(plr->posx - plr->dirx * MOVESPEED)] == '0')
		plr->posx -= plr->dirx * MOVESPEED;
	if (map[(int)(plr->posy - plr->diry * MOVESPEED)][(int)plr->posx] == '0')
		plr->posy -= plr->diry * MOVESPEED;
}

void	move_left(void)
{
	t_plr	*plr;
	char	**map;

	map = g_cub.map;
	plr = &g_cub.plr;
	if (map[(int)plr->posy]
		[(int)(plr->posx + plr->diry * MOVESPEED / 1.5)] == '0')
		plr->posx += plr->diry * MOVESPEED / 1.5;
	if (map[(int)(plr->posy - plr->dirx * MOVESPEED / 1.5)]
		[(int)plr->posx] == '0')
		plr->posy -= plr->dirx * MOVESPEED / 1.5;
}

void	move_right(void)
{
	t_plr	*plr;
	char	**map;

	map = g_cub.map;
	plr = &g_cub.plr;
	if (map[(int)plr->posy]
		[(int)(plr->posx - plr->diry * MOVESPEED / 1.5)] == '0')
		plr->posx -= plr->diry * MOVESPEED / 1.5;
	if (map[(int)(plr->posy + plr->dirx * MOVESPEED / 1.5)]
		[(int)plr->posx] == '0')
		plr->posy += plr->dirx * MOVESPEED / 1.5;
}
