/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 14:46:21 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/02 16:57:43 by lrocca           ###   ########.fr       */
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
#include <math.h>
# include "../mlx_mms/mlx.h"
# include "../mlx_opengl/mlx.h"

# include "../libft/libft.h"
# include "structs.h"

t_mlx	g_mlx;
t_win	g_win;
t_cub	g_cub;
t_txt	g_txt;
t_data	g_data;
t_plr	g_plr;
t_ray	g_ray;
char	**g_map;

/*
** utils.c
*/
int		ft_exit(int i);
void	ft_error(char *s, char *z);
char	*char_to_str(char c);

/*
** utils_check.c
*/
void	check_flag(char *s);
char	check_extension(char *s);

/*
** utils_color.c
*/
int		create_trgb(int t, int r, int g, int b);

/*
** utils_render.c
*/
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

/*
** gnl.c
*/
int		get_next_line(int fd, char **line);

/*
** mlx.c
*/
void	mlx(void);

char	parse_options(t_list *list);
char	parse_map(t_list *list);

void	check_file(void);

/*
** render.c
*/
void	ray(void);
void	draw_minimap(void);

#endif
