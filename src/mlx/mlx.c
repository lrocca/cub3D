/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 15:34:57 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/28 23:21:27 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	my_loop(void)
{
	g_cub.plr.life--;
	if (!g_cub.plr.life)
	{
		write(1, "You're dead!\n", 14);
		ft_exit(0);
	}
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

static void	load_textures(void)
{
	if (g_cub.opt & FLOOR)
		load_texture(&g_cub.floor);
	if (g_cub.opt & CEILING)
		load_texture(&g_cub.ceiling);
	load_texture(&g_cub.no);
	load_texture(&g_cub.so);
	load_texture(&g_cub.we);
	load_texture(&g_cub.ea);
	if (g_cub.spr)
		load_texture(&g_cub.s);
}

static void	save_flag(void)
{
	draw_floor();
	draw_walls();
	save_image_to_bmp_file();
	ft_exit(0);
}

static void	load_music(void)
{
	SDL_Init(SDL_INIT_AUDIO);
	initAudio();
	if (!(g_cub.music = createAudio(MUSICPATH, 1, SDL_MIX_MAXVOLUME)))
		ft_error("Failed to load music", NULL);
	playMusicFromMemory(g_cub.music, SDL_MIX_MAXVOLUME);
	g_cub.audio = 1;
}

void		mlx(void)
{
	t_data	*data;

	data = &g_cub.data;
	ft_bzero(g_cub.keys, 129);
	if (!(g_cub.mlx = mlx_init()))
		ft_error("Connection to graphical system failed", NULL);
	load_textures();
	data->img = mlx_new_image(g_cub.mlx, g_cub.w, g_cub.h);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, \
		&data->line_length, &data->endian);
	if (g_cub.save)
		save_flag();
	g_cub.win = mlx_new_window(g_cub.mlx, g_cub.w, g_cub.h, "cub3D");
	load_music();
	mlx_mouse_hide();
	mlx_mouse_move(g_cub.win, 0, 0);
	mlx_hook(g_cub.win, KEYPRESS, 0, &keypress, NULL);
	mlx_hook(g_cub.win, KEYRELEASE, 0, &keyrelease, NULL);
	mlx_hook(g_cub.win, 17, 0, &ft_exit, NULL);
	mlx_loop_hook(g_cub.mlx, &my_loop, NULL);
	mlx_loop(g_cub.mlx);
}
