/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 16:49:56 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/29 03:13:25 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#define WALK "034"

void	move_fwd(void)
{
	t_plr	*plr;
	char	**map;

	map = g_cub.map;
	plr = &g_cub.plr;
	if (ft_ischarset(
		map[(int)plr->posy][(int)(plr->posx + plr->dirx * MOVESPEED)], WALK))
		plr->posx += plr->dirx * MOVESPEED;
	if (ft_ischarset(
		map[(int)(plr->posy + plr->diry * MOVESPEED)][(int)plr->posx], WALK))
		plr->posy += plr->diry * MOVESPEED;
}

void	move_back(void)
{
	t_plr	*plr;
	char	**map;

	map = g_cub.map;
	plr = &g_cub.plr;
	if (ft_ischarset(
		map[(int)plr->posy][(int)(plr->posx - plr->dirx * MOVESPEED)], WALK))
		plr->posx -= plr->dirx * MOVESPEED;
	if (ft_ischarset(
		map[(int)(plr->posy - plr->diry * MOVESPEED)][(int)plr->posx], WALK))
		plr->posy -= plr->diry * MOVESPEED;
}

void	move_left(void)
{
	t_plr	*plr;
	char	**map;

	map = g_cub.map;
	plr = &g_cub.plr;
	if (ft_ischarset(
	map[(int)plr->posy][(int)(plr->posx + plr->diry * MOVESPEED / 1.5)], WALK))
		plr->posx += plr->diry * MOVESPEED / 1.5;
	if (ft_ischarset(
	map[(int)(plr->posy - plr->dirx * MOVESPEED / 1.5)][(int)plr->posx], WALK))
		plr->posy -= plr->dirx * MOVESPEED / 1.5;
}

void	move_right(void)
{
	t_plr	*plr;
	char	**map;

	map = g_cub.map;
	plr = &g_cub.plr;
	if (ft_ischarset(
	map[(int)plr->posy][(int)(plr->posx - plr->diry * MOVESPEED / 1.5)], WALK))
		plr->posx -= plr->diry * MOVESPEED / 1.5;
	if (ft_ischarset(
	map[(int)(plr->posy + plr->dirx * MOVESPEED / 1.5)][(int)plr->posx], WALK))
		plr->posy += plr->dirx * MOVESPEED / 1.5;
}
