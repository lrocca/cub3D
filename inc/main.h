/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 14:46:21 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/29 04:02:40 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

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
# include "../lib/simple-sdl2-audio/audio.h"

# include "structs.h"

# define KEYPRESS	2
# define KEYRELEASE	3
# define MOVESPEED	0.05
# define ROTSPEED	0.05

# define AKEY		0
# define SKEY		1
# define DKEY		2
# define WKEY		13
# define MKEY		46
# define SPACEBAR	49
# define ESCKEY		53
# define LEFTARROW	123
# define RIGHTARROW	124
# define MOUSE		128

# define FLOOR		0b001
# define CEILING	0b010

# define UDIV		1
# define VDIV		1

# define MUSICPATH	"audio/minecraft.wav"
# define LIFE		500

t_cub	g_cub;

char	parse_options(t_list *list);
char	parse_map(t_list *list);
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
int		save_image_to_bmp_file(void);

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
** floor.c
*/
void	draw_floor(void);

/*
** walls.c
*/
void	draw_walls(void);

/*
** sprites.c
*/
void	sprites(double *zbuffer);

/*
** life.c
*/
void	draw_life(void);

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
** utils/check.c
*/
void	check_flag(char *s);
char	check_extension(char *s);
char	empty_line(char *s);
char	invalid_character(int x, int y);

/*
** utils/color.c
*/
int		create_trgb(int t, int r, int g, int b);

/*
** utils/render.c
*/
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
t_tex	*select_texture(int side);

/*
** utils/sprites.c
*/
void	get_sprites_distance(t_list *curr);
void	put_texel(int y, int stripe, unsigned char type);
void	remove_sprite(int x, int y);
void	update_z_axis(t_spr *spr);

/*
** utils/parsing.c
*/
char	ft_skip(char **s, int n);
void	assign_tex(char **tex, char *path);
char	*fill_line(char *s);
int		parse_color_component(char **s, char c);

/*
** utils/mlx.c
*/
int		keypress(int key);
int		keyrelease(int key);
void	update_player(void);
int		mousemove(int x, int y);
void	load_texture(t_tex *tex);

#endif
