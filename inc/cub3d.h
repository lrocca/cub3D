/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 14:46:21 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/22 17:49:31 by lrocca           ###   ########.fr       */
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
# include <math.h>

# include "../lib/libft/libft.h"
# include "../lib/mlx_mms/mlx.h"
# include "../lib/mlx_opengl/mlx.h"

# include "structs.h"

# define KEYPRESS	2
# define KEYRELEASE	3
# define MOVESPEED	0.05
# define ROTSPEED	0.05
# define TEXWIDTH	64
# define TEXHEIGHT	64

# define ESCKEY		53
# define WKEY		13
# define SKEY		1
# define AKEY		0
# define DKEY		2
# define LEFTARROW	123
# define RIGHTARROW	124

t_mlx	g_mlx;
t_win	g_win;
t_cub	g_cub;
t_data	g_data;
t_ray	g_ray;

char	parse_options(t_list *list);
char	parse_map(t_list *list, int max);
void	check_file(void);

/*
** gnl.c
*/
int		get_next_line(int fd, char **line);

/*
** mlx.c
*/
void	mlx(void);

/*
** bmp.c
*/
int		save_image_to_bmp_file(int width, int height);

/*
** move.c
*/
void	move_fwd(void);
void	move_back(void);
void	move_left(void);
void	move_right(void);

/*
** rotate.c
*/
void	rotate_left(void);
void	rotate_right(void);

/*
** walls.c
*/
void	draw_walls(void);

/*
** sprites.c
*/
void	sprites(double *zBuffer);

/*
** minimap.c
*/
void	draw_minimap(void);
void	test_scene(void);

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
char	empty_line(char *s);

/*
** utils_color.c
*/
int		create_trgb(int t, int r, int g, int b);

/*
** utils_render.c
*/
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif
