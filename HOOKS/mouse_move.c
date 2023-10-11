/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cortiz <cortiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:46:24 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/10/11 13:48:13 by cortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

int	mouse_move(int x, int y, t_cube *data)
{
	(void)y;
	if (x < (HORIZONTAL / 2))
	{
		data->p->a -= PI * ((double)(HORIZONTAL / 2.0) - (double)x)
			/ (((double)HORIZONTAL / 2.0)) / 2;
		if (data->p->a > 2 * PI)
			data->p->a -= 2 * PI;
		data->p->x_off = cos(data->p->a);
		data->p->y_off = sin(data->p->a);
	}
	else
	{
		data->p->a += PI * (((double)x - ((double)(HORIZONTAL / 2.0)))
				/ (((double)HORIZONTAL / 2.0))) / 2;
		if (data->p->a < 0)
			data->p->a += 2 * PI;
		data->p->x_off = cos(data->p->a);
		data->p->y_off = sin(data->p->a);
	}
	mlx_mouse_move(data->mlx.window, (HORIZONTAL / 2), (VERTICAL / 2));
	return (0);
}
