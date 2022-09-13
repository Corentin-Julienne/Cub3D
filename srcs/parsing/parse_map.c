/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:48:53 by cjulienn          #+#    #+#             */
/*   Updated: 2022/09/13 17:59:07 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	calc_width_map(t_map_data *map_data)
{
	int			i;
	int			len;

	i = 0;
	map_data->size_x = INT_MIN;
	while (map_data->map && map_data->map[i])
	{
		len = ft_strlen(map_data->map[i]);
		if (len > map_data->size_x)
			map_data->size_x = len;
		i++;
	}
}

static void	parse_extended_map(t_map_data *map_data) // remove ?
{
	char	**xtd_map;
	char	*up_and_down;
	int		i;

	xtd_map = (char **)malloc(sizeof(char *) * (map_data->size_y + 3));
	if (!xtd_map)
		; // handle malloc error
	up_and_down = (char *)malloc(sizeof(char) * (map_data->size_x + 3));
	if (!up_and_down)
		; // handle malloc error
	i = 0;
	while (i < map_data->size_x + 2)
	{
		up_and_down[i] = 'E';
		i++;
	}
	up_and_down[i] = '\0';
	xtd_map[0] = up_and_down;
	xtd_map[map_data->size_x + 2] = ft_strdup(up_and_down);
	if (!xtd_map[map_data->size_x + 2])
		; // handle malloc error
	xtd_map[map_data->size_x + 3] = NULL;
	
}

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
	// TO IMPLEMENT : free cub with free_split and put it to NULL
	calc_width_map(map_data); // useless ?
	// TO IMPLEMENT : checking map validity
	parse_extended_map(map_data); // seems useless
}
