/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 15:58:02 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/24 19:19:59 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_exit(int i)
{
	if (g_cub.data.img)
		mlx_destroy_image(g_cub.mlx, g_cub.data.img);
	if (g_cub.win)
		mlx_destroy_window(g_cub.mlx, g_cub.win);
	ft_lstclear(&g_cub.spr, free);
	exit(i);
	return (i);
}

void	ft_error(char *s, char *z)
{
	if (!errno)
		errno = 1;
	printf("Error\n");
	printf("%s", s);
	if (z)
	{
		printf(": %s", z);
		free(z);
	}
	printf("\n");
	ft_exit(errno);
}

char	*char_to_str(char c)
{
	char	*s;

	if (!(s = malloc(2)))
		return (NULL);
	s[0] = c;
	s[1] = '\0';
	return (s);
}
