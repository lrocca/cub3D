/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:03:04 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/13 19:24:48 by lrocca           ###   ########.fr       */
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
		if (g_cub.NO || !(g_cub.NO = ft_strtrim(s, WHITESPACE)))
			ft_error("Multiple NO paths or memory allocation failed", NULL);
	}
	else if (!ft_strncmp(s, "SO", 2) && skip(&s, 2))
	{
		if (g_cub.SO || !(g_cub.SO = ft_strtrim(s, WHITESPACE)))
			ft_error("Multiple SO paths or memory allocation failed", NULL);
	}
	else if (!ft_strncmp(s, "WE", 2) && skip(&s, 2))
	{
		if (g_cub.WE || !(g_cub.WE = ft_strtrim(s, WHITESPACE)))
			ft_error("Multiple WE paths or memory allocation failed", NULL);
	}
	else if (!ft_strncmp(s, "EA", 2) && skip(&s, 2))
	{
		if (g_cub.EA || !(g_cub.EA = ft_strtrim(s, WHITESPACE)))
			ft_error("Multiple EA paths or memory allocation failed", NULL);
	}
	else if (!ft_strncmp(s, "S", 1) && skip(&s, 2))
	{
		if (g_cub.S || !(g_cub.S = ft_strtrim(s, WHITESPACE)))
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
		else if (parse_window((char *)list->content) || \
		parse_texture((char *)list->content) || \
		parse_color((char *)list->content))
			return (1);
		else // linea senza lettere ovvero mappa
			return (0);
		list->content++;
	}
	return (0);
}

char		parse_map(t_list *list)
{
	static int	i = 0;

	if (!(g_map[i] = ft_strdup(list->content)))
		ft_error("Matrix row allocation failed", NULL);
	i++;
	return (1);
}
