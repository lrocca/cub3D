/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 14:46:01 by lrocca            #+#    #+#             */
/*   Updated: 2021/02/28 19:23:32 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	parse_file(t_list *list)
{
	int	len;
	// ft_lstiter(list, (void *)&parse_options);
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
	// printf("Opening file: %s\n", file);
	if (check_extension(file))
		ft_error("Invalid file extension", NULL);
	if ((fd = open(file, O_RDONLY)) < 0)
		ft_error("Opening file failed", ft_strdup(strerror(errno)));
	while ((n = get_next_line(fd, &line)) > 0)
		// if (ft_strlen(line) > 0)
			ft_lstadd_back(&head, ft_lstnew(line));
	close(fd);
	if (ft_strlen(line) > 0)
		ft_lstadd_back(&head, ft_lstnew(line));
	if (n == -1)
		ft_error("Failed to get next line", NULL);
	parse_file(head);
	// free list
}

int			keypress(int key)
{
	if (key == 53)
		ft_exit(0);
	return (0);
}

static void	mlx(void)
{
	g_mlx.mlx = mlx_init();
	g_win.ptr = mlx_new_window(g_mlx.mlx, g_win.w, g_win.h, "cub3D");
	// test_scene();
	g_data.img = mlx_new_image(g_mlx.mlx, g_win.w, g_win.h);
	g_data.addr = mlx_get_data_addr(g_data.img, &g_data.bits_per_pixel, &g_data.line_length, &g_data.endian);
	draw_minimap();
	mlx_put_image_to_window(g_mlx.mlx, g_win.ptr, g_data.img, g_win.w/2, g_win.h/2);
	mlx_hook(g_win.ptr, 2, 1L << 0, &keypress, 0);
	mlx_hook(g_win.ptr, 17, 1L, &ft_exit, 0);
	mlx_loop(g_mlx.mlx);
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
		// printf("%d * %d\n", g_cub.x, g_cub.y);
		// check flag before file
		if (ac == 3)
			check_flag(av[2]);
		mlx();
	}
	else
		ft_error("Too many arguments", NULL);
}
