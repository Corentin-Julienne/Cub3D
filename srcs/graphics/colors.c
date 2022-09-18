/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 14:09:21 by cjulienn          #+#    #+#             */
/*   Updated: 2022/09/18 14:38:02 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* create_trgb_color use bitshift ops to convert 0 numbers
between 0 and 255 (one byte size) to an int regrouping
all those infos */

static int	create_trgb_color(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

/* convert the array of color informat rgb provided by 
the parsing of the map. Convert it to a single int use by mlx
to color a pixel using a given color. Put the first parameter 
to 0 as it is transparency */

int	rtn_ceil_and_floor_colors(t_infomap *infomap, int type)
{
	int		color;

	if (type == CEILING)
	{
		color = create_trgb_color(0, infomap->ceil_col[0],
			infomap->ceil_col[1], infomap->ceil_col[2]);
	}
	else
	{
		color = create_trgb_color(0, infomap->floor_col[0],
			infomap->floor_col[1], infomap->floor_col[2]);
	}
	return (color);
}
