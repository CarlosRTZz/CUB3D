/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cortiz <cortiz@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:36:04 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/10/15 14:11:24 by cortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	ft_exit_2(int status)
{
	if (status == EXIT_DUP_ID)
		ft_putstr_fd("An ID is duplicated in the map file\n", 2);
	else if (status == EXIT_WALL_ERROR)
		ft_putstr_fd("The map's walls are open near the player.\n", 2);
	else if (status == EXIT_MISS_PLAYER)
		ft_putstr_fd("Player character missing from map file\n", 2);
	else if (status == EXIT_DUP_PLAYER)
		ft_putstr_fd("Two or more player characters found in map\n", 2);
	else if (status == EXIT_MLX_ERR)
		ft_putstr_fd("MLX initialisation failed\n", 2);
	else if (status == EXIT_TEXTURE_ERR)
		ft_putstr_fd("A texture provided is corrupted\n", 2);
}

int	ft_exit(t_cube *data, int status)
{
	free_cub3d(data);
	if (status != EXIT_SUCCESS)
		ft_putstr_fd("Error\n", 2);
	if (status == EXIT_FAILURE)
		ft_putstr_fd("Unknown error occured\n", 2);
	else if (status == EXIT_MALLOC)
		ft_putstr_fd("Malloc failed to allocate requested memory\n", 2);
	else if (status == EXIT_OPEN)
		ft_putstr_fd("A file provided is missing\n", 2);
	else if (status == EXIT_READ)
		ft_putstr_fd("A file provided is corrupted\n", 2);
	else if (status == EXIT_EXTENSION)
		ft_putstr_fd("A file provided is in an unsupported format\n", 2);
	else if (status == EXIT_MAP_ERROR || status == EXIT_COR_ID)
		ft_putstr_fd("Map file is corrupted\n", 2);
	else if (status == EXIT_MISS_ID)
		ft_putstr_fd("An ID is missing from the map file\n", 2);
	ft_exit_2(status);
	exit(status);
}

int	main(int ac, char **argv)
{
	t_cube	*data;
	int		fd;

	fd = check_args(ac, argv);
	data = init_data(fd);
	init_mlx(data);
	render(data);
	mlx_hook(data->mlx.window, 2, 0, keypress, data);
	mlx_hook(data->mlx.window, 3, 0, keyrelease, data);
	mlx_hook(data->mlx.window, 17, 0, window_closed, data);
	mlx_mouse_hook(data->mlx.window, mouse_click, data);
	mlx_hook(data->mlx.window, 6, 0, mouse_move, data);
	mlx_mouse_hide();
	mlx_mouse_move(data->mlx.window, (HORIZONTAL / 2), (VERTICAL / 2));
	mlx_loop_hook(data->mlx.mlx, no_input, data);
	mlx_loop(data->mlx.mlx);
	return (EXIT_SUCCESS);
}
