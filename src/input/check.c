/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 17:13:23 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/22 18:32:55 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_direction(char c)
{
	if (c == 'N')
	{
		g_cub.plr.dirX = 0;
		g_cub.plr.dirY = -1;
		g_cub.plr.planeX = 0.66;
		g_cub.plr.planeY = 0;
	}
	if (c == 'S')
	{
		g_cub.plr.dirX = 0;
		g_cub.plr.dirY = 1;
		g_cub.plr.planeX = -0.66;
		g_cub.plr.planeY = 0;
	}
	if (c == 'E')
	{
		g_cub.plr.dirX = 1;
		g_cub.plr.dirY = 0;
		g_cub.plr.planeX = 0;
		g_cub.plr.planeY = 0.66;
	}
	if (c == 'W')
	{
		g_cub.plr.dirX = -1;
		g_cub.plr.dirY = 0;
		g_cub.plr.planeX = 0;
		g_cub.plr.planeY = -0.66;
	}
}

static char	check_map(void)
{
	int		x;
	int		y;
	int		max;
	int		len;
	char	player;
	t_spr	*spr;

	y = 0;
	player = 0;
	max = ft_strlen(g_cub.map[0]);
	if (max < 4)
		ft_error("Map too small", NULL);
	len = 0;
	while (g_cub.map[len])
		len++;
	while (y < len)
	{
		x = 0;
		while (x < max)
		{
			if (g_cub.map[y][x] == ' ')
			{
				if ((y > 0 && g_cub.map[y - 1] && !ft_ischarset(g_cub.map[y - 1][x], " 1")) || // tutte tranne prima colonna
					(x > 0 && g_cub.map[y] && !ft_ischarset(g_cub.map[y][x - 1], " 1")) || // tutte tranne prima riga
					(y < len - 1 && g_cub.map[y + 1] && !ft_ischarset(g_cub.map[y + 1][x], " 1")) || // tutte tranne ultima colonna
					(x < max - 1 && g_cub.map[y] && !ft_ischarset(g_cub.map[y][x + 1], " 1"))) // tutte tranne ultima riga
					ft_error("Bad character in map near...", NULL);
			}
			else if (ft_ischarset(g_cub.map[y][x], "NSEW"))
			{
				g_cub.plr.posX = x + 0.5;
				g_cub.plr.posY = y + 0.5;
				set_direction(g_cub.map[y][x]);
				g_cub.map[y][x] = '0';
				player++;
				if (player > 1)
					ft_error("Multiple players in map", NULL);
			}
			else if (g_cub.map[y][x] == '2')
			{
				if (!(spr = malloc(sizeof(t_spr))))
					ft_error("Failed sprite allocation", NULL);
				spr->x = x;
				spr->y = y;
				spr->distance = 0;
				ft_lstadd_back(&g_cub.spr, ft_lstnew(spr));
			}
			x++;
		}
		y++;
	}
	if (y < 4)
		ft_error("Map too small", NULL);
	g_cub.x = x;
	g_cub.y = y;
	return (player);
}

void		check_file(void)
{
	int width;
	int height;

	if (!g_win.h || !g_win.w)
		ft_error("Missing or invalid R declaration", NULL);
	else if (!g_cub.check[0] || !g_cub.check[1])
		ft_error("Missing colors", NULL);
	else if (!g_cub.no.path || !g_cub.so.path || !g_cub.ea.path || !g_cub.we.path || !g_cub.s.path)
		ft_error("One or more textures are missing", NULL);
	// else if (!load_textures())
	// 	ft_error("Failed to load textures", NULL);
	else if (!check_map())
		ft_error("Invalid map", NULL);
	mlx_get_screen_size(g_mlx.mlx, &width, &height);
	g_win.w = g_win.w > width ? width : g_win.w;
	g_win.h = g_win.h > height ? height : g_win.h;
}
