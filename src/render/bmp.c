/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 18:45:25 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/13 19:46:41 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_default_value(unsigned char header[])
{
	unsigned int	bi_size;
	unsigned int	bf_off_bits;
	unsigned short	bi_planes;

	bi_size = 40;
	bf_off_bits = 54;
	bi_planes = 1;
	ft_bzero(header, 54);
	ft_memcpy(header, "BM", 2);
	ft_memcpy(header + 10, &bf_off_bits, 4);
	ft_memcpy(header + 14, &bi_size, 4);
	ft_memcpy(header + 26, &bi_planes, 2);
}

void	set_header(unsigned char header[], int width,
					int height, int width_in_bytes)
{
	unsigned short	bitcount;
	unsigned int	imagesize;
	unsigned int	filesize;

	bitcount = 24;
	imagesize = width_in_bytes * height;
	filesize = 54 + imagesize;
	set_default_value(header);
	ft_memcpy(header + 2, &filesize, 4);
	ft_memcpy(header + 18, &width, 4);
	ft_memcpy(header + 22, &height, 4);
	ft_memcpy(header + 28, &bitcount, 2);
	ft_memcpy(header + 34, &imagesize, 4);
}

void	set_pixels(unsigned char *buf, unsigned int width_in_bytes,
					int width, int height)
{
	int	i;
	int	j;
	int	tmp;

	width_in_bytes = ((width * 24 + 31) / 32) * 4;
	tmp = height;
	i = 0;
	while (i < height)
	{
		j = -1;
		tmp--;
		while (++j < width)
		{
			buf[tmp * width_in_bytes + j * 3 + 0] = \
			(*((unsigned int*)(g_data.addr + (i * g_data.line_length + j \
			* (g_data.bits_per_pixel / 8))))) & 0xff;
			buf[tmp * width_in_bytes + j * 3 + 1] = \
			((*((unsigned int*)(g_data.addr + (i * g_data.line_length + j \
			* (g_data.bits_per_pixel / 8))))) >> 8) & 0xff;
			buf[tmp * width_in_bytes + j * 3 + 2] = \
			((*((unsigned int*)(g_data.addr + (i * g_data.line_length + j \
			* (g_data.bits_per_pixel / 8))))) >> 16) & 0xff;
		}
		i++;
	}
}

void	writefile(unsigned char header[], unsigned char *buf, unsigned int size)
{
	int	fd;

	fd = open("./save.bmp", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	write(fd, header, 54);
	write(fd, (char*)buf, size);
	close(fd);
}

int		save_image_to_bmp_file(int width, int height)
{
	unsigned char	header[54];
	unsigned char	*buff;
	unsigned int	width_in_bytes;
	unsigned int	size;

	width_in_bytes = ((width * 24 + 31) / 32) * 4;
	size = width_in_bytes * height;
	set_header(header, width, height, width_in_bytes);
	if (!(buff = malloc(size)))
		return (0);
	set_pixels(buff, width_in_bytes, width, height);
	writefile(header, buff, size);
	free(buff);
	return (1);
}