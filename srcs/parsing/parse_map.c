/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:48:53 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/18 12:29:24 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* parse_map is used to parse the grid of the map 
(the part composed of 0, 1 and player starting position and orientation) */

static void	fulfill_map(t_infomap *infomap, int i)
{
	int			j;

	j = 0;
	while (j < infomap->size_y)
	{
		infomap->map[j] = ft_strdup(infomap->cub[i + j]);
		if (!infomap->map[j])
		{
			free_problem_str_arr(&infomap->map, j);
			infomap->map = NULL;
			err_msg_and_free_map(ERR_MALLOC, infomap);
		}
		j++;
	}
	infomap->map[j] = NULL;
}

/* calc_map_dimensions allows to calculate infomap->size_y &&
infomap->size_x */

static void	calc_map_dimensions(t_infomap *infomap, int i)
{
	int			j;
	int			len;

	infomap->size_y = 0;
	while (infomap->cub && infomap->cub[i + infomap->size_y])
		infomap->size_y++;
	j = 0;
	len = INT_MIN;
	while (infomap->cub && infomap->cub[i + j])
	{
		if ((int)ft_strlen(infomap->cub[i + j]) > len)
			len = (int)ft_strlen(infomap->cub[i + j]);
		j++;
	}
	infomap->size_x = len;
}

void	parse_map(t_infomap *infomap, int i)
{
	if (!infomap->cub[i])
		err_msg_and_free_map(ERR_MISSING_GRID, infomap);
	calc_map_dimensions(infomap, i);
	infomap->map = (char **)malloc(sizeof(char *) * (infomap->size_y + 1));
	if (!infomap->map)
		err_msg_and_free_map(ERR_MALLOC, infomap);
	fulfill_map(infomap, i);
	free_split(&infomap->cub);
	infomap->cub = NULL;
	check_map_validity(infomap);
}
