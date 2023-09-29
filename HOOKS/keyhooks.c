/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <dopeyrat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:32:49 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/09/29 14:34:01 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

int	keypress(int keycode, t_cube *data)
{
	if (keycode == 53)
		ft_exit(data, EXIT_SUCCESS);
	if (keycode == UP)
		data->key_w = 1;
	if (keycode == DOWN)
		data->key_s = 1;
	if (keycode == RIGHT)
		data->key_d = 1;
	if (keycode == LEFT)
		data->key_a = 1;
	if (keycode == SHIFT)
		data->key_shift = 2;
	return (0);
}

int	keyrelease(int keycode, t_cube *data)
{
	if (keycode == UP)
		data->key_w = 0;
	if (keycode == DOWN)
		data->key_s = 0;
	if (keycode == RIGHT)
		data->key_d = 0;
	if (keycode == LEFT)
		data->key_a = 0;
	if (keycode == SHIFT)
		data->key_shift = 1;
	return (0);
}

int	window_closed(t_cube *data)
{
	ft_exit(data, EXIT_SUCCESS);
	return (0);
}
