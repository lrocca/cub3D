/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 14:46:01 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/17 19:23:54 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	max_len(t_list *list)
{
	int max;
	int	len;

	max = 0;
	while (list && list->content)
	{
		len = ft_strlen(list->content);
		max = max > len ? max : len;
		list = list->next;
	}
	return (max);
}

static void	parse_file(t_list *list)
{
	int	len;
	int	max;

	while (list && (parse_options(list) || ft_strlen(list->content) == 0))
		list = list->next;
	len = ft_lstsize(list) + 2;
	if (!(g_cub.map = malloc((len + 1) * sizeof(char*))))
		ft_error("Matrix allocation failed", NULL);
	g_cub.map[len] = NULL;

	max = max_len(list) + 2;
	while (list && parse_map(list, max))
		list = list->next;
	parse_map(NULL, max);

	check_file();
}

static void	open_file(char *file)
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
		open_file(av[1]);
		mlx();
	}
	else
		ft_error("Too many arguments", NULL);
}