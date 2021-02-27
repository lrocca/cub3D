/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 14:46:01 by lrocca            #+#    #+#             */
/*   Updated: 2021/02/27 19:46:49 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int			ft_exit(int i)
{
	if (g_mlx.mlx)
		mlx_destroy_window(g_mlx.mlx, g_mlx.win);
	exit(i);
	return (i);
}

char		*char_to_str(char c)
{
	char	*s;

	if (!(s = malloc(2)))
		return (NULL);
	s[0] = c;
	s[1] = '\0';
	return (s);
}

void		ft_error(char *s, char *z)
{
	errno = errno ? errno : 1;
	printf("Error: ");
	printf("%s", s);
	if (z)
		printf(": %s", z);
	printf("\n");
	free(z);
	ft_exit(errno);
}

static void	parse_file(t_list *list)
{
	int	len;
	// ft_lstiter(list, (void *)&parse_options);
	while (list && (parse_options(list) || ft_strlen(list->content) == 0))
		list = list->next;
	len = ft_lstsize(list);
	if (!(g_cub.matrix = malloc((len + 1) * sizeof(char*))))
		ft_error("Matrix allocation failed", NULL);
	g_cub.matrix[len] = NULL;
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
	// printf("Opening file: %s\n", file);
	if ((fd = open(file, O_RDONLY)) < 0)
		ft_error("Error opening file", ft_strdup(strerror(errno)));
	while ((n = get_next_line(fd, &line)) > 0)
		if (ft_strlen(line) > 0)
			ft_lstadd_back(&head, ft_lstnew(line));
	close(fd);
	// if (ft_strlen(line) > 0)
		ft_lstadd_back(&head, ft_lstnew(line));
	if (n == -1)
		ft_error("Failed to get next line", NULL);
	parse_file(head);
	// free list
}

void		check_flag(char *s)
{
	g_cub.save = 0;
	if (ft_strncmp(s, "--save", 6))
		ft_error("Unknown flag", ft_strdup(s));
	else
		g_cub.save = 1;
}

int			keypress(int key)
{
	if (key == 53)
		ft_exit(0);
	return (0);
}

void		test_scene()
{
	int height;
	int width;
	mlx_put_image_to_window(g_mlx.mlx, g_mlx.win, mlx_xpm_file_to_image(g_mlx.mlx, g_txt.S, &width, &height), g_cub.width/2 - width/2, g_cub.height/2 - height/2);
	mlx_string_put(g_mlx.mlx, g_mlx.win, g_cub.width/2 - 30, g_cub.height/2 + height * 3/4, create_trgb(0, 255, 255, 255), "lrocca");
}

int			main(int ac, char **av)
{
	if (ac == 1)
		ft_error("No .cub file specified", NULL);
	else if (ac == 2 || ac == 3)
	{
		// g_cub.C = -1;
		// g_cub.F = -1;
		open_map(av[1]);
		// check flag before file
		if (ac == 3)
			check_flag(av[2]);
		g_mlx.mlx = mlx_init();
		int width;
		int height;
		mlx_get_screen_size(g_mlx.mlx, &width, &height);
		printf("%d * %d\n", width, height);
		g_mlx.win = mlx_new_window(g_mlx.mlx, g_cub.width, g_cub.height, "cub3D");
		test_scene();
		mlx_hook(g_mlx.win, 2, 1L << 0, &keypress, 0);
		mlx_hook(g_mlx.win, 17, 1L, &ft_exit, 0);
		mlx_loop(g_mlx.mlx);
	}
	else
		ft_error("Too many arguments", NULL);
}
