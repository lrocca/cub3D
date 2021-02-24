/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 14:46:01 by lrocca            #+#    #+#             */
/*   Updated: 2021/02/24 19:54:35 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

char		*char_to_str(char c)
{
	char	*s;

	if (!(s = malloc(2)))
		return ("Failed to allocate char");
	s[0] = c;
	s[1] = '\0';
	return (s);
}

void		ft_exit(char *s, char *z)
{
	int	n;

	n = ft_strlen(s) ? 1 : 0;
	errno = errno ? errno : n;
	z ? printf("%s%s\n", s, z) : printf("%s\n", s);
	free(z);
	// free della roba
	exit(errno);
}

static void	parse_file(t_list *list)
{
	// ft_lstiter(list, (void *)&parse_options);
	while (parse_options(list))
		list = list->next;
}

static void	open_map(char *file)
{
	int		n;
	int		fd;
	char	*line;
	t_list	*head;

	head = NULL;
	// printf("Opening file: %s\n", file);
	if ((fd = open(file, O_RDONLY)) < 0)
		ft_exit("Error opening file: ", ft_strdup(strerror(errno)));
	while ((n = get_next_line(fd, &line)) > 0)
		if (ft_strlen(line) > 0)
			ft_lstadd_back(&head, ft_lstnew(line));
	close(fd);
	if (ft_strlen(line) > 0)
		ft_lstadd_back(&head, ft_lstnew(line));
	if (n == -1)
		ft_exit("Error: Failed to get next line", NULL);
	parse_file(head);
	// free list
}

void		check_flag(char *s)
{
	g_cub.save = 0;
	if (ft_strncmp(s, "--save", 6))
		ft_exit("Syntax error: Unknown flag: ", ft_strdup(s));
	else
		g_cub.save = 1;
}

int			main(int ac, char **av)
{
	if (ac == 1)
		ft_exit("Syntax error: No .cub file specified", NULL);
	else if (ac == 2 || ac == 3)
	{
		open_map(av[1]);
		printf("NO\t%s\n", g_txt.NO);
		printf("SO\t%s\n", g_txt.SO);
		printf("EA\t%s\n", g_txt.EA);
		printf("WE\t%s\n", g_txt.WE);
		printf("S\t%s\n", g_txt.S);
		printf("w\t%d\n", g_cub.wwidth);
		printf("h\t%d\n", g_cub.wheight);
		printf("F\t%#.8X\n", g_cub.F);
		printf("C\t%#.8X\n", g_cub.C);
		// check flag before file
		if (ac == 3)
			check_flag(av[2]);
	}
	else
		ft_exit("Syntax error: Too many arguments", NULL);
}
