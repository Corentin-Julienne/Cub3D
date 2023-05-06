/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:47:08 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/21 09:37:07 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Get the color of the pixel to draw */
static int	get_color(t_game *game, t_raysult res, int y, double *walls)
{
	int	cur_color;
	int	offsety;

	offsety = (y - walls[0]) / walls[1] * 64;
	if (res.wall_orientation == 'N')
		cur_color = get_color_in_texture(game->no_texture,
				CUBES_SIZE - res.offset, offsety);
	else if (res.wall_orientation == 'S')
		cur_color = get_color_in_texture(game->so_texture, res.offset, offsety);
	else if (res.wall_orientation == 'E')
		cur_color = get_color_in_texture(game->ea_texture,
				CUBES_SIZE - res.offset, offsety);
	else
		cur_color = get_color_in_texture(game->we_texture, res.offset, offsety);
	return (cur_color);
}

/* Calculate wall heights and other calculations */
static void	calc_walls(t_game *game, t_raysult res, double *height, double *y)
{
	*height = game->ply->dist_from_proj * CUBES_SIZE / res.dist;
	*y = (game->wdw_y / 2) - (*height / 2);
}

/* Render walls from the map with the raycasting algorithm */
void	render_walls(t_game *game, int idx, double start_ang, int x)
{
	double		walls[2];
	int			y;
	t_raysult	res;

	start_ang = game->ply->ang_y - (PLY_VIEW_FOV_DEG / 2);
	x = 0;
	while (start_ang < game->ply->ang_y + (PLY_VIEW_FOV_DEG / 2))
	{
		send_raycast(game, start_ang, &res);
		if (res.dist != -1)
		{
			calc_walls(game, res, &walls[1], &walls[0]);
			y = walls[0];
			if (y < 0)
				y = 0;
			while (y < game->imgs_set[idx]->height && y < walls[0] + walls[1])
			{
				mlx_pixel_put_to_img(game->imgs_set[idx], x, y, \
				get_color(game, res, y, walls));
				y++;
			}
		}
		x++;
		start_ang += (double)PLY_VIEW_FOV_DEG / (double)game->wdw_x;
	}
}
