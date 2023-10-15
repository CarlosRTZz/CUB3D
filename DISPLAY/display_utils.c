/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cortiz <cortiz@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:50:10 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/10/15 12:31:49 by cortiz           ###   ########.fr       */
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

void	draw_line(t_img *mini, int x1, int y1, int x2, int y2)
{
	t_point	dpoint;
	t_point	spoint;
	t_point	errpoint;;
	int		i;
	int		j;

	dpoint.x = abs(x2 - x1);
	dpoint.y = abs(y2 - y1);
	spoint.x = -1;
	if (x1 < x2)
		spoint.x = 1;
	spoint.y = -1;
	if (y1 < y2)
		spoint.y = 1;
	errpoint.x = dpoint.x - dpoint.y;
	while (x1 != x2 || y1 != y2)
	{
		i = 0;
		while (i < 3)
		{
			j = 0;
			while (j < 3)
			{
				if (x1 + i >= 0 && x1 + i < 400 && y1 + j >= 0 && y1 + j < 400)
					my_mlx_pixel_put(mini, x1 + i, y1 + j, 0xFF0000);
				j++;
			}
			i++;
		}
		errpoint.y = 2 * errpoint.x;
		if (errpoint.y > -dpoint.y)
		{
			errpoint.x -= dpoint.y;
			x1 += spoint.x;
		}
		if (errpoint.y < dpoint.x)
		{
			errpoint.x += dpoint.x;
			y1 += spoint.y;
		}
	}
}
