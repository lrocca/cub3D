/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 15:58:02 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/20 16:37:59 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_exit(int i)
{
	if (g_win.ptr)
		mlx_destroy_window(g_mlx.mlx, g_win.ptr);
	ft_lstclear(&g_cub.spr, free);
	exit(i);
	return (i);
}

void	ft_error(char *s, char *z)
{
	errno = errno ? errno : 1;
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
