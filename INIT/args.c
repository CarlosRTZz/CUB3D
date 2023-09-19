/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <dopeyrat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:44:32 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/09/19 11:07:36 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

int	check_map_extension(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	if (len < 4)
		return (EXIT_FAILURE);
	if (str[len - 4] != '.' || str[len - 3] != 'c'
		|| str[len - 2] != 'u' || str[len - 1] != 'b')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_args(int ac, char **argv)
{
	int	fd;

	if (ac != 2)
	{
		if (ac == 1)
			write(2, "Please provide a map\n", 21);
		else
			write(2, "Please provide only one map\n", 28);
		exit(EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1 || check_map_extension(argv[1]) == EXIT_FAILURE)
	{
		if (fd != -1)
			close(fd);
		write(2, "Map provided is invalid\n", 24);
		exit(EXIT_FAILURE);
	}
	return (fd);
}
