/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <dopeyrat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:32:45 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/09/28 11:39:23 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

int	is_empty_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if ((str[i] == '\n' && !str[i + 1]) || !str[i])
		return (1);
	return (0);
}

int	handle_line(char *str, t_cube *data, int fd, int *m)
{
	int	i;

	if (*m == 0)
	{
		if (is_empty_str(str))
			return (0);
		i = 0;
		while (str[i] == ' ')
			i++;
		if (is_map_id(&str[i]))
			return (add_map_id(str, data, fd, i));
		if (all_id_found(data))
		{
			*m = 1;
			return (re_malloc_map(str, data, fd));
		}
		close(fd);
		free(str);
		ft_exit(data, EXIT_MISS_ID);
	}
	else
		return (re_malloc_map(str, data, fd));
	return (0);
}

void	parse_map(t_cube *data, int fd)
{
	char	*str;
	int		m;

	m = 0;
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		handle_line(str, data, fd, &m);
		free(str);
	}
	close(fd);
	if (errno == ENOMEM)
		ft_exit(data, EXIT_MALLOC);
}

t_cube	*init_data(int fd)
{
	t_cube	*data;

	data = ft_calloc(1, sizeof(t_cube));
	if (!data)
	{
		close(fd);
		ft_exit(0, EXIT_MALLOC);
	}
	data->p = ft_calloc(1, sizeof(t_player));
	if (!data->p)
	{
		close(fd);
		ft_exit(data, EXIT_MALLOC);
	}
	parse_map(data, fd);
	check_map(data);
	data->key_a = 0;
	data->key_d = 0;
	data->key_w = 0;
	data->key_s = 0;
	data->key_shift = 1;
	return (data);
}
