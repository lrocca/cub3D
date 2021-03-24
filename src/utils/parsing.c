/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 18:25:45 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/24 18:32:12 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define WHITESPACE	" \t\v\f\r"

void	assign_tex(char **tex, char *path)
{
	if (*tex)
		ft_error("Multiple texture paths", NULL);
	if (!(*tex = ft_strtrim(path, WHITESPACE)))
		ft_error("Texture path allocation failed", NULL);
}
