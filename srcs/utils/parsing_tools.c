/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:29:10 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/18 14:44:26 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* store_intarr_to_struct store the int* containing RGB info
for ceiling or floor to the relevant map category.
If information is duplicated, triggers an error msg */

static void	store_intarr_to_struct(t_infomap *infomap, char *line,
				int *colors, char **color_arr)
{
	if (!ft_strncmp("C ", line, 2) && infomap->ceil_col == NULL)
		infomap->ceil_col = colors;
	else if (!ft_strncmp("F ", line, 2) && infomap->floor_col == NULL)
		infomap->floor_col = colors;
	else
	{
		free_split(&color_arr);
		free(colors);
		err_msg_and_free_map(ERR_DUP_PARAM, infomap);
	}
	free_split(&color_arr);
}

/* convert_to_intarr convert a char** to an int[3] which
contains colors for ceiling or floor in a RGB format
trigger an err msg if the format is out of range 0 - 255 */

static void	fulfill_intarr(t_infomap *infomap, int *colors, char **color_arr)
{
	int			i;

	i = 0;
	while (i < 3)
	{
		if (ft_strlen(color_arr[i]) > 3)
		{
			free_split(&color_arr);
			free(colors);
			err_msg_and_free_map(ERR_COLOR_RANGE, infomap);
		}
		colors[i] = ft_atoi(color_arr[i]);
		if (colors[i] > 255 || colors[i] < 0)
		{
			free_split(&color_arr);
			free(colors);
			err_msg_and_free_map(ERR_COLOR_RANGE, infomap);
		}
		i++;
	}
}

void	convert_to_intarr(t_infomap *infomap, char *line, char **color_arr)
{
	int		*colors;

	colors = (int *)malloc(sizeof(int) * 3);
	if (!colors)
	{
		free_split(&color_arr);
		err_msg_and_free_map(ERR_MALLOC, infomap);
	}
	fulfill_intarr(infomap, colors, color_arr);
	store_intarr_to_struct(infomap, line, colors, color_arr);
}
