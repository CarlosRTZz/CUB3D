/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_green.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <dopeyrat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 13:43:43 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/10/16 13:03:51 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

unsigned int	gen_grb(t_cube *data, unsigned int high,
					unsigned int mid, unsigned int low)
{
	unsigned int	mid_step;

	mid_step = (int)(((double)mid - (double)low)
			* 7.0 / ((double)high - (double)low));
	mid_step = 8 - mid_step;
	if (data->e_counter < mid_step)
		return (create_trgb(0, mid
				+ (data->e_counter * (high - low) / 8), high, low));
	if (data->e_counter < mid_step + 8)
		return (create_trgb(0, high, high
				- ((data->e_counter - mid_step) * (high - low) / 8), low));
	if (data->e_counter < mid_step + 16)
		return (create_trgb(0, high, low, low
				+ ((data->e_counter - 8 - mid_step) * (high - low) / 8)));
	if (data->e_counter < mid_step + 24)
		return (create_trgb(0, high - ((data->e_counter - 16
						- mid_step) * (high - low) / 8), low, high));
	if (data->e_counter < mid_step + 32)
		return (create_trgb(0, low, low + ((data->e_counter - 24
						- mid_step) * (high - low) / 8), high));
	if (data->e_counter < mid_step + 40)
		return (create_trgb(0, low, high, high - ((data->e_counter - 32
						- mid_step) * (high - low) / 8)));
	return (create_trgb(0, low + ((data->e_counter - 40 - mid_step)
				* (high - low) / 8), high, low));
}

unsigned int	gen_gbr(t_cube *data, unsigned int high,
					unsigned int mid, unsigned int low)
{
	unsigned int	mid_step;

	mid_step = (int)(((double)mid - (double)low)
			* 7.0 / ((double)high - (double)low));
	mid_step = 8 - mid_step;
	if (data->e_counter < mid_step)
		return (create_trgb(0, low, high, mid
				+ (data->e_counter * (high - low) / 8)));
	if (data->e_counter < mid_step + 8)
		return (create_trgb(0, low, high
				- ((data->e_counter - mid_step) * (high - low) / 8), high));
	if (data->e_counter < mid_step + 16)
		return (create_trgb(0, low + ((data->e_counter - 8
						- mid_step) * (high - low) / 8), low, high));
	if (data->e_counter < mid_step + 24)
		return (create_trgb(0, high, low, high
				- ((data->e_counter - 16 - mid_step) * (high - low) / 8)));
	if (data->e_counter < mid_step + 32)
		return (create_trgb(0, high, low
				+ ((data->e_counter - 24 - mid_step) * (high - low) / 8), low));
	if (data->e_counter < mid_step + 40)
		return (create_trgb(0, high - ((data->e_counter - 32 - mid_step)
					* (high - low) / 8), high, low));
	return (create_trgb(0, low, high, low + ((data->e_counter - 40 - mid_step)
				* (high - low) / 8)));
}
