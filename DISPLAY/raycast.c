/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <dopeyrat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:49:31 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/10/06 15:55:50 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

typedef struct s_trgb
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	t;
}				t_rgb;

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

void	init_dda(t_player *p, int i)
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
		p->stepx = 1;
		p->sidedistx = ((double)p->mapx + 1.0 - p->x) * p->deltadistx;
		if (p->raydirx < 0)
		{
			p->stepx = -1;
			p->sidedistx = (p->x - (double)p->mapx) * p->deltadistx;
		}
		p->stepy = 1;
		p->sidedisty = ((double)p->mapy + 1.0 - p->y) * p->deltadisty;
		if (p->raydiry < 0)
		{
			p->stepy = -1;
			p->sidedisty = (p->y - (double)p->mapy) * p->deltadisty;
		}
}

void	perform_dda(t_cube *data, t_player *p)
{
	p->hit = 0;
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
}

void	get_wall_info(t_cube *data, t_player *p)
{
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
}

void	put_texture(t_img *img, t_cube *data, int i, int j)
{
	unsigned int	colour;
	t_rgb			trgb;

	data->p->texy = (int)data->p->texpos & (data->p->texture->height - 1);
	data->p->texpos += data->p->step;
	colour = *(unsigned int *)(data->p->texture->addr + (data->p->texy * data->p->texture->line_len) + ((data->p->texx) * (data->p->texture->bpp / 8)));
	trgb.b = colour % 0x100;
	trgb.g = (colour % 0x10000) / 0x100;
	trgb.r = (colour % 0x1000000) / 0x10000;
	trgb.t = colour / 0x1000000;
	//printf("COLOUR = %#X, T = %#X, R = %#X, G = %#X, B = %#X\n", colour, trgb.t, trgb.r, trgb.g, trgb.b);
	if (trgb.r >= trgb.g && trgb.r >= trgb.b && trgb.g >= trgb.b)
		colour = (trgb.t * 0x1000000) + generate_rgb(data, trgb.r, trgb.g, trgb.b);
	else if (trgb.r >= trgb.g && trgb.r >= trgb.b)
		colour = (trgb.t * 0x1000000) + generate_rbg(data, trgb.r, trgb.b, trgb.g);
	else if (trgb.g >= trgb.b && trgb.r >= trgb.b)
		colour = (trgb.t * 0x1000000) + generate_grb(data, trgb.g, trgb.r, trgb.b);
	else if (trgb.g >= trgb.b)
		colour = (trgb.t * 0x1000000) + generate_gbr(data, trgb.g, trgb.b, trgb.r);
	else if (trgb.r >= trgb.g)
		colour = (trgb.t * 0x1000000) + generate_brg(data, trgb.b, trgb.r, trgb.g);
	else
		colour = (trgb.t * 0x1000000) + generate_bgr(data, trgb.b, trgb.g, trgb.r);
	my_mlx_pixel_put(img, i, j, colour);
}

unsigned int	generate_cf(unsigned int colour, t_cube *data)
{
	t_rgb	trgb;

	trgb.b = colour % 0x100;
	trgb.g = (colour % 0x10000) / 0x100;
	trgb.r = (colour % 0x1000000) / 0x10000;
	trgb.t = colour / 0x1000000;
	if (trgb.r >= trgb.g && trgb.r >= trgb.b && trgb.g >= trgb.b)
		return (generate_rgb(data, trgb.r, trgb.g, trgb.b));
	else if (trgb.r >= trgb.g && trgb.r >= trgb.b)
		return (generate_rbg(data, trgb.r, trgb.b, trgb.g));
	else if (trgb.g >= trgb.b && trgb.r >= trgb.b)
		return (generate_grb(data, trgb.g, trgb.r, trgb.b));
	else if (trgb.g >= trgb.b)
		return (generate_gbr(data, trgb.g, trgb.b, trgb.r));
	else if (trgb.r >= trgb.g)
		return (generate_brg(data, trgb.b, trgb.r, trgb.g));
	else
		return (generate_bgr(data, trgb.b, trgb.g, trgb.r));
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
		init_dda(p, i);
		perform_dda(data, p);
		get_wall_info(data, p);
		j = 0;
		while (j < VERTICAL)
		{
			if (j < p->drawstart)
				my_mlx_pixel_put(img, i, j, generate_cf(data->c, data));
			else if (j >= p->drawend)
				my_mlx_pixel_put(img, i, j, generate_cf(data->f, data));
			else
				put_texture(img, data, i, j);
			j++;
		}
		i++;
	}
}
