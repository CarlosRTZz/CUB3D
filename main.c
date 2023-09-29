/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <dopeyrat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:36:04 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/09/29 15:29:46 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

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
	else if (status == EXIT_DUP_ID)
		ft_putstr_fd("An ID is duplicated in the map file\n", 2);
	else if (status == EXIT_WALL_ERROR)
		ft_putstr_fd("The walls in the map file are not closed on the player\n", 2);
	else if (status == EXIT_MISS_PLAYER)
		ft_putstr_fd("Player character missing from map file\n", 2);
	else if (status == EXIT_DUP_PLAYER)
		ft_putstr_fd("Two or more player characters found in map\n", 2);
	else if (status == EXIT_MLX_ERR)
		ft_putstr_fd("MLX initialisation failed\n", 2);
	else if (status == EXIT_TEXTURE_ERR)
		ft_putstr_fd("A texture provided is corrupted\n", 2);
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
	mlx_loop_hook(data->mlx.mlx, no_input, data);
	mlx_loop(data->mlx.mlx);
	return (EXIT_SUCCESS);
}
