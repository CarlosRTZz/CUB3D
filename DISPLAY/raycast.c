/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <dopeyrat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:49:31 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/10/02 12:32:10 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	cast_rays(t_cube *data, t_img *img, t_player *p)
{
	int	i;

	i = 0;
	p->planeX = cos(p->a + (PI / 2)) * 0.66;
	p->planeY = sin(p->a + (PI / 2)) * 0.66;
	while (i < HORIZONTAL)
	{
		p->cameraX = ((double)(2 * i) / (double)HORIZONTAL) - 1.0;
		p->rayDirX = p->x_off + (p->planeX * p->cameraX);
		p->rayDirY = p->y_off + (p->planeY * p->cameraX);
		p->mapX = (int)p->x;
		p->mapY = (int)p->y;
		p->deltaDistX = 10e30;
		if (p->rayDirX != 0)
			p->deltaDistX = fabs((1 / p->rayDirX));
		p->deltaDistY = 10e30;
		if (p->rayDirY != 0)
			p->deltaDistY = fabs((1 / p->rayDirY));
		p->hit = 0;
		if (p->rayDirX < 0)
		{
			p->stepX = -1;
			p->sideDistX = (p->x - (double)p->mapX) * p->deltaDistX;
		}
		else
		{
			p->stepX = 1;
			p->sideDistX = ((double)p->mapX + 1.0 - p->x) * p->deltaDistX;
		}
		if (p->rayDirY < 0)
		{
			p->stepY = -1;
			p->sideDistY = (p->y - (double)p->mapY) * p->deltaDistY;
		}
		else
		{
			p->stepY = 1;
			p->sideDistY = ((double)p->mapY + 1.0 - p->y) * p->deltaDistY;
		}
		//DDA
		while (p->hit == 0)
		{
			if (p->sideDistX < p->sideDistY)
			{
				p->sideDistX += p->deltaDistX;
				p->mapX += p->stepX;
				p->side = 0;
			}
			else
			{
				p->sideDistY += p->deltaDistY;
				p->mapY += p->stepY;
				p->side = 1;
			}
			if (data->map[p->mapY][p->mapX] == '1' || data->map[p->mapY][p->mapX] == '2')
				p->hit = 1;
		}
		if (p->side == 0)
			p->perpWallDist = (p->sideDistX - p->deltaDistX);
		else
			p->perpWallDist = (p->sideDistY - p->deltaDistY);
		int lineHeight = (int)((double)VERTICAL / p->perpWallDist);
		int drawStart = -lineHeight / 2 + VERTICAL / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + VERTICAL / 2;
		if(drawEnd >= VERTICAL)
			drawEnd = VERTICAL - 1;
		int j = 0;
		while (j < VERTICAL)
		{
			if (j >= drawStart && j <= drawEnd)
				my_mlx_pixel_put(img, i, j, (p->side ? 0xFF0000 : 0x00FF00));
			else
				my_mlx_pixel_put(img, i, j, 0x0);
			j++;
		}
		i++;
	}
}
