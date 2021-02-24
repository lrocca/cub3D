/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:29:41 by lrocca            #+#    #+#             */
/*   Updated: 2021/02/24 16:36:42 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct	s_cub
{
	int		F;
	int		C;
	char 	save;
	int		wwidth;
	int		wheight;
	char	**matrix;
}				t_cub;

typedef struct	s_txt
{
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	char	*S;
}				t_txt;

#endif
