/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cortiz <cortiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:47:12 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/10/11 12:45:16 by cortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

int	get_minimap_colour(t_cube *data, double a, double b)
{
	int		a_a;
	int		a_b;
	double	f_a;
	double	f_b;

	a_a = (int)a;
	a_b = (int)b;
	if (a_a < 0 || a_b < 0 || a_a >= data->m_x || a_b >= data->m_y)
		return (0xFF000000);
	f_a = fmod(a, 1);
	f_b = fmod(b, 1);
	if (data->map[a_b][a_a] == '1' || data->map[a_b][a_a] == '0' ||
			data->map[a_b][a_a] == '2' || data->map[a_b][a_a] == '3')
	{
		if ((f_a < 0.0125 || f_a > 0.9875) || (f_b < 0.0125 || f_b > 0.9875))
			return (0x0);
		if (data->map[a_b][a_a] == '0')
			return (0xFFFFFF);
		if (data->map[a_b][a_a] == '2' || data->map[a_b][a_a] == '3')
			return (0x7F3F3F);
		return (0xFF);
	}
	return (0xFF000000);
}

void	render_minimap(t_cube *data, t_img *mini)
{
	int		i;
	int		j;
	double	a;
	double	b;
	int		colour;

	i = 0;
	while (i < 400)
	{
		j = 0;
		while (j < 400)
		{
			if (i >= 195 && i < 205 && j >= 195 && j < 205)
				my_mlx_pixel_put(mini, i, j, 0xFF0000);
			else
			{
				a = (double)(data->p->x - ((double)(199 - i) / 40.0));
				b = (double)(data->p->y - ((double)(199 - j) / 40.0));
				colour = get_minimap_colour(data, a, b);
				my_mlx_pixel_put(mini, i, j, colour);
			}
			j++;
		}
		i++;
	}
}
