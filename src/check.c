/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 17:13:23 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/08 18:11:20 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static char	check_row(char *s)
{
	while (s && *s)
		if (*s++ != '1')
			return (1);
	return (0);
}

static char	check_len_row(char *s, int len)
{
	while (*(s + len))
		if (*(s++ + len) != '1')
			return (1);
	return (0);
}

static void	set_direction(char c)
{
	if (c == 'N')
	{
		g_plr.dirX = 0;
		g_plr.dirY = -1;
	}
	if (c == 'S')
	{
		g_plr.dirX = 0;
		g_plr.dirY = 1;
	}
	if (c == 'E')
	{
		g_plr.dirX = 1;
		g_plr.dirY = 0;
	}
	if (c == 'W')
	{
		g_plr.dirX = -1;
		g_plr.dirY = 0;
	}
}

static char	check_map(void)
{
	int	y;
	int	x;
	int	len;
	int	player;

	y = 0;
	x = 0;
	g_cub.x = 0;
	len = ft_strlen(g_map[y]);
	player = 0;
	if (check_row(g_map[0])) // prima riga
		return (1);
	while (g_map[y])
	{
		x = 0;
		if (ft_strlen(g_map[y]) == 0)// && g_map[i + 1])
			return (1);
		while (g_map[y][x])
		{
			if (!g_map[y + 1] && check_row(g_map[y]))
				return (1);
			if (x > len && check_len_row(g_map[y], len)) // quella prima era piu' corta
				return (1);
			if (ft_ischarset(g_map[y][x], "NSEW"))
			{
				g_plr.posX = x + 0.5;
				g_plr.posY = y + 0.5;
				set_direction(g_map[y][x]);
				player++;
			}
			if (player > 1)
				return (1);
			if (!g_map[y][x + 1] && g_map[y][x] != '1') // controlla ultimo carattere
				return (1);
			if (ft_isspace(g_map[y][x]))
				g_map[y][x] = '1';
			x++;
		}
		if (len > x && check_len_row(g_map[y - 1], x)) // quella prima era piu' lunga
			return (1);
		len = x;
		g_cub.x = len > g_cub.x ? len : g_cub.x;
		y++;
	}
	g_cub.y = y;
	return (player != 1);
}

// prima riga
// prima colonna
// ultima colonna
// controlla riga prima
// controlla riga dopo
// ultima riga
// righe vuote

// static void debug(void)
// {
// 	printf("NO\t%s\n", g_tex.NO);
// 	printf("SO\t%s\n", g_tex.SO);
// 	printf("EA\t%s\n", g_tex.EA);
// 	printf("WE\t%s\n", g_tex.WE);
// 	printf("S\t%s\n", g_tex.S);
// 	printf("w\t%d\n", g_win.w);
// 	printf("h\t%d\n", g_win.h);
// 	printf("F\t%#.8X\n", g_cub.F);
// 	printf("C\t%#.8X\n", g_cub.C);
// 	int i = 0;
// 	while (g_map && g_map[i] != NULL)
// 		printf("%s\n", g_map[i++]);
// }

void		check_file(void)
{
	int width;
	int height;

	// debug();
	if (!g_win.h || !g_win.w)
		ft_error("Missing or invalid R declaration", NULL);
	else if (!g_cub.C || !g_cub.F )
		ft_error("Missing colors", NULL);
	else if (!g_cub.NO || !g_cub.SO || !g_cub.EA || !g_cub.WE || !g_cub.S)
		ft_error("One or more textures are missing", NULL);
	// else if (!load_textures())
	// 	ft_error("Failed to load textures", NULL);
	else if (check_map())
		ft_error("Invalid map", NULL);
	mlx_get_screen_size(g_mlx.mlx, &width, &height);
	g_win.w = g_win.w > width ? width : g_win.w;
	g_win.h = g_win.h > height ? height : g_win.h;
}
