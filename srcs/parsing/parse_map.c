/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:48:53 by cjulienn          #+#    #+#             */
/*   Updated: 2022/09/16 13:01:33 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* parse_map is used to parse the grid of the map 
(the part composed of 0, 1 and player starting position and orientation) */

static void	fulfill_map(t_map_data *map_data, int i)
{
	int			j;

	j = 0;
	while (j < map_data->size_y)
	{
		map_data->map[j] = ft_strdup(map_data->cub[i + j]);
		if (!map_data->map[j])
		{
			free_problem_str_arr(map_data->map, j);
			map_data->map = NULL;
			err_msg_and_free(ERR_MALLOC, map_data);
		}
		j++;
	}
	map_data->map[j] = NULL;
}

void	parse_map(t_map_data *map_data, int i)
{
	if (!map_data->cub[i])
		err_msg_and_free(ERR_MISSING_GRID, map_data);
	map_data->size_y = 0;
	while (map_data->cub && map_data->cub[i + map_data->size_y])
		map_data->size_y++;
	map_data->map = (char **)malloc(sizeof(char *) * (map_data->size_y + 1));
	if (!map_data->map)
		err_msg_and_free(ERR_MALLOC, map_data);
	fulfill_map(map_data, i);
	free_split(map_data->cub);
	map_data->cub = NULL;
	check_map_validity(map_data);
}
