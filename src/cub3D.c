/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 14:46:01 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/13 19:24:48 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	parse_file(t_list *list)
{
	int	len;

	while (list && (parse_options(list) || ft_strlen(list->content) == 0))
		list = list->next;
	len = ft_lstsize(list);
	if (!(g_map = malloc((len + 1) * sizeof(char*))))
		ft_error("Matrix allocation failed", NULL);
	g_map[len] = NULL;
	while (list && parse_map(list))
		list = list->next;
	check_file();
}

static void	open_map(char *file)
{
	int		n;
	int		fd;
	char	*line;
	t_list	*head;

	head = NULL;
	if (check_extension(file))
		ft_error("Invalid file extension", NULL);
	if ((fd = open(file, O_RDONLY)) < 0)
		ft_error("Opening file failed", ft_strdup(strerror(errno)));
	while ((n = get_next_line(fd, &line)) > 0)
		ft_lstadd_back(&head, ft_lstnew(line));
	close(fd);
	if (ft_strlen(line) > 0)
		ft_lstadd_back(&head, ft_lstnew(line));
	else
		free(line);
	if (n == -1)
		ft_error("Failed to get next line", NULL);
	parse_file(head);
	ft_lstclear(&head, free);
}

int			main(int ac, char **av)
{
	if (ac == 1)
		ft_error("No .cub file specified", NULL);
	else if (ac == 2 || ac == 3)
	{
		if (ac > 2)
			check_flag(av[2]);
		else
			g_cub.save = 0;
		open_map(av[1]);
		mlx();
	}
	else
		ft_error("Too many arguments", NULL);
}
