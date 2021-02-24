/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 14:45:52 by lrocca            #+#    #+#             */
/*   Updated: 2021/02/22 19:42:13 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static char	*ft_bufjoin(char *line, char buffer[128])
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	if (!(new = malloc(ft_strlen(line) + ft_strlen(buffer) + 1)))
		return (NULL);
	while (line && line[j])
		new[i++] = line[j++];
	if (line)
	{
		free(line);
		line = NULL;
	}
	j = 0;
	while (buffer && buffer[j])
		new[i++] = buffer[j++];
	new[i] = '\0';
	return (new);
}

int			get_next_line(int fd, char **line)
{
	int		n;
	int		i;
	char	c;
	char	buffer[128];

	if (fd < 0 || read(fd, 0, 0) < 0 || !line)
		return (-1);
	*line = NULL;
	i = 0;
	while ((n = read(fd, &c, 1)) > 0 && c != '\n')
	{
		buffer[i] = c;
		i++;
		if (i == 127)
		{
			puts("ciao");
			buffer[i] = '\0';
			*line = ft_bufjoin(*line, buffer);
			i = 0;
		}
	}
	buffer[i] = '\0';
	*line = ft_bufjoin(*line, buffer);
	return (n);
}
