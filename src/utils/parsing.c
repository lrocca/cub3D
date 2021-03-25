/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 18:25:45 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/25 19:28:48 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define WHITESPACE	" \t\v\f\r"

char	ft_skip(char **s, int n)
{
	*s += n;
	while (ft_isspace(**s))
		(*s)++;
	return (1);
}

void	assign_tex(char **tex, char *path)
{
	if (*tex)
		ft_error("Multiple texture paths", NULL);
	if (!(*tex = ft_strtrim(path, WHITESPACE)))
		ft_error("Texture path allocation failed", NULL);
}

char	*fill_line(char *s)
{
	int		i;
	char	*out;

	if (!(out = malloc(g_cub.x + 1)))
		ft_error("Matrix row allocation failed", NULL);
	out[0] = ' ';
	out[g_cub.x] = '\0';
	i = 0;
	while (s[i])
	{
		out[i + 1] = s[i];
		i++;
	}
	while (i + 1 < g_cub.x)
		out[1 + i++] = ' ';
	return (out);
}

int		parse_color_component(char **s, char c)
{
	int			n;
	static char	i = 0;
	static char	z = 0;

	if (!z)
		z = c;
	else if (c != z && (z = c))
		i = 0;
	if (!(ft_isdigit(**s)))
		ft_error("Invalid color", char_to_str(c));
	n = ft_atoi(*s);
	if (n < 0 || n > 255)
		ft_error("Invalid color component", char_to_str(c));
	while (ft_isdigit(**s))
		(*s)++;
	ft_skip(s, 0);
	if ((i == 0 || i == 1) && **s != ',')
		ft_error("Too few components for color", char_to_str(c));
	else if (i == 2 && **s != '\0')
		ft_error("Too many components for color", char_to_str(c));
	i++;
	ft_skip(s, 1);
	return (n);
}
