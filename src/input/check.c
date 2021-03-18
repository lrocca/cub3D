/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 17:13:23 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/18 19:51:08 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static char	check_row(char *s)
// {
// 	while (s && *s)
// 		if (*s++ != '1')
// 			return (1);
// 	return (0);
// }

// static char	check_len_row(char *s, int len)
// {
// 	while (*(s + len))
// 		if (*(s++ + len) != '1')
// 			return (1);
// 	return (0);
// }

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

static char	new_check(void)
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
				if ((y > 0 && g_cub.map[y - 1][x] && !ft_ischarset(g_cub.map[y - 1][x], " 1")) || // tutte tranne prima colonna
					(x > 0 && g_cub.map[y][x - 1] && !ft_ischarset(g_cub.map[y][x - 1], " 1")) || // tutte tranne prima riga
					(y < len - 1 && g_cub.map[y + 1][x] && !ft_ischarset(g_cub.map[y + 1][x], " 1")) || // tutte tranne ultima colonna
					(x < max && g_cub.map[y][x + 1] && !ft_ischarset(g_cub.map[y][x + 1], " 1"))) // tutte tranne ultima riga
					return (1);
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
	g_cub.x = x;
	g_cub.y = y;
	return (0);
}

static char	check_map(void)
{
	return (new_check());
	// int		y;
	// int		x;
	// int		len;
	// int		player;
	// t_spr	*spr;

	// y = 0;
	// x = 0;
	// g_cub.x = 0;
	// len = ft_strlen(g_cub.map[y]);
	// player = 0;

	// while (g_cub.map[0][x])
	// {
	// 	if (ft_isspace(g_cub.map[0][x]))
	// 		g_cub.map[0][x] = '1';
	// 	x++;
	// }
	// if (check_row(g_cub.map[0])) // prima riga
	// 	ft_error("Map: Problem with first line", NULL);
	// while (g_cub.map[y])
	// {
	// 	x = 0;
	// 	if (ft_strlen(g_cub.map[y]) == 0)
	// 		ft_error("Map: Empty line ", ft_itoa(y));
	// 	while (g_cub.map[y][x])
	// 	{
	// 		if (ft_isspace(g_cub.map[y][x]))
	// 			g_cub.map[y][x] = 1;
	// 		if (!g_cub.map[y + 1] && check_row(g_cub.map[y]))
	// 			ft_error("Problem with map in line ", ft_itoa(y));
	// 		if (x > len && check_len_row(g_cub.map[y], len)) // quella prima era piu' corta
	// 			ft_error("Problem with map in line ", ft_itoa(y));
	// 		if (ft_ischarset(g_cub.map[y][x], "NSEW"))
	// 		{
	// 			g_cub.plr.posX = x + 0.5;
	// 			g_cub.plr.posY = y + 0.5;
	// 			set_direction(g_cub.map[y][x]);
	// 			g_cub.map[y][x] = '0';
	// 			player++;
	// 			if (player > 1)
	// 				ft_error("Multiple players in map", NULL);
	// 		}
	// 		else if (g_cub.map[y][x] == '2')
	// 		{
	// 			if (!(spr = malloc(sizeof(t_spr))))
	// 				ft_error("Failed sprite allocation", NULL);
	// 			spr->x = x;
	// 			spr->y = y;
	// 			spr->distance = 0;
	// 			ft_lstadd_back(&g_cub.spr, ft_lstnew(spr));
	// 		}
	// 		if (!g_cub.map[y][x + 1] && g_cub.map[y][x] != '1') // controlla ultimo carattere
	// 			ft_error("Map: Problem with last character in line ", ft_itoa(y));
	// 		if (ft_isspace(g_cub.map[y][x]))
	// 			g_cub.map[y][x] = '1';
	// 		x++;
	// 	}
	// 	if (len > x && check_len_row(g_cub.map[y - 1], x)) // quella prima era piu' lunga
	// 		ft_error("Problem with map in line ", ft_itoa(y));
	// 	len = x;
	// 	g_cub.x = len > g_cub.x ? len : g_cub.x;
	// 	y++;
	// }
	// g_cub.y = y;
	// return (player != 1);
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
// 	printf("NO\t%s\n", g_cub.no.image);
// 	printf("SO\t%s\n", g_cub.so.image);
// 	printf("EA\t%s\n", g_cub.ea.image);
// 	printf("WE\t%s\n", g_cub.we.image);
// 	printf("S\t%s\n", g_cub.s.image);
// 	printf("w\t%d\n", g_win.w);
// 	printf("h\t%d\n", g_win.h);
// 	printf("F\t%#.8X\n", g_cub.F);
// 	printf("C\t%#.8X\n", g_cub.C);
// 	int i = 0;
// 	while (g_cub.map && g_cub.map[i] != NULL)
// 		printf("%s\n", g_cub.map[i++]);
// }

void		check_file(void)
{
	int width;
	int height;

	if (!g_win.h || !g_win.w)
		ft_error("Missing or invalid R declaration", NULL);
	else if (!g_cub.C || !g_cub.F)
		ft_error("Missing colors", NULL);
	else if (!g_cub.no.path || !g_cub.so.path || !g_cub.ea.path || !g_cub.we.path || !g_cub.s.path)
		ft_error("One or more textures are missing", NULL);
	// else if (!load_textures())
	// 	ft_error("Failed to load textures", NULL);
	else if (check_map())
		ft_error("Invalid map", NULL);
	mlx_get_screen_size(g_mlx.mlx, &width, &height);
	g_win.w = g_win.w > width ? width : g_win.w;
	g_win.h = g_win.h > height ? height : g_win.h;
}
