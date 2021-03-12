/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 18:15:40 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/12 18:17:08 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
** > init sprites
** calculate distance from single
** sort by furthest
** draw first (furthest) to last (closest)
*/

//sort algorithm
//sort the sprites based on distance
// void sortSprites(int* order, double* dist, int amount)
// {
// 	std::vector<std::pair<double, int>> sprites(amount);
// 	for (int i = 0; i < amount; i++)
// 	{
// 		sprites[i].first = dist[i];
// 		sprites[i].second = order[i];
// 	}
// 	std::sort(sprites.begin(), sprites.end());
// 	// restore in reverse order to go from farthest to nearest
// 	for(int i = 0; i < amount; i++)
// 	{
// 		dist[i] = sprites[amount - i - 1].first;
// 		order[i] = sprites[amount - i - 1].second;
// 	}
// }

void sprite(double *zBuffer)
{
	t_list	*curr;
	t_spr	*spr;

	//sort sprites from far to close
	curr = g_cub.spr;
	while (curr)
	{
		spr = curr->content;
		spr->distance = ((g_plr.posX - spr->x) * (g_plr.posX - spr->x) + (g_plr.posY - spr->y) * (g_plr.posY - spr->y)); //sqrt not taken, unneeded
		curr = curr->next;
	}

	// sort function

	//after sorting the sprites, do the projection and draw them
	curr = g_cub.spr;
	while (curr)
	{
		spr = curr->content;

		//translate sprite position to relative to camera
		double spriteX = spr->x - g_plr.posX + 0.5;
		double spriteY = spr->y - g_plr.posY + 0.5;

		//transform sprite with the inverse camera matrix
		// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
		// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
		// [ planeY   dirY ]                                          [ -planeY  planeX ]

		double invDet = 1.0 / (g_plr.planeX * g_plr.dirY - g_plr.dirX * g_plr.planeY); //required for correct matrix multiplication

		double transformX = invDet * (g_plr.dirY * spriteX - g_plr.dirX * spriteY);
		double transformY = invDet * (-g_plr.planeY * spriteX + g_plr.planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

		int spriteScreenX = (int)((g_win.w / 2) * (1 + transformX / transformY));

		int vMoveScreen = (int)(64.0 / transformY);
		//calculate height of the sprite on screen
		int spriteHeight = abs((int)(g_win.h / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + g_win.h / 2 + vMoveScreen;
		if (drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + g_win.h / 2 + vMoveScreen;
		if (drawEndY >= g_win.h)
			drawEndY = g_win.h - 1;

		//calculate width of the sprite
		int spriteWidth = abs((int)(g_win.h / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0)
			drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= g_win.w)
			drawEndX = g_win.w - 1;

		int texX;
		unsigned int	*texture = g_tex.S;
		//loop through every vertical stripe of the sprite on screen
		int stripe = drawStartX;
		while (stripe < drawEndX)
		{
			texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * TEXWIDTH / spriteWidth) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if (transformY > 0 && stripe > 0 && stripe < g_win.w && transformY < zBuffer[stripe])
			{
				int y = drawStartY;
				while (y < drawEndY) //for every pixel of the current stripe
				{
					int d = (y - vMoveScreen) * 256 - g_win.h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
					int texY = ((d * TEXHEIGHT) / spriteHeight) / 256;
					int color = texture[TEXWIDTH * texY + texX]; //get current color from the texture
					if ((color & 0x00FFFFFF) != 0) //paint pixel if it isn't black, black is the invisible color
						my_mlx_pixel_put(&g_data, stripe, y, color);
					y++;
				}
			}
			stripe++;
		}
		curr = curr->next;
	}
}
