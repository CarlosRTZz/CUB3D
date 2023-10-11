/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_click.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cortiz <cortiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:10:28 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/10/11 13:47:21 by cortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

typedef struct s_mouse_ray
{
	double	planex;
	double	planey;

	double	camerax;

	double	raydirx;
	double	raydiry;

	int		mapx;
	int		mapy;

	double	sidedistx;
	double	sidedisty;

	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;

	int		stepx;
	int		stepy;

	int		side;
	int		hit;
}			t_mouse;

int	mouse_click(int keycode, int x, int y, t_cube *data)
{
	t_mouse	ray;
	t_mouse	*p;
	int		i;

	(void)keycode;
	(void)x;
	(void)y;
	i = (HORIZONTAL / 2) - 1;
	p = &ray;
	p->planex = cos(data->p->a + (PI / 2)) * 0.66;
	p->planey = sin(data->p->a + (PI / 2)) * 0.66;
	p->camerax = ((double)(2 * i) / (double)HORIZONTAL) - 1.0;
	p->raydirx = data->p->x_off + (p->planex * p->camerax);
	p->raydiry = data->p->y_off + (p->planey * p->camerax);
	p->mapx = (int)data->p->x;
	p->mapy = (int)data->p->y;
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
		p->sidedistx = (data->p->x - (double)p->mapx) * p->deltadistx;
	}
	else
	{
		p->stepx = 1;
		p->sidedistx = ((double)p->mapx + 1.0 - data->p->x) * p->deltadistx;
	}
	if (p->raydiry < 0)
	{
		p->stepy = -1;
		p->sidedisty = (data->p->y - (double)p->mapy) * p->deltadisty;
	}
	else
	{
		p->stepy = 1;
		p->sidedisty = ((double)p->mapy + 1.0 - data->p->y) * p->deltadisty;
	}
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
		if (data->map[p->mapy][p->mapx] == '1')
			return (0);
		if (data->map[p->mapy][p->mapx] == '2')
		{
			data->map[p->mapy][p->mapx] = '3';
			return (0);
		}
		if (data->map[p->mapy][p->mapx] == '3')
		{
			data->map[p->mapy][p->mapx] = '2';
			return (0);
		}
	}
	return (0);
}
