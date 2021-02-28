/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:29:41 by lrocca            #+#    #+#             */
/*   Updated: 2021/02/28 18:30:53 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct	s_cub
{
	int		F;
	int		C;
	char 	save;
	int		x;
	int		y;
}				t_cub;

typedef struct s_win
{
	void	*ptr;
	int		w;
	int		h;
}				t_win;
typedef struct	s_txt
{
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	char	*S;
}				t_txt;

typedef struct s_mlx
{
	void	*mlx;
}				t_mlx;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

#endif
