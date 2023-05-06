/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:06:08 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/21 09:34:56 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* if no changes have been made, return 0, otherwise 1 */

static int	is_data_updated(t_player *ply, double prev_x,
	double prev_y, double prev_ang)
{
	if (ply->pos_x == prev_x && ply->pos_y == prev_y && ply->ang_y == prev_ang)
		return (0);
	return (1);
}

/* Check if there is a wall near the player */
static int	wall_near_ply(t_game *game, t_player *ply)
{
	int		x;
	int		y;

	if (ply->pos_x <= 64 && ply->pos_y <= 64 && ply->pos_x >= (game->\
	infomap->size_x - 1) * 64 && ply->pos_y >= (game->infomap->size_y - 1) * 64)
		return (1);
	y = 0;
	while (y < game->infomap->size_y)
	{
		x = 0;
		while (x < game->infomap->size_x)
		{
			if (game->infomap->map[y][x] == '1' && (ply->pos_x >= ((double)(x * \
			CUBES_SIZE)) - 5 && ply->pos_y >= ((double)(y * CUBES_SIZE)) - 5 \
			&& ply->pos_x <= ((double)(x * CUBES_SIZE)) + CUBES_SIZE + 5 && \
			ply->pos_y <= ((double)(y * CUBES_SIZE)) + CUBES_SIZE + 5))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

/* update pos (x, y ) of the player when WASD key are pressed */

static void	update_coord(t_game *game, t_player *ply)
{
	int	multiplier;

	multiplier = 4 + 4 * game->keys[6];
	if (game->keys[0] == true)
	{
		ply->pos_x += cos(ply->ang_y * M_PI / 180) * multiplier;
		ply->pos_y -= sin(ply->ang_y * M_PI / 180) * multiplier;
	}
	if (game->keys[1] == true)
	{
		ply->pos_x -= cos(ply->ang_y * M_PI / 180) * multiplier;
		ply->pos_y += sin(ply->ang_y * M_PI / 180) * multiplier;
	}
	if (game->keys[2] == true)
	{
		ply->pos_x += cos((ply->ang_y + 90) * M_PI / 180) * multiplier;
		ply->pos_y -= sin((ply->ang_y + 90) * M_PI / 180) * multiplier;
	}
	if (game->keys[3] == true)
	{
		ply->pos_x += cos((ply->ang_y - 90) * M_PI / 180) * multiplier;
		ply->pos_y -= sin((ply->ang_y - 90) * M_PI / 180) * multiplier;
	}
}

/* update_player_data is used to modify the player data
(position and angle), when the WASD and directional arrows 
are pressed */

int	update_player_data(t_game *game, t_player *ply)
{
	double			prev_pos_x;
	double			prev_pos_y;
	double			prev_ang;

	prev_pos_x = ply->pos_x;
	prev_pos_y = ply->pos_y;
	prev_ang = ply->ang_y;
	update_coord(game, ply);
	if (game->keys[4])
		ply->ang_y -= 2;
	if (game->keys[5])
		ply->ang_y += 2;
	if (wall_near_ply(game, ply))
	{
		ply->pos_x = prev_pos_x;
		ply->pos_y = prev_pos_y;
	}
	return (is_data_updated(ply, prev_pos_x, prev_pos_y, prev_ang));
}
