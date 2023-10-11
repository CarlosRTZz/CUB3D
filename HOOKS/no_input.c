/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cortiz <cortiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:35:39 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/10/11 13:48:48 by cortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

int	check_hor_col(t_cube *data, double offset)
{
	double	tmp;

	tmp = offset + data->p->x;
	if ((int)tmp >= data->m_x || (int)tmp < 0)
		return (0);
	if (data->map[(int)data->p->y][(int)tmp] == '1' ||
			data->map[(int)data->p->y][(int)tmp] == '2')
		return (0);
	return (1);
}

int	check_ver_col(t_cube *data, double offset)
{
	double	tmp;

	tmp = offset + data->p->y;
	if ((int)tmp >= data->m_y || (int)tmp < 0)
		return (0);
	if (data->map[(int)tmp][(int)data->p->x] == '1' ||
			data->map[(int)tmp][(int)data->p->x] == '2')
		return (0);
	return (1);
}

void	movement_key(t_cube *data)
{
	double	offset;

	if (data->key_w)
	{
		offset = data->p->x_off * 0.025 * data->key_shift;
		if (check_hor_col(data, offset))
			data->p->x += offset;
		offset = data->p->y_off * 0.025 * data->key_shift;
		if (check_ver_col(data, offset))
			data->p->y += offset;
	}
	if (data->key_s)
	{
		offset = -data->p->x_off * 0.025 * data->key_shift;
		if (check_hor_col(data, offset))
			data->p->x += offset;
		offset = -data->p->y_off * 0.025 * data->key_shift;
		if (check_ver_col(data, offset))
			data->p->y += offset;
	}
}

int	no_input(t_cube *data)
{
	if (time_diff(data->last_frame, get_time()) < FRAME_INTERVAL)
		return (0);
	if (data->key_w || data->key_s)
		movement_key(data);
	if (data->key_a)
	{
		data->p->a -= PI / 36;
		if (data->p->a < 0)
			data->p->a += 2 * PI;
		data->p->x_off = cos(data->p->a);
		data->p->y_off = sin(data->p->a);
	}
	if (data->key_d)
	{
		data->p->a += PI / 36;
		if (data->p->a > 2 * PI)
			data->p->a -= 2 * PI;
		data->p->x_off = cos(data->p->a);
		data->p->y_off = sin(data->p->a);
	}
	render(data);
	return (0);
}
