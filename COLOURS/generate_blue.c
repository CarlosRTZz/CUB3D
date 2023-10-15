/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_blue.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cortiz <cortiz@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 13:49:56 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/10/15 12:13:51 by cortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

unsigned int	gen_brg(t_cube *data, unsigned int high, unsigned int mid, unsigned int low)
{
	unsigned int	mid_step;

	mid_step = (int)(((double)mid - (double)low)
			* 7.0 / ((double)high - (double)low));
	mid_step = 8 - mid_step;
	if (data->e_counter < mid_step)
		return (create_trgb(0, mid + (data->e_counter
					* (high - low) / 8), low, high));
	if (data->e_counter < mid_step + 8)
		return (create_trgb(0, high, low, high
				- ((data->e_counter - 8) * (high - low) / 8)));
	if (data->e_counter < mid_step + 16)
		return (create_trgb(0, high, low + ((data->e_counter - 16)
					* (high - low) / 8), low));
	if (data->e_counter < mid_step + 24)
		return (create_trgb(0, high - ((data->e_counter - 24)
					* (high - low) / 8), high, low));
	if (data->e_counter < mid_step + 32)
		return (create_trgb(0, low, high, low
				+ ((data->e_counter - 32) * (high - low) / 8)));
	if (data->e_counter < mid_step + 40)
		return (create_trgb(0, low, high
				- ((data->e_counter - 40) * (high - low) / 8), high));
	return (create_trgb(0, low + ((data->e_counter - 48)
				* (high - low) / 8), low, high));
}

unsigned int	gen_bgr(t_cube *data, unsigned int high, unsigned int mid, unsigned int low)
{
	unsigned int	mid_step;

	mid_step = (int)(((double)mid - (double)low)
			* 7.0 / ((double)high - (double)low));
	mid_step = 8 - mid_step;
	if (data->e_counter < mid_step)
		return (create_trgb(0, low, mid
				+ (data->e_counter * (high - low) / 8), high));
	if (data->e_counter < mid_step + 8)
		return (create_trgb(0, low, high, high
				- ((data->e_counter - 8) * (high - low) / 8)));
	if (data->e_counter < mid_step + 16)
		return (create_trgb(0, low + ((data->e_counter - 16)
					* (high - low) / 8), high, low));
	if (data->e_counter < mid_step + 24)
		return (create_trgb(0, high, high - ((data->e_counter - 24)
					* (high - low) / 8), low));
	if (data->e_counter < mid_step + 32)
		return (create_trgb(0, high, low, low
				+ ((data->e_counter - 32) * (high - low) / 8)));
	if (data->e_counter < mid_step + 40)
		return (create_trgb(0, high - ((data->e_counter - 40)
					* (high - low) / 8), low, high));
	return (create_trgb(0, low, low + ((data->e_counter - 48)
				* (high - low) / 8), high));
}
