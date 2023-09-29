/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <dopeyrat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:50:10 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/09/29 14:50:32 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

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
