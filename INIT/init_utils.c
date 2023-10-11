/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cortiz <cortiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:58:19 by cortiz            #+#    #+#             */
/*   Updated: 2023/10/11 14:09:12 by cortiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	check_map(t_cube *data)
{
	int	i;
	// FONCTION A SUPPRIMER !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	i = 0;
	if (!all_id_found(data))
		ft_exit(data, EXIT_MISS_ID);
	check_walls(data);
	set_player(data);
	printf("Player -> x %f, y %f, a %f\n", data->p->x, data->p->y, data->p->a);
	printf("Texture -> NORTH %s, SOUTH %s", data->n_t, data->s_t);
	printf("EAST %s, WEST %s\n", data->e_t, data->w_t);
	printf("Colours -> FLOOR %u, CEILING %u\n", data->f, data->c);
	printf("MAP -> x %d, y %d\n", data->m_x, data->m_y);
	while (data->map[i])
	{
		printf("%s -> %d\n", data->map[i], (int)ft_strlen(data->map[i]));
		i++;
	}
}

char	**copy_map(t_cube *data)
{
	char	**dst;
	int		i;

	dst = ft_calloc(data->m_y + 1, sizeof(char *));
	if (!dst)
		ft_exit(data, EXIT_MALLOC);
	i = 0;
	while (i < data->m_y)
	{
		dst[i] = ft_strdup(data->map[i]);
		if (!dst[i])
		{
			free_cube_map(dst);
			ft_exit(data, EXIT_MALLOC);
		}
		i++;
	}
	return (dst);
}
