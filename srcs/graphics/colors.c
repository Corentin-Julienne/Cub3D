/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 14:09:21 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/18 14:25:05 by cjulienn         ###   ########.fr       */
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

static int	rtn_ceil_and_floor_colors(t_infomap *infomap, int type)
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

/* get_colors convert the colors of ceil and floor from trgb 
to a sole integer to be able to use it whith minilibx functions */

void	get_colors(t_game *game)
{
	game->col_ceil = rtn_ceil_and_floor_colors(game->infomap, CEILING);
	free(game->infomap->ceil_col);
	game->infomap->ceil_col = NULL;
	game->col_floor = rtn_ceil_and_floor_colors(game->infomap, FLOOR);
	free(game->infomap->floor_col);
	game->infomap->floor_col = NULL;
}

/* is used to retrieve a color of a pixel in a texture
x and y are the coordinates of this point in the texture img, 
not on the main img */

int	get_color_in_texture(t_img *mlx_img, int x, int y)
{
	int		color;
	int		offset;
	char	*dst;

	offset = y * mlx_img->line_length + x * (mlx_img->bits_per_pixel / 8);
	dst = mlx_img->addr + offset;
	color = *(int *)dst;
	return (color);
}
