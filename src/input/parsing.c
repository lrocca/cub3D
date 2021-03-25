/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:03:04 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/25 19:32:35 by lrocca           ###   ########.fr       */
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

static char	parse_texture(char *s)
{
	if (!ft_strncmp(s, "NO", 2) && ft_skip(&s, 2))
	{
		assign_tex(&g_cub.no.path, s);
	}
	else if (!ft_strncmp(s, "SO", 2) && ft_skip(&s, 2))
	{
		assign_tex(&g_cub.so.path, s);
	}
	else if (!ft_strncmp(s, "WE", 2) && ft_skip(&s, 2))
	{
		assign_tex(&g_cub.we.path, s);
	}
	else if (!ft_strncmp(s, "EA", 2) && ft_skip(&s, 2))
	{
		assign_tex(&g_cub.ea.path, s);
	}
	else if (!ft_strncmp(s, "S", 1) && ft_skip(&s, 2))
	{
		assign_tex(&g_cub.s.path, s);
	}
	else
		return (0);
	return (1);
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
		ft_skip(&s, 1);
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

char		parse_map(t_list *list)
{
	static int	i = 0;

	if (i == 0 || !list)
	{
		g_cub.map[i] = fill_line("");
		if (!list)
			return (1);
		i++;
	}
	g_cub.map[i++] = fill_line(list->content);
	return (1);
}
