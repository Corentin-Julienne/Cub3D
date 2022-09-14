/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:48:53 by cjulienn          #+#    #+#             */
/*   Updated: 2022/09/14 16:19:57 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	parse_map(t_map_data *map_data, int i)
{
	int		j;
	
	if (!map_data->cub[i])
		; // error : no map is present
	map_data->size_y = 0;
	while (map_data->cub && map_data->cub[i + map_data->size_y])
		map_data->size_y++;
	map_data->map = (char **)malloc(sizeof(char *) * (map_data->size_y + 1));
	if (!map_data->map)
		; // handle malloc error
	j = 0;
	while (j < map_data->size_y)
	{
		map_data->map[j] = ft_strdup(map_data->cub[i + j]);
		if (!map_data->map[j])
			; // handle malloc error
		j++;
	}
	map_data->map[j] = NULL;
	free_split(map_data->cub);
	check_map_validity(map_data);
}
