/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 18:08:39 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/09 18:21:11 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	draw_position(void)
{
	double	i;
	double	j;
	int		e;

	i = (g_win.w / 3) / g_cub.x;
	j = (g_win.h / 3) / g_cub.y;
	e = 0;
	if (g_win.h > 5 && g_win.w > 5)
	{
		while (e < 5)
		{
			my_mlx_pixel_put(&g_data, ((g_plr.posX * i) + e),
			((g_plr.posY * j)), 0x00000000);
			my_mlx_pixel_put(&g_data, ((g_plr.posX * i) - e),
			((g_plr.posY * j)), 0x00000000);
			my_mlx_pixel_put(&g_data, (g_plr.posX * i),
			(g_plr.posY * j - e), 0x00000000);
			my_mlx_pixel_put(&g_data, (g_plr.posX * i),
			(g_plr.posY * j + e), 0x00000000);
			e++;
		}
	}
}

void	draw_square(int x, int y)
{
	int		color;
	double	i;
	double	j;
	int		a;
	int		b;

	i = (g_win.w / 3) / g_cub.x;
	j = (g_win.h / 3) / g_cub.y;
	a = 0;
	while ((x + a) < (x + i))
	{
		b = 0;
		while ((y + b) < (y + j))
		{
			if (g_map[y][x] == '1')
				color = g_cub.C;
			// // else if (chose_color(x, y) == 1)
			else if (g_map[y][x] == '0')
				color = g_cub.F;
			else
				color = 0;
			// 	color = g_tex.color_sky;
			my_mlx_pixel_put(&g_data, ((x * i) + a), ((y * j) + b), color);
			b++;
		}
		a++;
	}
}

void	draw_minimap(void)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < g_cub.x)
	{
		while (y < g_cub.y)
		{
			draw_square(x, y);
			y++;
		}
		y = 0;
		x++;
	}
	draw_position();
}

void	get_distance(int x)//, double cameraX)
{
	int mapX = (int)g_plr.posX;
	int mapY = (int)g_plr.posY;
	//length of ray from current position to next x or y-side
	double sideDistX;
	double sideDistY;

	 //length of ray from one x or y-side to next x or y-side
	double deltaDistX = fabs(1 / g_ray.x);
	double deltaDistY = fabs(1 / g_ray.y);
	double perpWallDist;

	// //what direction to step in x or y-direction (either +1 or -1)
	int stepX;
	int stepY;

	int hit = 0; //was there a wall hit?
	int side; //was a NS or a EW wall hit?

	//calculate step and initial sideDist
	if (g_ray.x < 0)
	{
		stepX = -1;
		sideDistX = (g_plr.posX - mapX) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (mapX + 1.0 - g_plr.posX) * deltaDistX;
	}
	if (g_ray.y < 0)
	{
		stepY = -1;
		sideDistY = (g_plr.posY - mapY) * deltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = (mapY + 1.0 - g_plr.posY) * deltaDistY;
	}

	//perform DDA
	while (hit == 0)
	{
		//jump to next map square, OR in x-direction, OR in y-direction
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			mapX += stepX;
			side = 0;
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
		}
		//Check if ray has hit a wall
		if (g_map[mapY][mapX] == '1') hit = 1;
	}
	//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
	if (side == 0)
		perpWallDist = (mapX - g_plr.posX + (1 - stepX) / 2) / g_ray.x;
	else
		perpWallDist = (mapY - g_plr.posY + (1 - stepY) / 2) / g_ray.y;

	//Calculate height of line to draw on screen
	int lineHeight = (int)(g_win.h / perpWallDist);

	int color;

	//calculate lowest and highest pixel to fill in current stripe
	int drawStart = -lineHeight / 2 + g_win.h / 2;
	if (drawStart < 0)
		drawStart = 0;
	int drawEnd = lineHeight / 2 + g_win.h / 2;
	if (drawEnd >= g_win.h)
		drawEnd = g_win.h - 1;

	//calculate value of wallX
	double wallX; //where exactly the wall was hit
	if (side == 0)
		wallX = g_plr.posY + perpWallDist * g_ray.y;
	else
		wallX = g_plr.posX + perpWallDist * g_ray.x;
	wallX -= floor((wallX));

	//x coordinate on the texture
	int texX = (int)(wallX * (double)TEXWIDTH);
	if (side == 0 && g_ray.x > 0)
		texX = TEXWIDTH - texX - 1;
	if (side == 1 && g_ray.y < 0)
		texX = TEXWIDTH - texX - 1;

	// How much to increase the texture coordinate per screen pixel
	double step = 1.0 * TEXHEIGHT / lineHeight;
	// Starting texture coordinate
	double texPos = (drawStart - g_win.h / 2 + lineHeight / 2) * step;
	int y = 0;
	while (y < drawStart)
	{
		my_mlx_pixel_put(&g_data, x, y, g_cub.C);
		y++;
	}
	y = drawStart;
	void	*texture;
	if (side == 1)
	{
		if (g_ray.y > 0)
			texture = g_tex.SO;
		else
			texture = g_tex.NO;
	}
	else
	{
		if (g_ray.x > 0)
			texture = g_tex.EA;
		else
			texture = g_tex.WE;
	}
	while (y < drawEnd)
	{
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		int texY = (int)texPos & (TEXHEIGHT - 1);
		texPos += step;
		color = ((unsigned int *)texture)[TEXHEIGHT * texY + texX];
		//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		// if(side == 1) color = (color >> 1) & 8355711;
		my_mlx_pixel_put(&g_data, x, y, color);
		y++;
	}
	while (y < g_win.h)
	{
		my_mlx_pixel_put(&g_data, x, y, g_cub.F);
		y++;
	}
}

void	ray(void)
{
	for(int x = 0; x < g_win.w; x++)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)g_win.w - 1; //x-coordinate in camera space
		g_ray.x = g_plr.dirX + g_plr.planeX * cameraX;
		g_ray.y = g_plr.dirY + g_plr.planeY * cameraX;
		// printf("%f\n", cameraX);
		get_distance(x);//, cameraX);
	}
}
