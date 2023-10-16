/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <dopeyrat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:50:10 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/10/16 12:54:40 by dopeyrat         ###   ########.fr       */
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

void	put_texture(t_img *img, t_cube *data, int i, int j)
{
	unsigned int	colour;
	t_rgb			trgb;

	data->p->texy = (int)data->p->texpos & (data->p->texture->height - 1);
	data->p->texpos += data->p->step;
	colour = *(unsigned int *)(data->p->texture->addr + (data->p->texy
				* data->p->texture->line_len) + ((data->p->texx)
				* (data->p->texture->bpp / 8)));
	trgb.b = colour % 0x100;
	trgb.g = (colour % 0x10000) / 0x100;
	trgb.r = (colour % 0x1000000) / 0x10000;
	trgb.t = colour / 0x1000000;
	if (trgb.r >= trgb.g && trgb.r >= trgb.b && trgb.g >= trgb.b)
		colour = (trgb.t * 0x1000000) + gen_rgb(data, trgb.r, trgb.g, trgb.b);
	else if (trgb.r >= trgb.g && trgb.r >= trgb.b)
		colour = (trgb.t * 0x1000000) + gen_rbg(data, trgb.r, trgb.b, trgb.g);
	else if (trgb.g >= trgb.b && trgb.r >= trgb.b)
		colour = (trgb.t * 0x1000000) + gen_grb(data, trgb.g, trgb.r, trgb.b);
	else if (trgb.g >= trgb.b)
		colour = (trgb.t * 0x1000000) + gen_gbr(data, trgb.g, trgb.b, trgb.r);
	else if (trgb.r >= trgb.g)
		colour = (trgb.t * 0x1000000) + gen_brg(data, trgb.b, trgb.r, trgb.g);
	else
		colour = (trgb.t * 0x1000000) + gen_bgr(data, trgb.b, trgb.g, trgb.r);
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
		return (gen_rgb(data, trgb.r, trgb.g, trgb.b));
	else if (trgb.r >= trgb.g && trgb.r >= trgb.b)
		return (gen_rbg(data, trgb.r, trgb.b, trgb.g));
	else if (trgb.g >= trgb.b && trgb.r >= trgb.b)
		return (gen_grb(data, trgb.g, trgb.r, trgb.b));
	else if (trgb.g >= trgb.b)
		return (gen_gbr(data, trgb.g, trgb.b, trgb.r));
	else if (trgb.r >= trgb.g)
		return (gen_brg(data, trgb.b, trgb.r, trgb.g));
	else
		return (gen_bgr(data, trgb.b, trgb.g, trgb.r));
}
