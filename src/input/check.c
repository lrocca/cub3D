/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 17:13:23 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/26 18:45:33 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	set_direction(char c)
{
	g_cub.plr.dirx = 0;
	g_cub.plr.diry = 0;
	g_cub.plr.planex = 0;
	g_cub.plr.planey = 0;
	if (c == 'N')
	{
		g_cub.plr.diry = -1;
		g_cub.plr.planex = 0.66;
	}
	else if (c == 'S')
	{
		g_cub.plr.diry = 1;
		g_cub.plr.planex = -0.66;
	}
	else if (c == 'E')
	{
		g_cub.plr.dirx = 1;
		g_cub.plr.planey = 0.66;
	}
	else if (c == 'W')
	{
		g_cub.plr.dirx = -1;
		g_cub.plr.planey = -0.66;
	}
}

static void	set_player(int x, int y)
{
	g_cub.plr.posx = x + 0.5;
	g_cub.plr.posy = y + 0.5;
	set_direction(g_cub.map[y][x]);
	g_cub.map[y][x] = '0';
}

static void	set_sprite(int x, int y)
{
	t_spr	*spr;

	if (!(spr = malloc(sizeof(t_spr))))
		ft_error("Sprite allocation failed", NULL);
	spr->x = x;
	spr->y = y;
	spr->distance = 0;
	ft_lstadd_back(&g_cub.spr, ft_lstnew(spr));
}

static void	check_map(void)
{
	int		x;
	int		y;
	char	player;

	y = 0;
	player = 0;
	if (g_cub.x < 4 || g_cub.y < 4)
		ft_error("Map too small", NULL);
	while (y < g_cub.y)
	{
		x = 0;
		while (x < g_cub.x)
		{
			if (g_cub.map[y][x] == ' ' && invalid_character(x, y))
				ft_error("Bad character in map", NULL);
			else if (ft_ischarset(g_cub.map[y][x], "NSEW") && (player += 1))
				set_player(x, y);
			else if (g_cub.map[y][x] == '2')
				set_sprite(x, y);
			x++;
		}
		y++;
	}
	if (player != 1)
		ft_error("Invalid player in map", NULL);
}

void		check_file(void)
{
	int width;
	int height;

	if (!g_cub.h || !g_cub.w)
		ft_error("Missing or invalid R declaration", NULL);
	else if (!g_cub.check[0] || !g_cub.check[1])
		ft_error("Missing colors", NULL);
	else if (!g_cub.no.path || !g_cub.so.path || !g_cub.ea.path || \
		!g_cub.we.path || !g_cub.s.path)
		ft_error("One or more textures are missing", NULL);
	check_map();
	mlx_get_screen_size(g_cub.mlx, &width, &height);
	g_cub.w = g_cub.w > width ? width : g_cub.w;
	g_cub.h = g_cub.h > height ? height : g_cub.h;
}
