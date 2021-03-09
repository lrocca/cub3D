/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 18:58:41 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/09 18:21:11 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void		check_flag(char *s)
{
	g_cub.save = 0;
	if (ft_strncmp(s, "--save", 6))
		ft_error("Unknown flag", ft_strdup(s));
	else
		g_cub.save = 1;
}

char	check_extension(char *s)
{
	s = ft_strrchr(s, '.');
	if (!s)
		return (1);
	return (ft_strncmp(s, ".cub", 4));
}
