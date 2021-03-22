/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 18:58:41 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/22 17:48:44 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	return (ft_strncmp(s, ".cub", 4));
}

char	empty_line(char *s)
{
	while (s && *s)
		if (!ft_isspace(*s++))
			return (0);
	return (1);
}
