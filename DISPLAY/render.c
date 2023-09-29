/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <dopeyrat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:51:32 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/09/29 14:56:52 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	render(t_cube *data)
{
	t_img	*mini;
	t_img	*img;

	if (data->mlx.index)
	{
		mini = &data->mlx.mini2;
		img = &data->mlx.img2;
	}
	else
	{
		mini = &data->mlx.mini1;
		img = &data->mlx.img1;
	}
	render_minimap(data, mini);
	cast_rays(data, img, data->p);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.window, img->mlx_img, 0, 0);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.window, mini->mlx_img, 0, 0);
	data->last_frame = get_time();
	data->mlx.index = 1 - data->mlx.index;
}
