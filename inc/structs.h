/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:29:41 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/22 18:28:19 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct	s_win
{
	void	*ptr;
	int		w;
	int		h;
}				t_win;

typedef struct	s_data {
	void	*img;
	void	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_tex
{
	char	*path;
	int		width;
	int		height;
	t_data	data;
}				t_tex;

typedef struct	s_mlx
{
	void	*mlx;
	char	keys[129];
}				t_mlx;

typedef struct	s_plr
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
}				t_plr;

typedef struct	s_ray
{
	double	x;
	double	y;
	double	perpWallDist;
}				t_ray;

typedef struct	s_spr
{
	int		x;
	int		y;
	double	distance;
}				t_spr;

typedef struct	s_cub
{
	int		F;
	int		C;
	char	check[2];
	char	save;
	int		x;
	int		y;
	t_tex	no;
	t_tex	so;
	t_tex	we;
	t_tex	ea;
	t_tex	s;
	t_list	*spr;
	char	**map;
	t_plr	plr;
}				t_cub;

#endif
