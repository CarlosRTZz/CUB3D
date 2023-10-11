/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cortiz <cortiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:07:15 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/10/11 14:01:59 by cortiz           ###   ########.fr       */
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
