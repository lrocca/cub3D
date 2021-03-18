/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:03:04 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/17 18:59:43 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define WHITESPACE	 "\t\v\f\r"

static char	parse_window(char *s)
{
	if (*s == 'R')
	{
		if (g_win.w || g_win.h)
			ft_error("Multiple R declarations", NULL);
		s++;
		while (ft_isspace(*s))
			s++;
		if (!(ft_isdigit(*s) && (g_win.w = ft_atoi(s))))
			ft_error("Window width not valid", NULL);
		while (ft_isdigit(*s))
			s++;
		while (ft_isspace(*s))
			s++;
		if (!(ft_isdigit(*s) && (g_win.h = ft_atoi(s))))
			ft_error("Window height not valid", NULL);
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
		if (g_cub.no.path || !(g_cub.no.path = ft_strtrim(s, WHITESPACE)))
			ft_error("Multiple NO paths or memory allocation failed", NULL);
	}
	else if (!ft_strncmp(s, "SO", 2) && skip(&s, 2))
	{
		if (g_cub.so.path || !(g_cub.so.path = ft_strtrim(s, WHITESPACE)))
			ft_error("Multiple SO paths or memory allocation failed", NULL);
	}
	else if (!ft_strncmp(s, "WE", 2) && skip(&s, 2))
	{
		if (g_cub.we.path || !(g_cub.we.path = ft_strtrim(s, WHITESPACE)))
			ft_error("Multiple WE paths or memory allocation failed", NULL);
	}
	else if (!ft_strncmp(s, "EA", 2) && skip(&s, 2))
	{
		if (g_cub.ea.path || !(g_cub.ea.path = ft_strtrim(s, WHITESPACE)))
			ft_error("Multiple EA paths or memory allocation failed", NULL);
	}
	else if (!ft_strncmp(s, "S", 1) && skip(&s, 2))
	{
		if (g_cub.s.path || !(g_cub.s.path = ft_strtrim(s, WHITESPACE)))
			ft_error("Multiple S paths or memory allocation failed", NULL);
	}
	else
		return (0);
	return (1);
}

static int	parse_color_component(char **s, char c)
{
	int			n;
	static int	i = 0;
	static char	z = 0;

	i++;
	if (!z)
		z = c;
	if (c != z)
		i = 0;
	if (i > 3)
		ft_error("Invalid color", char_to_str(c));
	if (!(ft_isdigit(**s)))
		ft_error("Invalid color", char_to_str(c));
	n = ft_atoi(*s);
	if (n < 0 || n > 255)
		ft_error("Invalid color", char_to_str(c));
	while (ft_isdigit(**s))
		(*s)++;
	if (i == 3 && **s != '\0')
		ft_error("Invalid color", char_to_str(c));
	else if ((i == 1 || i == 2) && **s != ',')
		ft_error("Invalid color", char_to_str(c));
	(*s)++;
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
		if ((c == 'F' && g_cub.F) || (c == 'C' && g_cub.C))
			ft_error("Multiple declarations for", char_to_str(c));
		skip(&s, 1);
		r = parse_color_component(&s, c);
		g = parse_color_component(&s, c);
		b = parse_color_component(&s, c);
		if (c == 'F')
			g_cub.F = create_trgb(0, r, g, b);
		else if (c == 'C')
			g_cub.C = create_trgb(0, r, g, b);
		return (1);
	}
	return (0);
}

char		parse_options(t_list *list)
{
	while (*(char *)list->content)
	{
		if (ft_isspace(*(char *)list->content))
			;
		else if (parse_window((char *)list->content) ||
				 parse_texture((char *)list->content) ||
				 parse_color((char *)list->content))
			return (1);
		else
			return (0);
		list->content++;
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
