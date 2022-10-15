/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:16:06 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/15 13:21:37 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* check wether the provided coordinates are within the map background.
Returns 1 if it is the case, 0 otherwise */

int	is_within_minimap(t_minimap *mini, int x, int y)
{
	if (x < mini->offset + mini->padding_x || x > mini->offset + mini->width)
		return (0);
	if (y < mini->offset + mini->padding_y || y > mini->offset + mini->height)
		return (0);
	return (1);
}

/* check wether the minimap is big enough to display the entire 
map. Return 1 if it is the case, 0 otherwise. */

int	is_map_fitting(t_minimap *mini, t_game *game)
{
	if (mini->width - (mini->padding_x * 2) < game->infomap->size_x
		* mini->edge_len)
		return (0);
	if (mini->height - (mini->padding_y * 2) < game->infomap->size_y
		* mini->edge_len)
		return (0);
	return (1);
}

/* render a cubic section of wall (in white) */

void	render_square(t_minimap *mini, t_game *game, int x, int y)
{
	int			i;
	int			j;

	j = 0;
	while (y + j < y + mini->edge_len)
	{
		i = 0;
		while (x + i < x + mini->edge_len)
		{
			if (is_within_minimap(mini, x + i, y + j) == 1)
			{
				mlx_pixel_put_to_img(game->imgs_set[mini->img_index],
					x + i, y + j, mini->col_square);
			}
			i++;
		}
		j++;
	}
}

/* render the minimap background (in black) */

void	render_background(t_minimap *mini, t_game *game, int img_index)
{
	int		i;
	int		j;

	j = 0;
	while (j < mini->height)
	{
		i = 0;
		while (i < mini->width)
		{
			mlx_pixel_put_to_img(game->imgs_set[img_index],
				i + mini->offset, j + mini->offset, mini->col_back);
			i++;
		}
		j++;
	}
}
