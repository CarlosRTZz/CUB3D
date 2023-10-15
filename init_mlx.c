/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cortiz <cortiz@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:12:15 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/10/15 13:59:17 by cortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	set_textures_addr(t_cube *data)
{
	data->mlx.no.addr = mlx_get_data_addr(data->mlx.no.mlx_img,
			&data->mlx.no.bpp, &data->mlx.no.line_len, &data->mlx.no.endian);
	data->mlx.so.addr = mlx_get_data_addr(data->mlx.so.mlx_img,
			&data->mlx.so.bpp, &data->mlx.so.line_len, &data->mlx.so.endian);
	data->mlx.ea.addr = mlx_get_data_addr(data->mlx.ea.mlx_img,
			&data->mlx.ea.bpp, &data->mlx.ea.line_len, &data->mlx.ea.endian);
	data->mlx.we.addr = mlx_get_data_addr(data->mlx.we.mlx_img,
			&data->mlx.we.bpp, &data->mlx.we.line_len, &data->mlx.we.endian);
}

void	init_textures(t_cube *data)
{
	data->mlx.no.mlx_img = mlx_xpm_file_to_image(data->mlx.mlx, data->n_t,
			&data->mlx.no.width, &data->mlx.no.height);
	data->mlx.so.mlx_img = mlx_xpm_file_to_image(data->mlx.mlx, data->s_t,
			&data->mlx.so.width, &data->mlx.so.height);
	data->mlx.ea.mlx_img = mlx_xpm_file_to_image(data->mlx.mlx, data->e_t,
			&data->mlx.ea.width, &data->mlx.ea.height);
	data->mlx.we.mlx_img = mlx_xpm_file_to_image(data->mlx.mlx, data->w_t,
			&data->mlx.we.width, &data->mlx.we.height);
	if (!data->mlx.no.mlx_img || !data->mlx.so.mlx_img
		|| !data->mlx.ea.mlx_img || !data->mlx.we.mlx_img)
		ft_exit(data, EXIT_TEXTURE_ERR);
	free(data->n_t);
	data->n_t = 0;
	free(data->s_t);
	data->s_t = 0;
	free(data->w_t);
	data->w_t = 0;
	free(data->e_t);
	data->e_t = 0;
	set_textures_addr(data);
}

void	set_img_addr(t_cube *data)
{
	data->mlx.img1.addr = mlx_get_data_addr(data->mlx.img1.mlx_img, &data->mlx
			.img1.bpp, &data->mlx.img1.line_len, &data->mlx.img1.endian);
	data->mlx.img2.addr = mlx_get_data_addr(data->mlx.img2.mlx_img, &data->mlx
			.img2.bpp, &data->mlx.img2.line_len, &data->mlx.img2.endian);
}

void	init_mlx(t_cube *data)
{
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
		ft_exit(data, EXIT_MLX_ERR);
	data->mlx.window = mlx_new_window(data->mlx.mlx, 1280, 720, "Cub3D");
	if (!data->mlx.window)
		ft_exit(data, EXIT_MLX_ERR);
	data->mlx.mini1.mlx_img = mlx_new_image(data->mlx.mlx, 400, 400);
	if (!data->mlx.mini1.mlx_img)
		ft_exit(data, EXIT_MLX_ERR);
	data->mlx.mini2.mlx_img = mlx_new_image(data->mlx.mlx, 400, 400);
	if (!data->mlx.mini2.mlx_img)
		ft_exit(data, EXIT_MLX_ERR);
	data->mlx.mini1.addr = mlx_get_data_addr(data->mlx.mini1.mlx_img, &data->mlx
			.mini1.bpp, &data->mlx.mini1.line_len, &data->mlx.mini1.endian);
	data->mlx.mini2.addr = mlx_get_data_addr(data->mlx.mini2.mlx_img, &data->mlx
			.mini2.bpp, &data->mlx.mini2.line_len, &data->mlx.mini2.endian);
	data->mlx.img1.mlx_img = mlx_new_image(data->mlx.mlx, 1280, 720);
	if (!data->mlx.img1.mlx_img)
		ft_exit(data, EXIT_MLX_ERR);
	data->mlx.img2.mlx_img = mlx_new_image(data->mlx.mlx, 1280, 720);
	if (!data->mlx.img2.mlx_img)
		ft_exit(data, EXIT_MLX_ERR);
	set_img_addr(data);
	data->mlx.index = 1;
	init_textures(data);
}
