/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:03:04 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/24 18:44:40 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	parse_window(char *s)
{
	if (*s == 'R')
	{
		if (g_cub.w || g_cub.h)
			ft_error("Multiple R declarations", NULL);
		s++;
		while (ft_isspace(*s))
			s++;
		if (!(ft_isdigit(*s) && (g_cub.w = ft_atoi(s))))
			ft_error("Window width not valid", NULL);
		while (ft_isdigit(*s))
			s++;
		while (ft_isspace(*s))
			s++;
		if (!(ft_isdigit(*s) && (g_cub.h = ft_atoi(s))))
			ft_error("Window height not valid", NULL);
		while (ft_isdigit(*s))
			s++;
		while (ft_isspace(*s))
			s++;
		if (*s != '\0')
			ft_error("Bad character after resolution", NULL);
		return (1);
	}
	return (0);
}

static char	skip(char **s, int n)
{
	*s += n;
	while (ft_isspace(**s))
		(*s)++;
	return (1);
}

static char	parse_texture(char *s)
{
	if (!ft_strncmp(s, "NO", 2) && skip(&s, 2))
	{
		assign_tex(&g_cub.no.path, s);
	}
	else if (!ft_strncmp(s, "SO", 2) && skip(&s, 2))
	{
		assign_tex(&g_cub.so.path, s);
	}
	else if (!ft_strncmp(s, "WE", 2) && skip(&s, 2))
	{
		assign_tex(&g_cub.we.path, s);
	}
	else if (!ft_strncmp(s, "EA", 2) && skip(&s, 2))
	{
		assign_tex(&g_cub.ea.path, s);
	}
	else if (!ft_strncmp(s, "S", 1) && skip(&s, 2))
	{
		assign_tex(&g_cub.s.path, s);
	}
	else
		return (0);
	return (1);
}

static int	parse_color_component(char **s, char c)
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
	skip(s, 0);
	if ((i == 0 || i == 1) && **s != ',')
		ft_error("Too few components for color", char_to_str(c));
	else if (i == 2 && **s != '\0')
		ft_error("Too many components for color", char_to_str(c));
	i++;
	skip(s, 1);
	return (n);
}

static char	parse_color(char *s)
{
	int		r;
	int		g;
	int		b;
	char	c;

	if (*s == 'F' || *s == 'C')
	{
		c = *s;
		if ((c == 'F' && g_cub.check[0]) || (c == 'C' && g_cub.check[1]))
			ft_error("Multiple declarations for", char_to_str(c));
		skip(&s, 1);
		r = parse_color_component(&s, c);
		g = parse_color_component(&s, c);
		b = parse_color_component(&s, c);
		if (c == 'F' && (g_cub.check[0] = 1))
			g_cub.f = create_trgb(0, r, g, b);
		else if (c == 'C' && (g_cub.check[1] = 1))
			g_cub.c = create_trgb(0, r, g, b);
		return (1);
	}
	return (0);
}

char		parse_options(t_list *list)
{
	char	*s;

	s = (char *)list->content;
	while (*s)
	{
		if (ft_isspace(*s))
			;
		else if ((parse_window(s) || parse_texture(s) || parse_color(s)))
			return (1);
		else
			return (0);
		s++;
	}
	return (0);
}

static char	*fill_line(char *s, int max)
{
	int		i;
	char	*out;

	if (!(out = malloc(max + 1)))
		ft_error("Matrix row allocation failed", NULL);
	out[0] = ' ';
	out[max] = '\0';
	i = 0;
	while (s[i])
	{
		out[i + 1] = s[i];
		i++;
	}
	while (i + 1 < max)
		out[1 + i++] = ' ';
	return (out);
}

char		parse_map(t_list *list, int max)
{
	static int	i = 0;

	if (i == 0 || !list)
	{
		g_cub.map[i] = fill_line("", max);
		if (!list)
			return (1);
		i++;
	}
	g_cub.map[i++] = fill_line(list->content, max);
	return (1);
}
