/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 19:18:39 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/26 18:45:33 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		keypress(int key)
{
	if (key == ESCKEY)
		ft_exit(0);
	if (key < 128)
		g_cub.keys[key] = 1;
	return (0);
}

int		keyrelease(int key)
{
	if (key < 128)
		g_cub.keys[key] = 0;
	return (0);
}

void	update_player(void)
{
	if (g_cub.keys[WKEY])
		move_fwd();
	if (g_cub.keys[SKEY])
		move_back();
	if (g_cub.keys[AKEY])
		move_left();
	if (g_cub.keys[DKEY])
		move_right();
	if (g_cub.keys[LEFTARROW] || g_cub.keys[MOUSE] > 0)
	{
		g_cub.keys[MOUSE] = 0;
		rotate_left();
	}
	if (g_cub.keys[RIGHTARROW] || g_cub.keys[MOUSE] < 0)
	{
		g_cub.keys[MOUSE] = 0;
		rotate_right();
	}
}

int		mousemove(int x, int y)
{
	static int	ex_x;
	static char	flag;

	mlx_mouse_hide();
	if (y)
		mlx_mouse_move(g_cub.win, x, 0);
	if (flag && (flag = 0))
		return (0);
	if (ex_x > x)
		g_cub.keys[MOUSE] = 1;
	else if (ex_x < x)
		g_cub.keys[MOUSE] = -1;
	ex_x = x;
	if (x > g_cub.w || x < 0)
	{
		flag = 1;
		mlx_mouse_move(g_cub.win, g_cub.w / 2, 0);
	}
	return (0);
}
