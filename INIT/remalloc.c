/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remalloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:37:47 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/06/07 18:37:56 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

char	*re_malloc_map_str(char *str, int n)
{
	char	*dst;
	int		i;

	dst = malloc(sizeof(char) * (n + 1));
	if (!dst)
		return (0);
	i = 0;
	while (str[i])
	{
		dst[i] = str[i];
		i++;
	}
	while (i < n)
	{
		dst[i] = ' ';
		i++;
	}
	dst[i] = 0;
	return (dst);
}

void	re_malloc_prev_map(char *str, t_cube *data, int fd, char **map)
{
	int	i;

	i = 0;
	while (data->map && data->map[i])
	{
		if (ft_strlen(data->map[i]) == (size_t)data->m_x)
			map[i] = ft_strdup(data->map[i]);
		else
			map[i] = re_malloc_map_str(data->map[i], data->m_x);
		if (!map[i])
		{
			close(fd);
			free(str);
			free_cube_map(map);
			ft_exit(data, EXIT_MALLOC);
		}
		i++;
	}
	free_cube_map(data->map);
	data->map = map;
}

char	*ft_strndup_map(char *str, int n)
{
	char	*dst;
	int		i;

	dst = malloc(sizeof(char) * (n + 1));
	if (!dst)
		return (0);
	i = 0;
	while (str[i] && i < n && str[i] != '\n')
	{
		dst[i] = str[i];
		i++;
	}
	while (i < n)
	{
		dst[i] = ' ';
		i++;
	}
	dst[i] = 0;
	return (dst);
}

int	re_malloc_map(char *str, t_cube *data, int fd)
{
	int		i;
	char	**map;

	i = 0;
	while (data->map && data->map[i])
		i++;
	if (ft_strlen(str) - 1 > (size_t)data->m_x)
		data->m_x = ft_strlen(str) - 1;
	map = ft_calloc(i + 2, sizeof(char *));
	if (!map)
	{
		close(fd);
		free(str);
		ft_exit(data, EXIT_MALLOC);
	}
	re_malloc_prev_map(str, data, fd, map);
	map[i] = ft_strndup_map(str, data->m_x);
	if (!map[i])
	{
		close(fd);
		free(str);
		ft_exit(data, EXIT_MALLOC);
	}
	data->m_y++;
	return (0);
}
