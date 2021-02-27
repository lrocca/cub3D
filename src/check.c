/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 17:13:23 by lrocca            #+#    #+#             */
/*   Updated: 2021/02/27 18:37:03 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static char	check_map(void)
{

	return (0);
}

void	check_file(void)
{
	// printf("NO\t%s\n", g_txt.NO);
	// printf("SO\t%s\n", g_txt.SO);
	// printf("EA\t%s\n", g_txt.EA);
	// printf("WE\t%s\n", g_txt.WE);
	// printf("S\t%s\n", g_txt.S);
	// printf("w\t%d\n", g_cub.width);
	// printf("h\t%d\n", g_cub.height);
	// printf("F\t%#.8X\n", g_cub.F);
	// printf("C\t%#.8X\n", g_cub.C);
	// int i = 0;
	// while (g_cub.matrix && g_cub.matrix[i] != NULL)
	// 	printf("%s\n", g_cub.matrix[i++]);
	if (!g_cub.height || !g_cub.width)
		ft_error("Missing or invalid R declaration", NULL);
	else if (!g_cub.C || !g_cub.F )
		ft_error("Missing colors", NULL);
	else if (!g_txt.NO || !g_txt.SO || !g_txt.EA || !g_txt.WE || !g_txt.S)
		ft_error("One or more textures are missing", NULL);
	else if (check_map())
		ft_error("Invalid map", NULL);
}
