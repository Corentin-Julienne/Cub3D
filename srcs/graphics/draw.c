/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 14:34:12 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/18 14:25:05 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* mlx_pixel_put_to_img allow to draw a pixel in the img, not to the window
The img is draw and then is "glued" into the window */

void	mlx_pixel_put_to_img(t_img *mlx_img, int x, int y, int color)
{
	char	*dst;
	int		offset;

	if (x >= mlx_img->width || y >= mlx_img->height)
		return ;
	offset = y * mlx_img->line_length + x * (mlx_img->bits_per_pixel / 8);
	dst = mlx_img->addr + offset;
	*(unsigned int *)dst = color;
}
