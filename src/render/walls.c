/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 18:08:39 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/17 19:34:44 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_tex	*select_texture(int side)
{
	t_tex	*texture;

	if (side == 1)
	{
		if (g_ray.y > 0)
			texture = &g_cub.so;
		else
			texture = &g_cub.no;
	}
	else
	{
		if (g_ray.x > 0)
			texture = &g_cub.ea;
		else
			texture = &g_cub.we;
	}
	return (texture);
}

void	draw_column(int x)
{
	int mapX = (int)g_cub.plr.posX;
	int mapY = (int)g_cub.plr.posY;
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

	//calculate step and initial sideDist
	if (g_ray.x < 0 && (stepX = -1))
		sideDistX = (g_cub.plr.posX - mapX) * deltaDistX;
	else if ((stepX = 1))
		sideDistX = (mapX + 1.0 - g_cub.plr.posX) * deltaDistX;
	if (g_ray.y < 0 && (stepY = -1))
		sideDistY = (g_cub.plr.posY - mapY) * deltaDistY;
	else if ((stepY = 1))
		sideDistY = (mapY + 1.0 - g_cub.plr.posY) * deltaDistY;

	int hit = 0; //was there a wall hit?
	int side;	 //was a NS or a EW wall hit?

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
		if (g_cub.map[mapY][mapX] == '1')
			hit = 1;
	}
	//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
	if (side == 0)
		perpWallDist = (mapX - g_cub.plr.posX + (1 - stepX) / 2) / g_ray.x;
	else
		perpWallDist = (mapY - g_cub.plr.posY + (1 - stepY) / 2) / g_ray.y;

	//Calculate height of line to draw on screen
	int lineHeight = (int)(g_win.h / perpWallDist);

	//calculate lowest and highest pixel to fill in current stripe
	int draw_start = -lineHeight / 2 + g_win.h / 2;
	if (draw_start < 0)
		draw_start = 0;
	int draw_end;
	draw_end = lineHeight / 2 + g_win.h / 2;
	if (draw_end >= g_win.h)
		draw_end = g_win.h - 1;

	//calculate value of wallX
	double wallX; //where exactly the wall was hit
	if (side == 0)
		wallX = g_cub.plr.posY + perpWallDist * g_ray.y;
	else
		wallX = g_cub.plr.posX + perpWallDist * g_ray.x;
	wallX -= floor((wallX));

	t_tex *texture;
	texture = select_texture(side);

	//x coordinate on the texture
	int	texX;
	texX = (int)(wallX * (double)texture->width);
	if (side == 0 && g_ray.x > 0)
		texX = texture->width - texX - 1;
	if (side == 1 && g_ray.y < 0)
		texX = texture->width - texX - 1;

	// How much to increase the texture coordinate per screen pixel
	double	step;
	step = 1.0 * texture->height / lineHeight;
	// Starting texture coordinate
	double	texPos;
	texPos = (draw_start - g_win.h / 2 + lineHeight / 2) * step;
	int y = 0;

	while (y < draw_start)
		my_mlx_pixel_put(&g_data, x, y++, g_cub.C);
	y = draw_start;
	int color;
	while (y < draw_end)
	{
		int texY = (int)texPos % texture->height;
		texPos += step;
		color = ((int *)(texture->data.addr))[texture->height * texY + texX];
		my_mlx_pixel_put(&g_data, x, y, color);
		y++;
	}
	while (y < g_win.h)
		my_mlx_pixel_put(&g_data, x, y++, g_cub.F);
	//SET THE ZBUFFER FOR THE SPRITE CASTING
	g_ray.perpWallDist = perpWallDist; //perpendicular distance is used
}

void draw_walls(void)
{
	int x;
	double zBuffer[g_win.w];

	x = 0;
	while (x < g_win.w)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)g_win.w - 1; //x-coordinate in camera space
		g_ray.x = g_cub.plr.dirX + g_cub.plr.planeX * cameraX;
		g_ray.y = g_cub.plr.dirY + g_cub.plr.planeY * cameraX;
		draw_column(x);
		zBuffer[x] = g_ray.perpWallDist;
		x++;
	}
	if (g_cub.spr)
		sprites(zBuffer);
}
