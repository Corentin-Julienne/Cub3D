/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crosshair.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:55:38 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/10 16:43:48 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* display a minimalistic standard FPS-style crosshair
in the center of the screen */

void	render_crosshair(t_game *game, int img_index)
{
	int			center_x;
	int			center_y;
	int			i;
	int			j;

	center_x = game->wdw_x / 2;
	center_y = game->wdw_y / 2;
	i = -10;
	j = -10;
	while (i < 10)
	{	
		mlx_pixel_put_to_img(game->imgs_set[img_index],
			center_x + i, center_y, 0x0000000);
		i++;
	}
	while (j < 10)
	{
		mlx_pixel_put_to_img(game->imgs_set[img_index],
			center_x, center_y + j, 0x0000000);
		j++;
	}
}
