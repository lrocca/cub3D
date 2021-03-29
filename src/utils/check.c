/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 18:58:41 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/29 03:54:25 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#define VALIDCHAR " 1"

void	check_flag(char *s)
{
	if (ft_strlen(s) != 6 || ft_strncmp(s, "--save", 6))
		ft_error("Unknown flag", ft_strdup(s));
	else
		g_cub.save = 1;
}

char	check_extension(char *s)
{
	if (!(s = ft_strrchr(s, '.')))
		return (1);
	return (ft_strlen(s) != 4 || ft_strncmp(s, ".cub", 4));
}

char	empty_line(char *s)
{
	while (s && *s)
		if (!ft_isspace(*s++))
			return (0);
	return (1);
}

char	invalid_character(int x, int y)
{
	if (y > 0 && !ft_ischarset(g_cub.map[y - 1][x], VALIDCHAR))
		return (1);
	if (x > 0 && !ft_ischarset(g_cub.map[y][x - 1], VALIDCHAR))
		return (1);
	if (y < g_cub.y - 1 && !ft_ischarset(g_cub.map[y + 1][x], VALIDCHAR))
		return (1);
	if (x < g_cub.x - 1 && !ft_ischarset(g_cub.map[y][x + 1], VALIDCHAR))
		return (1);
	return (0);
}
