/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 18:15:40 by lrocca            #+#    #+#             */
/*   Updated: 2021/03/23 15:11:01 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** > init sprites
** calculate distance from single
** sort by furthest
** draw first (furthest) to last (closest)
*/

static void	get_sprites_distance(t_list *curr, t_spr *spr)
{
	while (curr)
	{
		spr = curr->content;
		spr->distance = ((g_cub.plr.posx - spr->x) * (g_cub.plr.posx - spr->x)
						+ (g_cub.plr.posy - spr->y) * (g_cub.plr.posy - spr->y));
		curr = curr->next;
	}
}

static t_list *find_lowest(t_list *curr, t_list *prev)
{
	double	n;

	if (!curr)
		return (NULL);
	n = ((t_spr*)curr->content)->distance;
	while (curr->next) // itera la lista
	{
		if (((t_spr*)curr->next->content)->distance <= n) // un minore
		{
			n = ((t_spr*)curr->next->content)->distance; // nuovo minimo
			prev = curr; // il precedente te lo salvi per riconnettere la lista
		}
		curr = curr->next; // controlla il resto
	}
	if (prev) // se ce n'e' uno da ricollegare
	{
		curr = prev->next; // prendi il minimo
		prev->next = curr->next; // next del minimo diventa il next del prev
		return (curr); // ritorna il minimo
	}
	prev = g_cub.spr; // altrimenti e' il primo
	g_cub.spr = prev->next; // metti il secondo come primo
	return (prev); // ritorna il primo
}

static void	sort_sprites(void)
{
	t_list	*out;
	t_list	*lowest;

	while ((lowest = find_lowest(g_cub.spr, 0)))
	{
		lowest->next = NULL;
		ft_lstadd_front(&out, lowest);
	}
	g_cub.spr = out;
}

void sprites(double *zBuffer)
{
	t_list	*curr;
	t_spr	*spr = NULL;

	curr = g_cub.spr;

	//sort sprites from far to close
	get_sprites_distance(curr, spr);

	// sort function
	sort_sprites();

	//after sorting the sprites, do the projection and draw them
	while (curr)
	{
		spr = curr->content;

		//translate sprite position to relative to camera
		double spriteX = spr->x - g_cub.plr.posx + 0.5;
		double spriteY = spr->y - g_cub.plr.posy + 0.5;

		double invDet = 1.0 / (g_cub.plr.planex * g_cub.plr.diry - g_cub.plr.dirx * g_cub.plr.planey); //required for correct matrix multiplication

		double transformX = invDet * (g_cub.plr.diry * spriteX - g_cub.plr.dirx * spriteY);
		double transformY = invDet * (-g_cub.plr.planey * spriteX + g_cub.plr.planex * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

		int spriteScreenX = (int)((g_cub.w / 2) * (1 + transformX / transformY));

		int vDiv = 2;
		int uDiv = 2;
		t_tex	*texture = &g_cub.s;
		int vMoveScreen = (int)(texture->height * 4 / transformY);
		//calculate height of the sprite on screen
		int spriteHeight = abs((int)(g_cub.h / (transformY))) / vDiv; //using 'transformY' instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + g_cub.h / 2 + vMoveScreen;
		if (drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + g_cub.h / 2 + vMoveScreen;
		if (drawEndY >= g_cub.h)
			drawEndY = g_cub.h - 1;

		//calculate width of the sprite
		int spriteWidth = abs((int)(g_cub.h / (transformY))) / uDiv;
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0)
			drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= g_cub.w)
			drawEndX = g_cub.w - 1;

		int texX;
		//loop through every vertical stripe of the sprite on screen
		int stripe = drawStartX;
		while (stripe < drawEndX)
		{
			texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texture->width / spriteWidth) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if (transformY > 0 && stripe > 0 && stripe < g_cub.w && transformY < zBuffer[stripe])
			{
				int y = drawStartY;
				while (y < drawEndY) //for every pixel of the current stripe
				{
					int d = (y - vMoveScreen) * 256 - g_cub.h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
					int texY = ((d * texture->height) / spriteHeight) / 256;
					int color = ((unsigned int *)(texture->data.addr))[texture->width * texY + texX]; //get current color from the texture
					if ((color & 0x00FFFFFF) != 0) //paint pixel if it isn't black, black is the invisible color
						my_mlx_pixel_put(&g_cub.data, stripe, y, color);
					y++;
				}
			}
			stripe++;
		}
		curr = curr->next;
	}
}
