/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 17:13:23 by lrocca            #+#    #+#             */
/*   Updated: 2021/02/28 18:47:58 by lrocca           ###   ########.fr       */
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

static char	check_map(void)
{
	int	i;
	int	j;
	int	len;
	int	player;

	i = 0;
	j = 0;
	g_cub.x = 0;
	len = ft_strlen(g_map[i]);
	player = 0;
	if (check_row(g_map[0])) // prima riga
		return (1);
	while (g_map[i])
	{
		j = 0;
		if (ft_strlen(g_map[i]) == 0)// && g_map[i + 1])
			return (1);
		while (g_map[i][j])
		{
			if (!g_map[i + 1] && check_row(g_map[i]))
				return (1);
			if (j > len && check_len_row(g_map[i], len)) // quella prima era piu' corta
				return (1);
			player += ft_ischarset(g_map[i][j], "NSEW");
			if (player > 1)
				return (1);
			if (!g_map[i][j + 1] && g_map[i][j] != '1') // controlla ultimo carattere
				return (1);
			if (ft_isspace(g_map[i][j]))
				g_map[i][j] = '1';
			j++;
		}
		if (len > j && check_len_row(g_map[i - 1], j)) // quella prima era piu' lunga
			return (1);
		len = j;
		g_cub.x = len > g_cub.x ? len : g_cub.x;
		i++;
	}
	g_cub.y = i;
	return (player != 1);
}

// prima riga
// prima colonna
// ultima colonna
// controlla riga prima
// controlla riga dopo
// ultima riga
// righe vuote

void	check_file(void)
{
	// printf("NO\t%s\n", g_txt.NO);
	// printf("SO\t%s\n", g_txt.SO);
	// printf("EA\t%s\n", g_txt.EA);
	// printf("WE\t%s\n", g_txt.WE);
	// printf("S\t%s\n", g_txt.S);
	// printf("w\t%d\n", g_win.w);
	// printf("h\t%d\n", g_win.h);
	// printf("F\t%#.8X\n", g_cub.F);
	// printf("C\t%#.8X\n", g_cub.C);
	// int i = 0;
	// while (g_map && g_map[i] != NULL)
	// 	printf("%s\n", g_map[i++]);

	int width;
	int height;

	if (!g_win.h || !g_win.w)
		ft_error("Missing or invalid R declaration", NULL);
	else if (!g_cub.C || !g_cub.F )
		ft_error("Missing colors", NULL);
	else if (!g_txt.NO || !g_txt.SO || !g_txt.EA || !g_txt.WE || !g_txt.S)
		ft_error("One or more textures are missing", NULL);
	else if (check_map())
		ft_error("Invalid map", NULL);
	mlx_get_screen_size(g_mlx.mlx, &width, &height);
	g_win.w = g_win.w > width ? width : g_win.w;
	g_win.h = g_win.h > height ? height : g_win.h;
}
