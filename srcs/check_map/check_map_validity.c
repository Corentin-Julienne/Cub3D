/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_validity.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 18:03:18 by cjulienn          #+#    #+#             */
/*   Updated: 2022/09/13 18:41:37 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* check_invalid_nl verify that the map does not contain any empty line,
which is not allowed by the instructions PDF */

static void	check_invalid_nl(t_map_data *map_data)
{
	char			**map_lines;
	int				i;

	map_lines = map_data->lines;
	i = 0;
	while (map_lines && map_lines[i])
	{
		if (map_lines[i] == '\n' && map_lines[i + 1] 
			&& map_lines[i + 1] == '\n')
			; // handle with error msg
		i++;
	}
	free(map_data->lines);
	map_data->lines = NULL;
}

/* when verifying that a 0 is not actually close to a free space,
check wether the direction checked is in the map or not,
in order to avoid segfaults */

static int	is_out_of_map(t_map_data *map_data, int x, int y)
{
	return (0);
}

static int	is_pos_valid(t_map_data *map_data, int x, int y)
{
	if (is_out_of_map(map_data, x + 1, y) || )
		return (1);
	else if (is_out_of_map(map_data, x - 1, y) || )
		return (1);
	else if (is_out_of_map(map_data, x, y + 1) || )
		return (1);
	else if (is_out_of_map(map_data, x, y - 1) || )
		return (1);
	return (0);
}

static int	is_verif_needed(t_map_data *map_data, int x, int y)
{
	if (map_data->map[y][x] == '0' || map_data->map[y][x] == 'N'
		|| map_data->map[y][x] == 'S' || map_data->map[y][x] == 'E'
		|| map_data->map[y][x] == 'W')
		return (1);
	return (0);
}

void	check_map_validity(t_map_data *map_data)
{
	int			x;
	int			y;
	
	check_invalid_nl(map_data);
	x = 0;
	y = 0;
	while (map_data->map[y])
	{
		x = 0;
		while (map_data->map[y][x])
		{
			if (is_verif_needed(map_data, x, y) == 1) // change that
			{
				if (is_pos_valid(map_data, x, y) == 1)
					; // handle error : unvalid map 				
			}
			x++;
		}
		y++;	
	}
}
