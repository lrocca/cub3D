/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 19:10:42 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/29 20:26:23 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	loop_life(void)
{
	playSoundFromMemory(g_cub.life, SDL_MIX_MAXVOLUME / SOUNDLEVEL);
	remove_sprite((int)g_cub.plr.posx, (int)g_cub.plr.posy);
	g_cub.plr.life += LIFE / 10;
}

void	loop_success(void)
{
	playSoundFromMemory(g_cub.success, SDL_MIX_MAXVOLUME / SOUNDLEVEL);
	write(1, "You won!\n", 10);
	sleep(1);
	ft_exit(0);
}

void	loop_fail(void)
{
	playSoundFromMemory(g_cub.fail, SDL_MIX_MAXVOLUME / SOUNDLEVEL);
	write(1, "You lost!\n", 11);
	sleep(1);
	ft_exit(0);
}

int		my_loop(void)
{
	g_cub.plr.life--;
	if (g_cub.map[(int)g_cub.plr.posy][(int)g_cub.plr.posx] == '3')
		loop_life();
	else if (g_cub.map[(int)g_cub.plr.posy][(int)g_cub.plr.posx] == '4')
		loop_success();
	if (!g_cub.plr.life)
		loop_fail();
	update_player();
	draw_floor();
	draw_walls();
	draw_life();
	if (g_cub.keys[SPACEBAR])
		draw_minimap();
	mlx_put_image_to_window(g_cub.mlx, g_cub.win, g_cub.data.img, 0, 0);
	mlx_do_sync(g_cub.mlx);
	return (1);
}
