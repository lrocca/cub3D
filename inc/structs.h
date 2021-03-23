/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:29:41 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/23 19:22:41 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct	s_data {
	int		endian;
	int		line_length;
	int		bits_per_pixel;
	void	*img;
	void	*addr;
}				t_data;

typedef struct	s_tex {
	int		width;
	int		height;
	char	*path;
	t_data	data;
}				t_tex;

typedef struct	s_plr {
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
}				t_plr;

typedef struct	s_ray {
	int		mapx;
	int		mapy;
	int		texx;
	int		stepx;
	int		stepy;
	int		drawstart;
	int		drawend;
	int		line_height;
	double	x;
	double	y;
	double	dist;
	double	wallx;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	spritex;
	double	spritey;
	double	invdet;
	double	transformx;
	double	transformy;
	int		spriteheight;
	int		spritewidth;
	int		drawstarty;
	int		drawendy;
	int		drawstartx;
	int		drawendx;
	int		vmove;
	int		spritescreenx;
	int		udiv;
	int		vdiv;
	t_tex	*texture;
}				t_ray;

typedef struct	s_spr {
	int		x;
	int		y;
	double	distance;
}				t_spr;

typedef struct	s_cub {
	int		w;
	int		h;
	int		f;
	int		c;
	int		x;
	int		y;
	void	*mlx;
	void	*win;
	char	save;
	char	**map;
	char	check[2];
	char	keys[129];
	t_tex	no;
	t_tex	so;
	t_tex	we;
	t_tex	ea;
	t_tex	s;
	t_plr	plr;
	t_ray	ray;
	t_list	*spr;
	t_data	data;
}				t_cub;

#endif
