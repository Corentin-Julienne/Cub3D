/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:47:08 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/17 21:04:03 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Get the color of the pixel to draw */
static int	get_color(t_game *game, t_raysult res, int y)
{
	int	cur_color;

	if (res.wall_orientation == 'N')
		cur_color = retrieve_color_in_texture(game->no_texture, res.offset, y);
	else if (res.wall_orientation == 'S')
		cur_color = retrieve_color_in_texture(game->so_texture, res.offset, y);
	else if (res.wall_orientation == 'E')
		cur_color = retrieve_color_in_texture(game->ea_texture, res.offset, y);
	else
		cur_color = retrieve_color_in_texture(game->we_texture, res.offset, y);
	return (cur_color);
}

/* Calculate wall heights and other calculations */
static void	calc_walls(t_game *game, t_raysult res, double *height, double *y)
{
	*height = game->ply->dist_from_proj * CUBES_SIZE / res.dist;
	*y = (game->wdw_y / 2) - (*height / 2);
}

/* Render walls from the map with the raycasting algorithm */
void	render_walls(t_game *game, int idx, double start_ang)
{
	double		wall_height;
	double		wall_y;
	int			y;
	int			x;
	t_raysult	res;

	start_ang = game->ply->ang_y - (PLY_VIEW_FOV_DEG / 2);
	x = 0;
	while (start_ang < game->ply->ang_y + (PLY_VIEW_FOV_DEG / 2))
	{
		send_raycast(game, start_ang, &res);
		calc_walls(game, res, &wall_height, &wall_y);
		y = wall_y;
		if (y < 0)
			y = 0;
		while (y < game->imgs_set[idx]->height && y < wall_y + wall_height)
		{
			int perc = (y - wall_y) / wall_height * 64;
			mlx_pixel_put_to_img(game->imgs_set[idx], x, y, get_color(game, res, perc));
			y++;
		}
		x++;
		start_ang += (double)PLY_VIEW_FOV_DEG / (double)game->wdw_x;
	}
}
