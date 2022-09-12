/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:42:10 by cjulienn          #+#    #+#             */
/*   Updated: 2022/09/12 10:54:51 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* get_y_size allow to check the size of the y-axis of the map */

size_t	get_y_size(char	**map)
{
	size_t		y_size;

	y_size = 0;
	while (map && map[y_size])
		y_size++;
	return (y_size);
}

void	init_map_data(t_map_data *map_data, char *map)
{
	
}
