/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <dopeyrat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:43:17 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/09/29 15:23:27 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	free_mlx(t_cube *data)
{
	if (!data->mlx.mlx)
		return ;
	if (data->mlx.mini1.mlx_img)
		mlx_destroy_image(data->mlx.mlx, data->mlx.mini1.mlx_img);
	if (data->mlx.mini2.mlx_img)
		mlx_destroy_image(data->mlx.mlx, data->mlx.mini2.mlx_img);
	if (data->mlx.img1.mlx_img)
		mlx_destroy_image(data->mlx.mlx, data->mlx.img1.mlx_img);
	if (data->mlx.img2.mlx_img)
		mlx_destroy_image(data->mlx.mlx, data->mlx.img2.mlx_img);
	if (data->mlx.no.ptr)
		mlx_destroy_image(data->mlx.mlx, data->mlx.no.ptr);
	if (data->mlx.so.ptr)
		mlx_destroy_image(data->mlx.mlx, data->mlx.so.ptr);
	if (data->mlx.ea.ptr)
		mlx_destroy_image(data->mlx.mlx, data->mlx.ea.ptr);
	if (data->mlx.we.ptr)
		mlx_destroy_image(data->mlx.mlx, data->mlx.we.ptr);
	if (data->mlx.window)
		mlx_destroy_window(data->mlx.mlx, data->mlx.window);
}

void	free_cube_map(char **map)
{
	int	i;

	if (map)
	{
		i = 0;
		while (map[i])
		{
			free(map[i]);
			i++;
		}
		free(map);
	}
}

static void	free_textures(t_cube *data)
{
	if (data->n_t)
		free(data->n_t);
	if (data->s_t)
		free(data->s_t);
	if (data->w_t)
		free(data->w_t);
	if (data->e_t)
		free(data->e_t);
}

t_cube	*free_cub3d(t_cube *data)
{
	if (data)
	{
		if (data->p)
			free(data->p);
		free_cube_map(data->map);
		free_textures(data);
		free_mlx(data);
		free(data);
	}
	return (0);
}
