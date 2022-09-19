/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_img_struct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 14:09:23 by cjulienn          #+#    #+#             */
/*   Updated: 2022/09/19 16:46:27 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* init_mlx_img_struct create a new image for the minilibx,
allocated space for the struct, then creating a window attached to 
the minilibx, then getting relevant data in order to be able to 
draw pixels with the custom function mlx_pixel_put_to_img */

t_mlx_img	*init_mlx_img_struct(void *mlx, int x, int y)
{
	t_mlx_img		*new;

	new = (t_mlx_img *)malloc(sizeof(t_mlx_img));
	if (!new)
		return (NULL);
	new->img = mlx_new_image(mlx, x, y);
	new->addr = mlx_get_data_addr(new->img, &new->bits_per_pixel,
				&new->line_length, &new->endian);
	new->width = x;
	new->height = y;
	new->mlx = mlx;
	return (new);
}

/* clear_mlx_img_struct destroy the img and free the struct */

void	clear_mlx_img_struct(t_mlx_img **mlx_img)
{
	mlx_destroy_image((*mlx_img)->mlx, (*mlx_img)->img);
	free(*mlx_img);
	*mlx_img = NULL;
}
