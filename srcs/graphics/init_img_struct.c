/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img_struct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 14:09:23 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/17 21:11:22 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* init_img_struct create a new image for the minilibx,
allocated space for the struct, then creating a window attached to 
the minilibx, then getting relevant data in order to be able to 
draw pixels with the custom function mlx_pixel_put_to_img */

t_img	*init_img_struct(void *mlx, int x, int y, int type)
{
	t_img		*new;

	new = (t_img *)malloc(sizeof(t_img));
	if (!new)
		return (NULL);
	if (type == NEW_IMG)
	{
		new->img = mlx_new_image(mlx, x, y);
		new->addr = mlx_get_data_addr(new->img, &new->bits_per_pixel, \
		&new->line_length, &new->endian);
	}
	else
		new->img = NULL;
	new->width = x;
	new->height = y;
	new->mlx = mlx;
	return (new);
}
