/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:43:17 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/06/07 14:43:26 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

static void	free_player(t_player *p)
{
	if (p)
	{
		free(p);
	}
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
		free_player(data->p);
		free_cube_map(data->map);
		free_textures(data);
		free(data);
	}
	return (0);
}
