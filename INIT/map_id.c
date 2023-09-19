/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_id.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:57:10 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/06/07 17:57:19 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

int	is_map_id(char *str)
{
	if (str[0] == 'N' && str[1] == 'O' && str[2] == ' ')
		return ((int) 'N');
	if (str[0] == 'S' && str[1] == 'O' && str[2] == ' ')
		return ((int) 'S');
	if (str[0] == 'W' && str[1] == 'E' && str[2] == ' ')
		return ((int) 'W');
	if (str[0] == 'E' && str[1] == 'A' && str[2] == ' ')
		return ((int) 'E');
	if (str[0] == 'F' && str[1] == ' ')
		return ((int) 'F');
	if (str[0] == 'C' && str[1] == ' ')
		return ((int) 'C');
	return (0);
}

long	get_rgb_colour_id(char *str, int i, int j)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(&str[i]);
	while (ft_isdigit(str[i]))
		i++;
	if (r > 255 || r < 0 || i - j > 3 || i == j || str[i] != ',')
		return (-1);
	i++;
	j = i;
	g = ft_atoi(&str[i]);
	while (ft_isdigit(str[i]))
		i++;
	if (g > 255 || g < 0 || i - j > 3 || i == j || str[i] != ',')
		return (-1);
	i++;
	j = i;
	b = ft_atoi(&str[i]);
	while (ft_isdigit(str[i]))
		i++;
	if (b > 255 || b < 0 || i - j > 3 || i == j || !is_empty_str(&str[i]))
		return (-1);
	return (create_trgb(0, r, g, b));
}

int	add_colour_id(char *str, t_cube *data, int i, char type)
{
	long	ret;

	if ((type == 'F' && data->f_f) || (type == 'C' && data->c_f))
		return (EXIT_DUP_ID);
	ret = get_rgb_colour_id(str, i, i);
	if (ret == -1)
		return (EXIT_COR_ID);
	if (type == 'F')
	{
		data->f = (unsigned int)ret;
		data->f_f = 1;
	}
	else
	{
		data->c = (unsigned int)ret;
		data->c_f = 1;
	}
	return (EXIT_SUCCESS);
}

int	add_texture_id(char *str, t_cube *data, int i, char type)
{
	char	*texture;
	int		j;

	if ((type == 'N' && data->n_t) || (type == 'S' && data->s_t)
		|| (type == 'W' && data->w_t) || (type == 'E' && data->e_t))
		return (EXIT_DUP_ID);
	j = i;
	while (str[i] && str[i] != ' ' && str[i] != '\n')
		i++;
	if (!is_empty_str(&str[i]))
		return (EXIT_COR_ID);
	texture = ft_strndup(&str[j], i - j);
	if (!texture)
		return (EXIT_MALLOC);
	if (type == 'N')
		data->n_t = texture;
	else if (type == 'S')
		data->s_t = texture;
	else if (type == 'W')
		data->w_t = texture;
	else
		data->e_t = texture;
	return (EXIT_SUCCESS);
}

int	add_map_id(char *str, t_cube *data, int fd, int i)
{
	char	type;
	int		ret;

	type = (char)is_map_id(&str[i]);
	while (str[i] != ' ')
		i++;
	while (str[i] == ' ')
		i++;
	if (type == 'F' || type == 'C')
		ret = add_colour_id(str, data, i, type);
	else
		ret = add_texture_id(str, data, i, type);
	if (ret != EXIT_SUCCESS)
	{
		close(fd);
		free(str);
		ft_exit(data, ret);
	}
	return (EXIT_SUCCESS);
}
