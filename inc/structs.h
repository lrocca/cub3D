/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:29:41 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/29 20:21:12 by lrocca           ###   ########.fr       */
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
	int		life;
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
	int		p;
	float	z;
	float	raydirx0;
	float	raydiry0;
	float	raydirx1;
	float	raydiry1;
	float	floorstepx;
	float	floorstepy;
	float	floorx;
	float	floory;
	int		cellx;
	int		celly;
}				t_ray;

typedef struct	s_spr {
	int				x;
	int				y;
	double			distance;
	double			z;
	unsigned char	type;
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
	char	opt;
	char	save;
	char	audio;
	char	**map;
	char	check[2];
	char	keys[129];
	t_tex	no;
	t_tex	so;
	t_tex	we;
	t_tex	ea;
	t_tex	s[3];
	t_tex	floor;
	t_tex	ceiling;
	t_plr	plr;
	t_ray	ray;
	t_list	*spr;
	t_data	data;
	Audio	*music;
	Audio	*life;
	Audio	*success;
	Audio	*fail;
}				t_cub;

#endif
