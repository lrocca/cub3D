/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 14:46:21 by lrocca            #+#    #+#             */
/*   Updated: 2021/02/24 19:41:39 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# include "../libft/libft.h"
# include "structs.h"

t_cub	g_cub;
t_txt	g_txt;

char	*char_to_str(char c);
void	ft_exit(char *s, char *z);

int		create_trgb(int t, int r, int g, int b);

int		get_next_line(int fd, char **line);

char	parse_options(t_list *list);

#endif
