/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <dopeyrat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:07:15 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/09/29 13:01:39 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

int	all_id_found(t_cube *data)
{
	if (data->n_t == 0 || data->s_t == 0 || data->w_t == 0
		|| data->e_t == 0 || data->f_f == 0 || data->c_f == 0)
		return (0);
	return (1);
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

void	recu_check_walls(t_cube *data, char **map, int i, int j)
{
	if (map[i][j] == '1')
		return ;
	if (map[i][j] == ' ')
	{
		free_cube_map(map);
		ft_exit(data, EXIT_WALL_ERROR);
	}
	if (i == 0 || j == 0 || i == data->m_y - 1 || j == data->m_x - 1)
	{
		free_cube_map(map);
		ft_exit(data, EXIT_WALL_ERROR);
	}
	map[i][j] = '1';
	recu_check_walls(data, map, i + 1, j + 1);
	recu_check_walls(data, map, i + 1, j);
	recu_check_walls(data, map, i + 1, j - 1);
	recu_check_walls(data, map, i, j + 1);
	recu_check_walls(data, map, i, j - 1);
	recu_check_walls(data, map, i - 1, j + 1);
	recu_check_walls(data, map, i - 1, j);
	recu_check_walls(data, map, i - 1, j - 1);
}

void	check_walls(t_cube *data)
{
	char	**copy;
	int		i;
	int		j;

	copy = copy_map(data);
	i = 0;
	while (i < data->m_y)
	{
		j = 0;
		while (j < data->m_x)
		{
			if (copy[i][j] == 'N' || copy[i][j] == 'S' || copy[i][j] == 'E'
				|| copy[i][j] == 'W')
			{
				recu_check_walls(data, copy, i, j);
				free_cube_map(copy);
				return ;
			}
			j++;
		}
		i++;
	}
	free_cube_map(copy);
	ft_exit(data, EXIT_MISS_PLAYER);
}

void	set_player_start_pos(t_player *p, int i, int j, char dir)
{
	p->x = (double)j + 0.5;
	p->y = (double)i + 0.5;
	if (dir == 'N')
		p->a = (double)(3 * PI) / 2;
	else if (dir == 'S')
		p->a = (double)(PI) / 2;
	else if (dir == 'W')
		p->a = (double)(PI);
	else
		p->a = (double)(0);
	p->x_off = cos(p->a);
	p->y_off = sin(p->a);
}

void	set_player(t_cube *data)
{
	int	i;
	int	j;
	int	p;

	p = 0;
	i = 0;
	while (i < data->m_y)
	{
		j = 0;
		while (j < data->m_x)
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'E' || data->map[i][j] == 'W')
			{
				if (p)
					ft_exit(data, EXIT_DUP_PLAYER);
				p = 1;
				set_player_start_pos(data->p, i, j, data->map[i][j]);
				data->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}

void	check_map(t_cube *data)
{
	if (!all_id_found(data))
		ft_exit(data, EXIT_MISS_ID);
	check_walls(data);
	set_player(data);
	printf("Player -> x %f, y %f, a %f\n", data->p->x, data->p->y, data->p->a);
	printf("Texture -> NORTH %s, SOUTH %s, EAST %s, WEST %s\n", data->n_t, data->s_t, data->e_t, data->w_t);
	printf("Colours -> FLOOR %u, CEILING %u\n", data->f, data->c);
	int i = 0;
	printf("MAP -> x %d, y %d\n", data->m_x, data->m_y);
	while (data->map[i])
	{
		printf("%s -> %d\n", data->map[i], (int)ft_strlen(data->map[i]));
		i++;
	}
}
