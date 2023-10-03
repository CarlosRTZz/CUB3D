/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <dopeyrat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:49:31 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/10/02 15:17:54 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

t_texture	*get_wall_texture(t_cube *data, t_player *p)
{
	if (p->side == 1 && p->stepy < 0)
		return (&data->mlx.no);
	else if (p->side == 1)
		return (&data->mlx.so);
	else if (p->side == 0 && p->stepx < 0)
		return (&data->mlx.we);
	else if (p->side == 0)
		return (&data->mlx.ea);
	return (0);
}

void	cast_rays(t_cube *data, t_img *img, t_player *p)
{
	int	i;
	int	j;

	i = 0;
	p->planex = cos(p->a + (PI / 2)) * 0.66;
	p->planey = sin(p->a + (PI / 2)) * 0.66;
	while (i < HORIZONTAL)
	{
		p->camerax = ((double)(2 * i) / (double)HORIZONTAL) - 1.0;
		p->raydirx = p->x_off + (p->planex * p->camerax);
		p->raydiry = p->y_off + (p->planey * p->camerax);
		p->mapx = (int)p->x;
		p->mapy = (int)p->y;
		p->deltadistx = 10e30;
		if (p->raydirx != 0)
			p->deltadistx = fabs((1 / p->raydirx));
		p->deltadisty = 10e30;
		if (p->raydiry != 0)
			p->deltadisty = fabs((1 / p->raydiry));
		p->hit = 0;
		if (p->raydirx < 0)
		{
			p->stepx = -1;
			p->sidedistx = (p->x - (double)p->mapx) * p->deltadistx;
		}
		else
		{
			p->stepx = 1;
			p->sidedistx = ((double)p->mapx + 1.0 - p->x) * p->deltadistx;
		}
		if (p->raydiry < 0)
		{
			p->stepy = -1;
			p->sidedisty = (p->y - (double)p->mapy) * p->deltadisty;
		}
		else
		{
			p->stepy = 1;
			p->sidedisty = ((double)p->mapy + 1.0 - p->y) * p->deltadisty;
		}
		//ddA
		while (p->hit == 0)
		{
			if (p->sidedistx < p->sidedisty)
			{
				p->sidedistx += p->deltadistx;
				p->mapx += p->stepx;
				p->side = 0;
			}
			else
			{
				p->sidedisty += p->deltadisty;
				p->mapy += p->stepy;
				p->side = 1;
			}
			if (data->map[p->mapy][p->mapx] == '1' || data->map[p->mapy][p->mapx] == '2')
				p->hit = 1;
		}
		if (p->side == 0)
			p->perpwalldist = (p->sidedistx - p->deltadistx);
		else
			p->perpwalldist = (p->sidedisty - p->deltadisty);
		p->lineheight = (int)((double)VERTICAL / p->perpwalldist);
		p->drawstart = -p->lineheight / 2 + VERTICAL / 2;
		if(p->drawstart < 0)
			p->drawstart = 0;
		p->drawend = p->lineheight / 2 + VERTICAL / 2;
		if(p->drawend >= VERTICAL)
			p->drawend = VERTICAL - 1;
		if (p->side == 0)
			p->wallx = p->y + p->perpwalldist * p->raydiry;
		else
			p->wallx = p->x + p->perpwalldist * p->raydirx;
		p->wallx -= (int)p->wallx;
		p->texture = get_wall_texture(data, p);
		p->texx = (int)(p->wallx * (double)p->texture->width);
		if (p->side == 0 && p->raydirx < 0)
			p->texx = p->texture->width - p->texx - 1;
		if (p->side == 1 && p->raydiry > 0)
			p->texx = p->texture->width - p->texx - 1;
		p->step = 1.0 * p->texture->height / p->lineheight;
		p->texpos = (p->drawstart - VERTICAL / 2 + p->lineheight / 2) * p->step;
		j = 0;
		while (j < VERTICAL)
		{
			if (j < p->drawstart)
				my_mlx_pixel_put(img, i, j, data->c);
			else if (j >= p->drawend)
				my_mlx_pixel_put(img, i, j, data->f);
			else
			{
				p->texy = (int)p->texpos & (p->texture->height - 1);
				p->texpos += p->step;
				my_mlx_pixel_put(img, i, j, *(unsigned int *)(p->texture->addr + (p->texy * p->texture->line_len) + ((p->texx) * (p->texture->bpp / 8))));
			}
			j++;
		}
		i++;
	}
}
