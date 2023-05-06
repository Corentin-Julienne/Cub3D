/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:48:53 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/21 09:31:13 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Just some function to bypass the norm */
static void	assign_map(t_infomap *infomap, int y, int j)
{
	j = 0;
	while (j < infomap->size_x)
		infomap->map[y][j++] = ' ';
	infomap->map[y][j] = '\0';
}

/* parse_map is used to parse the grid of the map 
(the part composed of 0, 1 and player starting position and orientation) */
static void	fulfill_map(t_infomap *infomap, int i)
{
	int			y;
	int			j;

	y = 0;
	while (y < infomap->size_y)
	{
		infomap->map[y] = malloc(sizeof(char) * (infomap->size_x + 1));
		if (!infomap->map[y])
		{
			free_problem_str_arr(&infomap->map, y);
			infomap->map = NULL;
			err_msg_and_free_map(ERR_MALLOC, infomap);
		}
		assign_map(infomap, y, j);
		j = 0;
		while (infomap->cub[i + y][j] && j < infomap->size_x)
		{
			if (ft_isalnum(infomap->cub[i + y][j]))
				infomap->map[y][j] = infomap->cub[i + y][j];
			j++;
		}
		y++;
	}
	infomap->map[y] = NULL;
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

/* Parse the actual map into the infomap map char array */
void	parse_map(t_infomap *infomap, int i)
{
	int	y;

	if (!infomap->cub[i])
		err_msg_and_free_map(ERR_MISSING_GRID, infomap);
	calc_map_dimensions(infomap, i);
	infomap->map = (char **)malloc(sizeof(char *) * (infomap->size_y + 1));
	if (!infomap->map)
		err_msg_and_free_map(ERR_MALLOC, infomap);
	y = 0;
	while (y < infomap->size_y)
		infomap->map[y++] = NULL;
	fulfill_map(infomap, i);
	free_split(&infomap->cub);
	infomap->cub = NULL;
	check_map_validity(infomap);
}
