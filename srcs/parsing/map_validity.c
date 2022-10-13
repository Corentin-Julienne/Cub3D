/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 18:03:18 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/13 12:00:30 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* check_invalid_nl verify that the map does not contain any empty line,
which is not allowed by the instructions PDF */

static void	check_invalid_nl(t_infomap *infomap)
{
	char			*map_lines;
	int				i;

	map_lines = ft_strnstr(infomap->lines, infomap->map[0],
			ft_strlen(infomap->lines));
	i = 0;
	while (map_lines && map_lines[i])
	{
		if (map_lines[i] == '\n' && map_lines[i + 1]
			&& map_lines[i + 1] == '\n')
			err_msg_and_free_map(ERR_EMPTY_LINE, infomap);
		i++;
	}
	free(infomap->lines);
	infomap->lines = NULL;
}

/* check if there is a player starting position and only one,
and check for invalid characters in map grid */

static void	check_invalid_grid_format(t_infomap *infomap)
{
	int		x;
	int		y;
	int		psp_num;

	psp_num = 0;
	y = 0;
	while (infomap->map[y])
	{
		x = 0;
		while (infomap->map[y][x])
		{
			if (!ft_isspace(infomap->map[y][x])
				&& !ft_strchr("01NSEW", infomap->map[y][x]))
				err_msg_and_free_map(ERR_INVALID_CHAR, infomap);
			if (ft_strchr("NSEW", infomap->map[y][x]))
				psp_num++;
			x++;
		}
		y++;
	}
	if (psp_num != 1)
		err_msg_and_free_map(ERR_PSP, infomap);
}

/* when verifying that a 0 is not actually close to a free space,
check wether the direction checked is in the map or not,
in order to avoid segfaults */

static int	is_out_of_map(t_infomap *infomap, int x, int y)
{
	int		size_line;

	size_line = ft_strlen(infomap->map[y]);
	if (y < 0 || y >= infomap->size_y)
		return (1);
	if (x < 0 || x >= size_line)
		return (1);
	return (0);
}

/* check whether the position of a 0 or a player starting position
(AKA S, O, W or E) is valid. In other terms, check wether the map is 
bounded by walls (AKA 1) */

static int	is_pos_valid(t_infomap *infomap, int x, int y)
{
	if (is_out_of_map(infomap, x + 1, y)
		|| ft_isspace(infomap->map[y][x + 1]))
		return (0);
	else if (is_out_of_map(infomap, x - 1, y)
		|| ft_isspace(infomap->map[y][x - 1]))
		return (0);
	else if (is_out_of_map(infomap, x, y + 1)
		|| ft_isspace(infomap->map[y + 1][x]))
		return (0);
	else if (is_out_of_map(infomap, x, y - 1)
		|| ft_isspace(infomap->map[y - 1][x]))
		return (0);
	return (1);
}

/* check_map_validity checks whether the map grid is valid,
which means 1) there is one player starting position with the orientation
(AKA N, S, W and E), 2) map is surrounded by wall,
3) no invalid char is present and 4) no empty line is present within
the map grid */

void	check_map_validity(t_infomap *infomap)
{
	int			x;
	int			y;

	check_invalid_nl(infomap);
	check_invalid_grid_format(infomap);
	x = 0;
	y = 0;
	while (infomap->map[y])
	{
		x = 0;
		while (infomap->map[y][x])
		{
			if (ft_strchr("0NSEW", infomap->map[y][x]))
			{
				if (!is_pos_valid(infomap, x, y))
					err_msg_and_free_map(ERR_BREACH_MAP, infomap);
			}
			x++;
		}
		y++;
	}
}
